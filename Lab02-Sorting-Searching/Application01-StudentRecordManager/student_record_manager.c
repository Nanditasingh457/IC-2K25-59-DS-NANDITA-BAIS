/**
 * Course: IC-307D Data Structures and Algorithms LAB
 * Unit 2: Sorting & Searching Algorithms Application 01
 * Application: Student Record Manager
 * 
 * Features:
 *   1. Store and manage structured student records (Roll No, Name, Marks)
 *   2. Quick Sort by Roll Number
 *   3. Merge Sort by Marks (Descending Rank Ordering)
 *   4. Insertion Sort by Name (Alphabetical)
 *   5. Binary Search by Roll Number - O(log n)
 *   6. Linear Search by Name
 *   7. Comparative Performance Reporting
 * 
 * Student Name: Nandita Bais
 * Roll Number: IC-2K25-59
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define MAX_STUDENTS 100

typedef struct {
    int rollNo;
    char name[50];
    float marks;
} Student;

// Prototypes
void displayStudents(const Student s[], int n);
void mergeSortByMarks(Student s[], int l, int r, long long *comp);
void quickSortByRoll(Student s[], int low, int high, long long *comp, long long *swaps);
void insertionSortByName(Student s[], int n, long long *comp, long long *shifts);
int binarySearchRoll(const Student s[], int n, int targetRoll, long long *comp);
int linearSearchName(const Student s[], int n, const char *targetName);
void loadDefaultStudents(Student s[], int *n);
void clearInputBuffer(void);

int main(void) {
    Student students[MAX_STUDENTS];
    int count = 0;
    int choice;
    bool sortedByRoll = false;

    printf("============================================================\n");
    printf("   IC-307D LAB 2 | Student Record Manager (Application 01)  \n");
    printf("   Student: Nandita Bais | Roll No: IC-2K25-59              \n");
    printf("============================================================\n\n");

    loadDefaultStudents(students, &count);
    printf("[INFO] Loaded %d initial student records.\n", count);
    displayStudents(students, count);

    do {
        printf("\n------------- STUDENT RECORD MANAGER MENU -------------\n");
        printf(" 1. Display All Student Records\n");
        printf(" 2. Add New Student Record\n");
        printf(" 3. Sort Records by Roll Number (Quick Sort)\n");
        printf(" 4. Sort Records by Marks / Merit Rank (Merge Sort)\n");
        printf(" 5. Sort Records Alphabetically by Name (Insertion Sort)\n");
        printf(" 6. Search Student by Roll Number (Binary Search)\n");
        printf(" 7. Search Student by Name (Linear Search)\n");
        printf(" 8. Run Comparative Sorting Performance Report\n");
        printf(" 0. Exit System\n");
        printf("-------------------------------------------------------\n");
        printf("Enter your selection (0-8): ");

        if (scanf("%d", &choice) != 1) {
            printf("[ERROR] Invalid choice. Enter a number.\n");
            clearInputBuffer();
            continue;
        }

        switch (choice) {
            case 1:
                displayStudents(students, count);
                break;

            case 2:
                if (count >= MAX_STUDENTS) {
                    printf("[OVERFLOW] Maximum student capacity reached!\n");
                    break;
                }
                printf("Enter Roll Number (int): ");
                scanf("%d", &students[count].rollNo);
                clearInputBuffer();
                printf("Enter Full Name: ");
                fgets(students[count].name, sizeof(students[count].name), stdin);
                students[count].name[strcspn(students[count].name, "\r\n")] = '\0';
                printf("Enter Marks (0.0 to 100.0): ");
                scanf("%f", &students[count].marks);
                count++;
                sortedByRoll = false;
                printf("[SUCCESS] Student record added successfully.\n");
                break;

            case 3: {
                long long comp = 0, swaps = 0;
                quickSortByRoll(students, 0, count - 1, &comp, &swaps);
                sortedByRoll = true;
                printf("\n[SUCCESS] Records sorted by Roll Number using Quick Sort.\n");
                printf("Comparisons: %lld | Swaps: %lld\n", comp, swaps);
                displayStudents(students, count);
                break;
            }

            case 4: {
                long long comp = 0;
                mergeSortByMarks(students, 0, count - 1, &comp);
                sortedByRoll = false;
                printf("\n[SUCCESS] Records sorted by Marks (Descending) using Merge Sort.\n");
                printf("Comparisons: %lld\n", comp);
                displayStudents(students, count);
                break;
            }

            case 5: {
                long long comp = 0, shifts = 0;
                insertionSortByName(students, count, &comp, &shifts);
                sortedByRoll = false;
                printf("\n[SUCCESS] Records sorted Alphabetically by Name using Insertion Sort.\n");
                printf("Comparisons: %lld | Shifts: %lld\n", comp, shifts);
                displayStudents(students, count);
                break;
            }

            case 6: {
                if (!sortedByRoll) {
                    printf("[INFO] Array must be sorted by Roll Number before Binary Search. Auto-sorting now...\n");
                    long long c = 0, s = 0;
                    quickSortByRoll(students, 0, count - 1, &c, &s);
                    sortedByRoll = true;
                }
                int roll;
                printf("Enter Roll Number to search: ");
                scanf("%d", &roll);
                long long comp = 0;
                int idx = binarySearchRoll(students, count, roll, &comp);
                if (idx != -1) {
                    printf("\n[FOUND] Student Record Found (in %lld comparison%s):\n", comp, comp == 1 ? "" : "s");
                    printf("  Roll No: %d\n", students[idx].rollNo);
                    printf("  Name:    %s\n", students[idx].name);
                    printf("  Marks:   %.2f%%\n", students[idx].marks);
                } else {
                    printf("[NOT FOUND] No student with Roll Number %d (Comparisons: %lld).\n", roll, comp);
                }
                break;
            }

            case 7: {
                char targetName[50];
                clearInputBuffer();
                printf("Enter student name to search: ");
                fgets(targetName, sizeof(targetName), stdin);
                targetName[strcspn(targetName, "\r\n")] = '\0';
                int idx = linearSearchName(students, count, targetName);
                if (idx != -1) {
                    printf("\n[FOUND] Record Match:\n");
                    printf("  Roll No: %d\n", students[idx].rollNo);
                    printf("  Name:    %s\n", students[idx].name);
                    printf("  Marks:   %.2f%%\n", students[idx].marks);
                } else {
                    printf("[NOT FOUND] No record matching name \"%s\".\n", targetName);
                }
                break;
            }

            case 8: {
                printf("\n================ COMPARATIVE PERFORMANCE REPORT ================\n");
                printf(" Dataset Size: %d student records\n", count);
                printf("----------------------------------------------------------------\n");
                printf(" Algorithm      | Key Field     | Time Complexity | Space Compl.\n");
                printf("----------------------------------------------------------------\n");
                printf(" Quick Sort     | Roll Number   | O(n log n) avg  | O(log n)\n");
                printf(" Merge Sort     | Marks (Merit) | O(n log n) best | O(n)\n");
                printf(" Insertion Sort | Student Name  | O(n^2) worst    | O(1)\n");
                printf(" Binary Search  | Roll Number   | O(log n)        | O(1)\n");
                printf(" Linear Search  | Student Name  | O(n)            | O(1)\n");
                printf("================================================================\n\n");
                break;
            }

            case 0:
                printf("\nExiting Student Record Manager. Goodbye!\n");
                break;

            default:
                printf("[ERROR] Invalid choice '%d'.\n", choice);
                break;
        }
    } while (choice != 0);

    return 0;
}

void clearInputBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void loadDefaultStudents(Student s[], int *n) {
    Student defaults[] = {
        {104, "Rahul Sharma", 88.5f},
        {101, "Aarav Gupta", 94.0f},
        {108, "Pooja Verma", 76.2f},
        {102, "Nandita Bais", 98.5f},
        {106, "Aditya Singh", 82.0f},
        {103, "Kavya Patel", 91.5f},
        {107, "Deepak Joshi", 68.0f},
        {105, "Sneha Reddy", 89.0f}
    };
    *n = sizeof(defaults) / sizeof(defaults[0]);
    for (int i = 0; i < *n; i++) {
        s[i] = defaults[i];
    }
}

void displayStudents(const Student s[], int n) {
    printf("\n+---------+---------------------------+---------+\n");
    printf("| Roll No | Student Name              | Marks   |\n");
    printf("+---------+---------------------------+---------+\n");
    for (int i = 0; i < n; i++) {
        printf("| %-7d | %-25s | %7.2f |\n", s[i].rollNo, s[i].name, s[i].marks);
    }
    printf("+---------+---------------------------+---------+\n");
    printf("Total Records: %d\n\n", n);
}

static void mergeSubarrays(Student s[], int l, int m, int r, long long *comp) {
    int n1 = m - l + 1;
    int n2 = r - m;

    Student *L = (Student *)malloc(n1 * sizeof(Student));
    Student *R = (Student *)malloc(n2 * sizeof(Student));

    for (int i = 0; i < n1; i++) L[i] = s[l + i];
    for (int j = 0; j < n2; j++) R[j] = s[m + 1 + j];

    int i = 0, j = 0, k = l;
    // Descending order for merit ranking
    while (i < n1 && j < n2) {
        (*comp)++;
        if (L[i].marks >= R[j].marks) {
            s[k++] = L[i++];
        } else {
            s[k++] = R[j++];
        }
    }
    while (i < n1) s[k++] = L[i++];
    while (j < n2) s[k++] = R[j++];

    free(L);
    free(R);
}

void mergeSortByMarks(Student s[], int l, int r, long long *comp) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSortByMarks(s, l, m, comp);
        mergeSortByMarks(s, m + 1, r, comp);
        mergeSubarrays(s, l, m, r, comp);
    }
}

static void swapStudents(Student *a, Student *b) {
    Student t = *a;
    *a = *b;
    *b = t;
}

static int partitionRoll(Student s[], int low, int high, long long *comp, long long *swaps) {
    int pivot = s[high].rollNo;
    int i = low - 1;

    for (int j = low; j < high; j++) {
        (*comp)++;
        if (s[j].rollNo <= pivot) {
            i++;
            swapStudents(&s[i], &s[j]);
            (*swaps)++;
        }
    }
    swapStudents(&s[i + 1], &s[high]);
    (*swaps)++;
    return i + 1;
}

void quickSortByRoll(Student s[], int low, int high, long long *comp, long long *swaps) {
    if (low < high) {
        int pi = partitionRoll(s, low, high, comp, swaps);
        quickSortByRoll(s, low, pi - 1, comp, swaps);
        quickSortByRoll(s, pi + 1, high, comp, swaps);
    }
}

void insertionSortByName(Student s[], int n, long long *comp, long long *shifts) {
    for (int i = 1; i < n; i++) {
        Student key = s[i];
        int j = i - 1;
        while (j >= 0) {
            (*comp)++;
            if (strcmp(s[j].name, key.name) > 0) {
                s[j + 1] = s[j];
                (*shifts)++;
                j--;
            } else {
                break;
            }
        }
        s[j + 1] = key;
    }
}

int binarySearchRoll(const Student s[], int n, int targetRoll, long long *comp) {
    int low = 0, high = n - 1;
    while (low <= high) {
        (*comp)++;
        int mid = low + (high - low) / 2;
        if (s[mid].rollNo == targetRoll) {
            return mid;
        } else if (s[mid].rollNo < targetRoll) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return -1;
}

int linearSearchName(const Student s[], int n, const char *targetName) {
    for (int i = 0; i < n; i++) {
        if (strstr(s[i].name, targetName) != NULL) {
            return i;
        }
    }
    return -1;
}
