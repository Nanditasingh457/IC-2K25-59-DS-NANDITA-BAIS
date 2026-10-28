/**
 * Course: IC-307D Data Structures and Algorithms LAB
 * Unit 1: Introduction to Data Structures & Arrays
 * Program 03: Sparse Matrix Representation (3-Tuple Format) and Operations
 * 
 * Operations Included:
 *   1. Standard Matrix to 3-Tuple (Triplet) Conversion
 *   2. Triplet Display
 *   3. Simple Transpose of Triplet Matrix
 *   4. Fast Transpose of Triplet Matrix - O(cols + non_zeros)
 *   5. Addition of Two Sparse Matrices in Triplet Form
 *   6. Space Optimization & Memory Savings Analysis
 * 
 * Student Name: Nandita Bais
 * Roll Number: IC-2K25-59
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_ELEMENTS 100
#define MAX_DIM 15

typedef struct {
    int row;
    int col;
    int val;
} Element;

// Function Prototypes
void displayTriplet(const Element t[], const char *title);
void convertToTriplet(int rows, int cols, const int mat[MAX_DIM][MAX_DIM], Element t[]);
void simpleTranspose(const Element a[], Element b[]);
void fastTranspose(const Element a[], Element b[]);
bool addSparse(const Element a[], const Element b[], Element c[]);
void analyzeSpaceSavings(const Element t[]);
void clearInputBuffer(void);

int main(void) {
    int mat1[MAX_DIM][MAX_DIM];
    int mat2[MAX_DIM][MAX_DIM];
    Element t1[MAX_ELEMENTS];
    Element t2[MAX_ELEMENTS];
    Element res[MAX_ELEMENTS];
    int r1, c1, r2, c2;
    int choice;

    printf("============================================================\n");
    printf("   IC-307D LAB 1 | Program 03: Sparse Matrix (3-Tuple)      \n");
    printf("   Student: Nandita Bais | Roll No: IC-2K25-59              \n");
    printf("============================================================\n\n");

    printf("Input Primary Matrix Dimensions (Rows Cols <= %d): ", MAX_DIM);
    while (scanf("%d %d", &r1, &c1) != 2 || r1 < 1 || r1 > MAX_DIM || c1 < 1 || c1 > MAX_DIM) {
        printf("[ERROR] Enter valid dimensions between 1 and %d: ", MAX_DIM);
        clearInputBuffer();
    }

    printf("Enter elements of Matrix 1 (%d x %d):\n", r1, c1);
    for (int i = 0; i < r1; i++) {
        for (int j = 0; j < c1; j++) {
            scanf("%d", &mat1[i][j]);
        }
    }

    convertToTriplet(r1, c1, mat1, t1);
    displayTriplet(t1, "Matrix 1 (Triplet Representation)");

    do {
        printf("\n------------- SPARSE MATRIX OPERATIONS MENU -------------\n");
        printf(" 1. Display Current Triplet Representation\n");
        printf(" 2. Simple Transpose - O(Cols * Non-Zeros)\n");
        printf(" 3. Fast Transpose - O(Cols + Non-Zeros)\n");
        printf(" 4. Add Another Sparse Matrix\n");
        printf(" 5. Space Optimization & Memory Analysis\n");
        printf(" 6. Re-enter Primary Matrix\n");
        printf(" 0. Exit Program\n");
        printf("---------------------------------------------------------\n");
        printf("Enter your choice (0-6): ");

        if (scanf("%d", &choice) != 1) {
            printf("[ERROR] Please enter a valid numerical choice.\n");
            clearInputBuffer();
            continue;
        }

        switch (choice) {
            case 1:
                displayTriplet(t1, "Matrix 1 Triplet");
                break;

            case 2: {
                Element transSimple[MAX_ELEMENTS];
                simpleTranspose(t1, transSimple);
                displayTriplet(transSimple, "Simple Transpose Result");
                break;
            }

            case 3: {
                Element transFast[MAX_ELEMENTS];
                fastTranspose(t1, transFast);
                displayTriplet(transFast, "Fast Transpose Result");
                break;
            }

            case 4: {
                printf("Enter dimensions for Matrix 2 (Must be %d x %d for addition): ", r1, c1);
                scanf("%d %d", &r2, &c2);
                if (r1 != r2 || c1 != c2) {
                    printf("[ERROR] Dimension mismatch! Matrix 1 is %dx%d, cannot add with %dx%d.\n", r1, c1, r2, c2);
                    break;
                }
                printf("Enter elements of Matrix 2 (%d x %d):\n", r2, c2);
                for (int i = 0; i < r2; i++) {
                    for (int j = 0; j < c2; j++) {
                        scanf("%d", &mat2[i][j]);
                    }
                }
                convertToTriplet(r2, c2, mat2, t2);
                displayTriplet(t2, "Matrix 2 Triplet");

                if (addSparse(t1, t2, res)) {
                    displayTriplet(res, "Sum Matrix (Triplet Form)");
                }
                break;
            }

            case 5:
                analyzeSpaceSavings(t1);
                break;

            case 6:
                printf("Input new Primary Matrix Dimensions (Rows Cols): ");
                scanf("%d %d", &r1, &c1);
                printf("Enter elements of Matrix 1 (%d x %d):\n", r1, c1);
                for (int i = 0; i < r1; i++) {
                    for (int j = 0; j < c1; j++) {
                        scanf("%d", &mat1[i][j]);
                    }
                }
                convertToTriplet(r1, c1, mat1, t1);
                displayTriplet(t1, "Updated Matrix 1 Triplet");
                break;

            case 0:
                printf("\nExiting Program 03. Goodbye!\n");
                break;

            default:
                printf("[ERROR] Invalid selection '%d'. Please select 0-6.\n", choice);
                break;
        }
    } while (choice != 0);

    return 0;
}

void clearInputBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void convertToTriplet(int rows, int cols, const int mat[MAX_DIM][MAX_DIM], Element t[]) {
    int count = 0;
    // Row 0 stores meta-information: total rows, total cols, total non-zeros
    t[0].row = rows;
    t[0].col = cols;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (mat[i][j] != 0) {
                count++;
                if (count >= MAX_ELEMENTS) {
                    printf("[WARNING] Exceeded maximum triplet capacity!\n");
                    break;
                }
                t[count].row = i;
                t[count].col = j;
                t[count].val = mat[i][j];
            }
        }
    }
    t[0].val = count;
}

void displayTriplet(const Element t[], const char *title) {
    printf("\n===============================================\n");
    printf("   %s\n", title);
    printf("===============================================\n");
    printf("   Index |  Row  |  Column  |   Value         \n");
    printf("-----------------------------------------------\n");
    printf("   [0]   | %5d | %8d | %7d  (Meta)\n", t[0].row, t[0].col, t[0].val);
    printf("-----------------------------------------------\n");
    for (int i = 1; i <= t[0].val; i++) {
        printf("   [%2d]  | %5d | %8d | %7d\n", i, t[i].row, t[i].col, t[i].val);
    }
    printf("===============================================\n");
    printf("Total non-zero elements: %d\n\n", t[0].val);
}

void simpleTranspose(const Element a[], Element b[]) {
    b[0].row = a[0].col;
    b[0].col = a[0].row;
    b[0].val = a[0].val;

    int totalNonZero = a[0].val;
    int currentB = 1;

    if (totalNonZero <= 0) return;

    for (int c = 0; c < a[0].col; c++) {
        for (int i = 1; i <= totalNonZero; i++) {
            if (a[i].col == c) {
                b[currentB].row = a[i].col;
                b[currentB].col = a[i].row;
                b[currentB].val = a[i].val;
                currentB++;
            }
        }
    }
}

void fastTranspose(const Element a[], Element b[]) {
    int totalCols = a[0].col;
    int totalNonZero = a[0].val;

    b[0].row = a[0].col;
    b[0].col = a[0].row;
    b[0].val = totalNonZero;

    if (totalNonZero <= 0) return;

    int rowTerms[MAX_DIM] = {0};
    int startingPos[MAX_DIM] = {0};

    // Frequency of each column
    for (int i = 1; i <= totalNonZero; i++) {
        rowTerms[a[i].col]++;
    }

    startingPos[0] = 1;
    for (int i = 1; i < totalCols; i++) {
        startingPos[i] = startingPos[i - 1] + rowTerms[i - 1];
    }

    // Direct placement into target positions
    for (int i = 1; i <= totalNonZero; i++) {
        int col = a[i].col;
        int dest = startingPos[col]++;
        b[dest].row = a[i].col;
        b[dest].col = a[i].row;
        b[dest].val = a[i].val;
    }
}

bool addSparse(const Element a[], const Element b[], Element c[]) {
    if (a[0].row != b[0].row || a[0].col != b[0].col) {
        printf("[ERROR] Dimension mismatch in sparse addition!\n");
        return false;
    }

    c[0].row = a[0].row;
    c[0].col = a[0].col;

    int i = 1, j = 1, k = 1;
    int numA = a[0].val;
    int numB = b[0].val;

    while (i <= numA && j <= numB) {
        if (a[i].row < b[j].row || (a[i].row == b[j].row && a[i].col < b[j].col)) {
            c[k++] = a[i++];
        } else if (b[j].row < a[i].row || (b[j].row == a[i].row && b[j].col < a[i].col)) {
            c[k++] = b[j++];
        } else {
            int sum = a[i].val + b[j].val;
            if (sum != 0) {
                c[k].row = a[i].row;
                c[k].col = a[i].col;
                c[k].val = sum;
                k++;
            }
            i++;
            j++;
        }
    }

    while (i <= numA) c[k++] = a[i++];
    while (j <= numB) c[k++] = b[j++];

    c[0].val = k - 1;
    return true;
}

void analyzeSpaceSavings(const Element t[]) {
    int rows = t[0].row;
    int cols = t[0].col;
    int nonZeros = t[0].val;
    int totalElements = rows * cols;

    size_t standardBytes = (size_t)totalElements * sizeof(int);
    // 3 ints per triplet entry, plus 1 meta entry
    size_t tripletBytes = (size_t)(nonZeros + 1) * 3 * sizeof(int);

    double sparsityPercentage = ((double)(totalElements - nonZeros) / totalElements) * 100.0;
    double savings = ((double)(standardBytes - tripletBytes) / standardBytes) * 100.0;

    printf("\n============== SPACE OPTIMIZATION ANALYSIS ==============\n");
    printf(" Matrix Dimensions          : %d x %d (%d total cells)\n", rows, cols, totalElements);
    printf(" Non-zero Elements          : %d\n", nonZeros);
    printf(" Zero Elements              : %d\n", totalElements - nonZeros);
    printf(" Sparsity Level             : %.2f%%\n", sparsityPercentage);
    printf(" Standard Matrix Memory     : %zu bytes\n", standardBytes);
    printf(" Triplet Format Memory      : %zu bytes\n", tripletBytes);
    if (savings > 0) {
        printf(" Net Memory Saved           : %zu bytes (%.2f%% reduction)\n", standardBytes - tripletBytes, savings);
        printf(" Status                     : SPARSE STORAGE HIGHLY EFFECTIVE\n");
    } else {
        printf(" Net Memory Overhead        : %zu bytes extra (Sparse storage not beneficial for dense matrices)\n", tripletBytes - standardBytes);
        printf(" Status                     : DENSE MATRIX (Standard storage preferred)\n");
    }
    printf("=========================================================\n\n");
}
