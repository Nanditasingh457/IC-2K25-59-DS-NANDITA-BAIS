/**
 * Course: IC-307D Data Structures and Algorithms LAB
 * Unit 2: Sorting & Searching Algorithms Application 02
 * Application: Search Engine Simulator (Dictionary with Binary Search & Hashing)
 * 
 * Collision Handling:
 *   1. Hash Table with Separate Chaining (Linked Lists)
 *   2. Hash Table with Linear Probing (Open Addressing)
 *   3. Sorted Dictionary with Binary Search - O(log n)
 * 
 * Student Name: Nandita Bais
 * Roll Number: IC-2K25-59
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define TABLE_SIZE 17
#define MAX_WORD_LEN 50
#define MAX_URL_LEN 100

// --- Separate Chaining Node ---
typedef struct ChainNode {
    char keyword[MAX_WORD_LEN];
    char targetUrl[MAX_URL_LEN];
    struct ChainNode *next;
} ChainNode;

// --- Linear Probing Entry ---
typedef struct {
    char keyword[MAX_WORD_LEN];
    char targetUrl[MAX_URL_LEN];
    bool isOccupied;
} LinearProbeEntry;

// --- Sorted Dictionary Entry ---
typedef struct {
    char keyword[MAX_WORD_LEN];
    char targetUrl[MAX_URL_LEN];
} DictEntry;

// Hash function (djb2)
unsigned long hashDJB2(const char *str) {
    unsigned long hash = 5381;
    int c;
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
    return hash % TABLE_SIZE;
}

// Global data structures
static ChainNode *chainTable[TABLE_SIZE] = {NULL};
static LinearProbeEntry probeTable[TABLE_SIZE];
static DictEntry sortedDict[TABLE_SIZE * 2];
static int dictCount = 0;

void initTables(void) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        chainTable[i] = NULL;
        probeTable[i].isOccupied = false;
        probeTable[i].keyword[0] = '\0';
        probeTable[i].targetUrl[0] = '\0';
    }
    dictCount = 0;
}

// Separate Chaining Insert
void insertSeparateChaining(const char *key, const char *url) {
    unsigned long index = hashDJB2(key);
    ChainNode *newNode = (ChainNode *)malloc(sizeof(ChainNode));
    strncpy(newNode->keyword, key, MAX_WORD_LEN - 1);
    newNode->keyword[MAX_WORD_LEN - 1] = '\0';
    strncpy(newNode->targetUrl, url, MAX_URL_LEN - 1);
    newNode->targetUrl[MAX_URL_LEN - 1] = '\0';
    newNode->next = chainTable[index];
    chainTable[index] = newNode;
}

// Linear Probing Insert
bool insertLinearProbing(const char *key, const char *url) {
    unsigned long startIdx = hashDJB2(key);
    for (int i = 0; i < TABLE_SIZE; i++) {
        int idx = (startIdx + i) % TABLE_SIZE;
        if (!probeTable[idx].isOccupied) {
            strncpy(probeTable[idx].keyword, key, MAX_WORD_LEN - 1);
            probeTable[idx].keyword[MAX_WORD_LEN - 1] = '\0';
            strncpy(probeTable[idx].targetUrl, url, MAX_URL_LEN - 1);
            probeTable[idx].targetUrl[MAX_URL_LEN - 1] = '\0';
            probeTable[idx].isOccupied = true;
            return true;
        }
    }
    return false; // Table full
}

// Compare function for qsort on sorted dictionary
int compareDict(const void *a, const void *b) {
    return strcmp(((const DictEntry *)a)->keyword, ((const DictEntry *)b)->keyword);
}

void insertDictionary(const char *key, const char *url) {
    insertSeparateChaining(key, url);
    insertLinearProbing(key, url);

    strncpy(sortedDict[dictCount].keyword, key, MAX_WORD_LEN - 1);
    sortedDict[dictCount].keyword[MAX_WORD_LEN - 1] = '\0';
    strncpy(sortedDict[dictCount].targetUrl, url, MAX_URL_LEN - 1);
    sortedDict[dictCount].targetUrl[MAX_URL_LEN - 1] = '\0';
    dictCount++;
    qsort(sortedDict, dictCount, sizeof(DictEntry), compareDict);
}

// Search Separate Chaining
const char *searchChaining(const char *key, int *probes) {
    *probes = 0;
    unsigned long index = hashDJB2(key);
    ChainNode *curr = chainTable[index];
    while (curr) {
        (*probes)++;
        if (strcmp(curr->keyword, key) == 0) {
            return curr->targetUrl;
        }
        curr = curr->next;
    }
    return NULL;
}

// Search Linear Probing
const char *searchLinearProbing(const char *key, int *probes) {
    *probes = 0;
    unsigned long startIdx = hashDJB2(key);
    for (int i = 0; i < TABLE_SIZE; i++) {
        (*probes)++;
        int idx = (startIdx + i) % TABLE_SIZE;
        if (!probeTable[idx].isOccupied) {
            return NULL; // Empty slot means key does not exist
        }
        if (strcmp(probeTable[idx].keyword, key) == 0) {
            return probeTable[idx].targetUrl;
        }
    }
    return NULL;
}

// Search Binary Search on Sorted Dictionary
const char *searchBinary(const char *key, int *comparisons) {
    *comparisons = 0;
    int low = 0, high = dictCount - 1;
    while (low <= high) {
        (*comparisons)++;
        int mid = low + (high - low) / 2;
        int cmp = strcmp(sortedDict[mid].keyword, key);
        if (cmp == 0) {
            return sortedDict[mid].targetUrl;
        } else if (cmp < 0) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return NULL;
}

void displayChainingTable(void) {
    printf("\n=== Hash Table: Separate Chaining ===\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        printf(" Bucket [%2d]: ", i);
        ChainNode *curr = chainTable[i];
        if (!curr) {
            printf("NULL\n");
        } else {
            while (curr) {
                printf("[%s -> %s] -> ", curr->keyword, curr->targetUrl);
                curr = curr->next;
            }
            printf("NULL\n");
        }
    }
}

void displayLinearTable(void) {
    printf("\n=== Hash Table: Linear Probing ===\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (probeTable[i].isOccupied) {
            printf(" Slot [%2d]: %-15s -> %s\n", i, probeTable[i].keyword, probeTable[i].targetUrl);
        } else {
            printf(" Slot [%2d]: [EMPTY]\n", i);
        }
    }
}

void loadDefaultIndex(void) {
    insertDictionary("algorithms",   "https://cs.edu/algorithms");
    insertDictionary("arrays",       "https://cs.edu/arrays");
    insertDictionary("binary_search","https://cs.edu/binary_search");
    insertDictionary("compiler",     "https://cs.edu/gcc_compiler");
    insertDictionary("graphs",       "https://cs.edu/graph_theory");
    insertDictionary("hashing",      "https://cs.edu/hash_tables");
    insertDictionary("matrices",     "https://cs.edu/sparse_matrices");
    insertDictionary("pointers",     "https://cs.edu/c_pointers");
    insertDictionary("queues",       "https://cs.edu/queues");
    insertDictionary("sorting",      "https://cs.edu/sorting_comparison");
    insertDictionary("stacks",       "https://cs.edu/stack_adt");
    insertDictionary("trees",        "https://cs.edu/binary_trees");
}

void clearInputBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main(void) {
    initTables();
    loadDefaultIndex();

    int choice;
    char query[MAX_WORD_LEN];

    printf("============================================================\n");
    printf("   IC-307D LAB 2 | Search Engine Simulator (Application 02) \n");
    printf("   Student: Nandita Bais | Roll No: IC-2K25-59              \n");
    printf("============================================================\n\n");

    printf("[INFO] Pre-loaded 12 computer science keywords into inverted index.\n");

    do {
        printf("\n------------- SEARCH ENGINE SIMULATOR MENU -------------\n");
        printf(" 1. Query Keyword Across All Structures (Comparative Search)\n");
        printf(" 2. Display Hash Table (Separate Chaining)\n");
        printf(" 3. Display Hash Table (Linear Probing)\n");
        printf(" 4. Display Sorted Keyword Dictionary (Binary Search pre-sort)\n");
        printf(" 5. Insert New Keyword & URL\n");
        printf(" 6. Collision & Performance Metrics\n");
        printf(" 0. Exit Simulator\n");
        printf("--------------------------------------------------------\n");
        printf("Enter your choice (0-6): ");

        if (scanf("%d", &choice) != 1) {
            printf("[ERROR] Invalid choice. Enter a number.\n");
            clearInputBuffer();
            continue;
        }

        switch (choice) {
            case 1: {
                printf("Enter search query keyword: ");
                scanf("%49s", query);

                int chainProbes = 0, linearProbes = 0, binComps = 0;
                const char *urlChain = searchChaining(query, &chainProbes);
                const char *urlLinear = searchLinearProbing(query, &linearProbes);
                const char *urlBin = searchBinary(query, &binComps);

                printf("\n================ MULTI-INDEX QUERY RESULTS ================\n");
                printf(" Query Keyword: '%s'\n", query);
                if (urlChain) {
                    printf(" Found Target URL (Chaining) : %s\n", urlChain);
                    printf(" Found Target URL (Linear)   : %s\n", urlLinear ? urlLinear : "N/A");
                    printf(" Found Target URL (Binary)   : %s\n\n", urlBin ? urlBin : "N/A");
                    printf(" Retrieval Method           | Comparisons / Probes | Lookup Complexity\n");
                    printf(" ---------------------------+----------------------+------------------\n");
                    printf(" 1. Hash (Separate Chaining)| %-20d | O(1) Average\n", chainProbes);
                    printf(" 2. Hash (Linear Probing)   | %-20d | O(1) Average\n", linearProbes);
                    printf(" 3. Sorted Binary Search    | %-20d | O(log n) Exact\n", binComps);
                } else {
                    printf(" Query keyword '%s' not indexed in database!\n", query);
                    printf(" Probes Checked: Chaining: %d | Linear: %d | Binary: %d\n", chainProbes, linearProbes, binComps);
                }
                printf("===========================================================\n");
                break;
            }

            case 2:
                displayChainingTable();
                break;

            case 3:
                displayLinearTable();
                break;

            case 4:
                printf("\n=== Sorted Dictionary for Binary Search (Size = %d) ===\n", dictCount);
                for (int i = 0; i < dictCount; i++) {
                    printf(" [%2d] %-16s -> %s\n", i, sortedDict[i].keyword, sortedDict[i].targetUrl);
                }
                break;

            case 5: {
                char newKey[MAX_WORD_LEN], newUrl[MAX_URL_LEN];
                printf("Enter keyword (no spaces): ");
                scanf("%49s", newKey);
                printf("Enter destination URL: ");
                scanf("%99s", newUrl);
                insertDictionary(newKey, newUrl);
                printf("[SUCCESS] Added '%s' -> '%s' to all search indexes.\n", newKey, newUrl);
                break;
            }

            case 6: {
                int chainCollisions = 0;
                for (int i = 0; i < TABLE_SIZE; i++) {
                    int chainLen = 0;
                    ChainNode *c = chainTable[i];
                    while (c) {
                        chainLen++;
                        c = c->next;
                    }
                    if (chainLen > 1) {
                        chainCollisions += (chainLen - 1);
                    }
                }
                printf("\n============== HASH ENGINE STATISTICS ==============\n");
                printf(" Table Bucket Capacity : %d slots\n", TABLE_SIZE);
                printf(" Total Indexed Keywords : %d entries\n", dictCount);
                printf(" Load Factor (alpha)    : %.2f\n", (float)dictCount / TABLE_SIZE);
                printf(" Chaining Collisions    : %d bucket overflow events\n", chainCollisions);
                printf(" Collision Strategies   : Separate Chaining & Linear Probing\n");
                printf(" Average Search Cost    : O(1 + alpha) for Hashing vs O(log n) for Binary Search\n");
                printf("====================================================\n");
                break;
            }

            case 0:
                printf("\nExiting Search Engine Simulator. Goodbye!\n");
                break;

            default:
                printf("[ERROR] Invalid choice '%d'.\n", choice);
                break;
        }
    } while (choice != 0);

    return 0;
}
