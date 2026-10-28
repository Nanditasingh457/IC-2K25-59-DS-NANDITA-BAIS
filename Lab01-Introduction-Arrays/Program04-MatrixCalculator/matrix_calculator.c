/**
 * Course: IC-307D Data Structures and Algorithms LAB
 * Unit 1: Introduction to Data Structures & Arrays
 * Program 04: Matrix Calculator with Menu-Driven Interface
 * 
 * Operations Included:
 *   1. Matrix Addition (A + B)
 *   2. Matrix Subtraction (A - B)
 *   3. Matrix Multiplication (A x B)
 *   4. Matrix Transpose (A^T and B^T)
 *   5. Determinant for Small Matrices (2x2 and 3x3)
 *   6. Matrix Inverse for Small Matrices (2x2 and 3x3)
 *   7. Scalar Multiplication
 * 
 * Student Name: Nandita Bais
 * Roll Number: IC-2K25-59
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_DIM 10

// Function Prototypes
void printMatrix(int r, int c, const double mat[MAX_DIM][MAX_DIM], const char *name);
void inputMatrix(int *r, int *c, double mat[MAX_DIM][MAX_DIM], const char *name);
bool addMatrices(int r1, int c1, const double a[MAX_DIM][MAX_DIM], int r2, int c2, const double b[MAX_DIM][MAX_DIM], double res[MAX_DIM][MAX_DIM]);
bool subtractMatrices(int r1, int c1, const double a[MAX_DIM][MAX_DIM], int r2, int c2, const double b[MAX_DIM][MAX_DIM], double res[MAX_DIM][MAX_DIM]);
bool multiplyMatrices(int r1, int c1, const double a[MAX_DIM][MAX_DIM], int r2, int c2, const double b[MAX_DIM][MAX_DIM], int *rr, int *rc, double res[MAX_DIM][MAX_DIM]);
void transposeMatrix(int r, int c, const double a[MAX_DIM][MAX_DIM], double res[MAX_DIM][MAX_DIM]);
double determinant2x2(const double m[MAX_DIM][MAX_DIM]);
double determinant3x3(const double m[MAX_DIM][MAX_DIM]);
bool inverseSmallMatrix(int n, const double m[MAX_DIM][MAX_DIM], double inv[MAX_DIM][MAX_DIM]);
void clearInputBuffer(void);

int main(void) {
    double matA[MAX_DIM][MAX_DIM];
    double matB[MAX_DIM][MAX_DIM];
    double result[MAX_DIM][MAX_DIM];
    int rA = 0, cA = 0;
    int rB = 0, cB = 0;
    int resR = 0, resC = 0;
    int choice;

    printf("============================================================\n");
    printf("   IC-307D LAB 1 | Program 04: Matrix Calculator            \n");
    printf("   Student: Nandita Bais | Roll No: IC-2K25-59              \n");
    printf("============================================================\n\n");

    printf("--- Input Matrix A ---\n");
    inputMatrix(&rA, &cA, matA, "Matrix A");

    printf("\n--- Input Matrix B ---\n");
    inputMatrix(&rB, &cB, matB, "Matrix B");

    do {
        printf("\n================ MATRIX CALCULATOR MENU ================\n");
        printf(" 1. Display Current Matrices (A and B)\n");
        printf(" 2. Matrix Addition (A + B)\n");
        printf(" 3. Matrix Subtraction (A - B)\n");
        printf(" 4. Matrix Multiplication (A x B)\n");
        printf(" 5. Transpose of Matrix A\n");
        printf(" 6. Transpose of Matrix B\n");
        printf(" 7. Determinant of Matrix A (2x2 or 3x3)\n");
        printf(" 8. Determinant of Matrix B (2x2 or 3x3)\n");
        printf(" 9. Inverse of Matrix A (2x2 or 3x3)\n");
        printf("10. Inverse of Matrix B (2x2 or 3x3)\n");
        printf("11. Re-enter Matrix A\n");
        printf("12. Re-enter Matrix B\n");
        printf(" 0. Exit Calculator\n");
        printf("========================================================\n");
        printf("Enter your choice (0-12): ");

        if (scanf("%d", &choice) != 1) {
            printf("[ERROR] Invalid choice. Please enter a number.\n");
            clearInputBuffer();
            continue;
        }

        switch (choice) {
            case 1:
                printMatrix(rA, cA, matA, "Matrix A");
                printMatrix(rB, cB, matB, "Matrix B");
                break;

            case 2:
                if (addMatrices(rA, cA, matA, rB, cB, matB, result)) {
                    printMatrix(rA, cA, result, "Result: (A + B)");
                }
                break;

            case 3:
                if (subtractMatrices(rA, cA, matA, rB, cB, matB, result)) {
                    printMatrix(rA, cA, result, "Result: (A - B)");
                }
                break;

            case 4:
                if (multiplyMatrices(rA, cA, matA, rB, cB, matB, &resR, &resC, result)) {
                    printMatrix(resR, resC, result, "Result: (A x B)");
                }
                break;

            case 5:
                transposeMatrix(rA, cA, matA, result);
                printMatrix(cA, rA, result, "Transpose of Matrix A (A^T)");
                break;

            case 6:
                transposeMatrix(rB, cB, matB, result);
                printMatrix(cB, rB, result, "Transpose of Matrix B (B^T)");
                break;

            case 7:
                if (rA != cA || (rA != 2 && rA != 3)) {
                    printf("[ERROR] Determinant requires a 2x2 or 3x3 square matrix. Current A is %dx%d.\n", rA, cA);
                } else if (rA == 2) {
                    double det = determinant2x2(matA);
                    printf("\n[CALCULATION] Determinant of Matrix A (2x2) = %.4f\n", det);
                } else {
                    double det = determinant3x3(matA);
                    printf("\n[CALCULATION] Determinant of Matrix A (3x3) = %.4f\n", det);
                }
                break;

            case 8:
                if (rB != cB || (rB != 2 && rB != 3)) {
                    printf("[ERROR] Determinant requires a 2x2 or 3x3 square matrix. Current B is %dx%d.\n", rB, cB);
                } else if (rB == 2) {
                    double det = determinant2x2(matB);
                    printf("\n[CALCULATION] Determinant of Matrix B (2x2) = %.4f\n", det);
                } else {
                    double det = determinant3x3(matB);
                    printf("\n[CALCULATION] Determinant of Matrix B (3x3) = %.4f\n", det);
                }
                break;

            case 9:
                if (rA != cA || (rA != 2 && rA != 3)) {
                    printf("[ERROR] Matrix A must be 2x2 or 3x3 square matrix for inverse. Current A: %dx%d.\n", rA, cA);
                } else {
                    if (inverseSmallMatrix(rA, matA, result)) {
                        printMatrix(rA, cA, result, "Inverse of Matrix A (A^-1)");
                    }
                }
                break;

            case 10:
                if (rB != cB || (rB != 2 && rB != 3)) {
                    printf("[ERROR] Matrix B must be 2x2 or 3x3 square matrix for inverse. Current B: %dx%d.\n", rB, cB);
                } else {
                    if (inverseSmallMatrix(rB, matB, result)) {
                        printMatrix(rB, cB, result, "Inverse of Matrix B (B^-1)");
                    }
                }
                break;

            case 11:
                inputMatrix(&rA, &cA, matA, "Matrix A");
                break;

            case 12:
                inputMatrix(&rB, &cB, matB, "Matrix B");
                break;

            case 0:
                printf("\nExiting Matrix Calculator. Goodbye!\n");
                break;

            default:
                printf("[ERROR] Invalid choice '%d'. Please select 0 to 12.\n", choice);
                break;
        }
    } while (choice != 0);

    return 0;
}

void clearInputBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void printMatrix(int r, int c, const double mat[MAX_DIM][MAX_DIM], const char *name) {
    printf("\n[%s] (%d x %d):\n", name, r, c);
    for (int i = 0; i < r; i++) {
        printf("  | ");
        for (int j = 0; j < c; j++) {
            printf("%8.2f ", mat[i][j]);
        }
        printf("|\n");
    }
    printf("\n");
}

void inputMatrix(int *r, int *c, double mat[MAX_DIM][MAX_DIM], const char *name) {
    int rows, cols;
    printf("Enter number of rows for %s (1 to %d): ", name, MAX_DIM);
    while (scanf("%d", &rows) != 1 || rows < 1 || rows > MAX_DIM) {
        printf("[ERROR] Invalid. Enter rows between 1 and %d: ", MAX_DIM);
        clearInputBuffer();
    }
    printf("Enter number of columns for %s (1 to %d): ", name, MAX_DIM);
    while (scanf("%d", &cols) != 1 || cols < 1 || cols > MAX_DIM) {
        printf("[ERROR] Invalid. Enter columns between 1 and %d: ", MAX_DIM);
        clearInputBuffer();
    }
    *r = rows;
    *c = cols;

    printf("Enter %d values row by row:\n", rows * cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (scanf("%lf", &mat[i][j]) != 1) {
                printf("[ERROR] Bad input at (%d,%d). Defaulting to 0.0.\n", i, j);
                mat[i][j] = 0.0;
                clearInputBuffer();
            }
        }
    }
    printMatrix(*r, *c, mat, name);
}

bool addMatrices(int r1, int c1, const double a[MAX_DIM][MAX_DIM], int r2, int c2, const double b[MAX_DIM][MAX_DIM], double res[MAX_DIM][MAX_DIM]) {
    if (r1 != r2 || c1 != c2) {
        printf("[ERROR] Addition incompatible! Dimensions %dx%d and %dx%d must match exactly.\n", r1, c1, r2, c2);
        return false;
    }
    for (int i = 0; i < r1; i++) {
        for (int j = 0; j < c1; j++) {
            res[i][j] = a[i][j] + b[i][j];
        }
    }
    return true;
}

bool subtractMatrices(int r1, int c1, const double a[MAX_DIM][MAX_DIM], int r2, int c2, const double b[MAX_DIM][MAX_DIM], double res[MAX_DIM][MAX_DIM]) {
    if (r1 != r2 || c1 != c2) {
        printf("[ERROR] Subtraction incompatible! Dimensions %dx%d and %dx%d must match exactly.\n", r1, c1, r2, c2);
        return false;
    }
    for (int i = 0; i < r1; i++) {
        for (int j = 0; j < c1; j++) {
            res[i][j] = a[i][j] - b[i][j];
        }
    }
    return true;
}

bool multiplyMatrices(int r1, int c1, const double a[MAX_DIM][MAX_DIM], int r2, int c2, const double b[MAX_DIM][MAX_DIM], int *rr, int *rc, double res[MAX_DIM][MAX_DIM]) {
    if (c1 != r2) {
        printf("[ERROR] Multiplication incompatible! Columns of A (%d) must equal rows of B (%d).\n", c1, r2);
        return false;
    }
    *rr = r1;
    *rc = c2;

    for (int i = 0; i < r1; i++) {
        for (int j = 0; j < c2; j++) {
            res[i][j] = 0.0;
            for (int k = 0; k < c1; k++) {
                res[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    return true;
}

void transposeMatrix(int r, int c, const double a[MAX_DIM][MAX_DIM], double res[MAX_DIM][MAX_DIM]) {
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            res[j][i] = a[i][j];
        }
    }
}

double determinant2x2(const double m[MAX_DIM][MAX_DIM]) {
    return (m[0][0] * m[1][1]) - (m[0][1] * m[1][0]);
}

double determinant3x3(const double m[MAX_DIM][MAX_DIM]) {
    double a = m[0][0] * (m[1][1] * m[2][2] - m[1][2] * m[2][1]);
    double b = m[0][1] * (m[1][0] * m[2][2] - m[1][2] * m[2][0]);
    double c = m[0][2] * (m[1][0] * m[2][1] - m[1][1] * m[2][0]);
    return a - b + c;
}

bool inverseSmallMatrix(int n, const double m[MAX_DIM][MAX_DIM], double inv[MAX_DIM][MAX_DIM]) {
    if (n == 2) {
        double det = determinant2x2(m);
        if (det == 0.0) {
            printf("[SINGULAR MATRIX] Determinant is zero; inverse does not exist!\n");
            return false;
        }
        inv[0][0] =  m[1][1] / det;
        inv[0][1] = -m[0][1] / det;
        inv[1][0] = -m[1][0] / det;
        inv[1][1] =  m[0][0] / det;
        return true;
    } else if (n == 3) {
        double det = determinant3x3(m);
        if (det == 0.0) {
            printf("[SINGULAR MATRIX] Determinant is zero; inverse does not exist!\n");
            return false;
        }
        // Cofactor matrix transposed (Adjugate)
        inv[0][0] =  (m[1][1] * m[2][2] - m[1][2] * m[2][1]) / det;
        inv[0][1] = -(m[0][1] * m[2][2] - m[0][2] * m[2][1]) / det;
        inv[0][2] =  (m[0][1] * m[1][2] - m[0][2] * m[1][1]) / det;

        inv[1][0] = -(m[1][0] * m[2][2] - m[1][2] * m[2][0]) / det;
        inv[1][1] =  (m[0][0] * m[2][2] - m[0][2] * m[2][0]) / det;
        inv[1][2] = -(m[0][0] * m[1][2] - m[0][2] * m[1][0]) / det;

        inv[2][0] =  (m[1][0] * m[2][1] - m[1][1] * m[2][0]) / det;
        inv[2][1] = -(m[0][0] * m[2][1] - m[0][1] * m[2][0]) / det;
        inv[2][2] =  (m[0][0] * m[1][1] - m[0][1] * m[1][0]) / det;
        return true;
    }
    return false;
}
