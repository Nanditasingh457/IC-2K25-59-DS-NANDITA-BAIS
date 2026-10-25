/**
 * Course: IC-307D Data Structures and Algorithms LAB
 * Unit 1: Introduction to Data Structures & Arrays
 * Program 02: 2D Array Operations (Insert, Delete, Search, Rotate, Spiral Traversal)
 * 
 * Student Name: Nandita Bais
 * Roll Number: IC-2K25-59
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_ROWS 10
#define MAX_COLS 10

// Function Prototypes
void displayMatrix(int rows, int cols, const int mat[MAX_ROWS][MAX_COLS]);
void inputMatrix(int *rows, int *cols, int mat[MAX_ROWS][MAX_COLS]);
bool insertRow(int *rows, int cols, int mat[MAX_ROWS][MAX_COLS], int rowIdx, const int newRow[]);
bool deleteRow(int *rows, int cols, int mat[MAX_ROWS][MAX_COLS], int rowIdx);
bool insertCol(int rows, int *cols, int mat[MAX_ROWS][MAX_COLS], int colIdx, const int newCol[]);
bool deleteCol(int rows, int *cols, int mat[MAX_ROWS][MAX_COLS], int colIdx);
bool searchElement(int rows, int cols, const int mat[MAX_ROWS][MAX_COLS], int target, int *foundR, int *foundC);
void rotate90Clockwise(int *rows, int *cols, int mat[MAX_ROWS][MAX_COLS]);
void rotate90CounterClockwise(int *rows, int *cols, int mat[MAX_ROWS][MAX_COLS]);
void spiralTraversal(int rows, int cols, const int mat[MAX_ROWS][MAX_COLS]);
void boundaryTraversal(int rows, int cols, const int mat[MAX_ROWS][MAX_COLS]);
void clearInputBuffer(void);

int main(void) {
    int mat[MAX_ROWS][MAX_COLS];
    int rows = 0, cols = 0;
    int choice;
    int tempArr[MAX_COLS > MAX_ROWS ? MAX_COLS : MAX_ROWS];
    int idx, target, foundR, foundC;

    printf("============================================================\n");
    printf("   IC-307D LAB 1 | Program 02: 2D Array Operations          \n");
    printf("   Student: Nandita Bais | Roll No: IC-2K25-59              \n");
    printf("============================================================\n\n");

    printf("Initialize the 2D Matrix:\n");
    inputMatrix(&rows, &cols, mat);

    do {
        printf("\n------------- 2D ARRAY OPERATIONS MENU -------------\n");
        printf(" 1. Display Current Matrix\n");
        printf(" 2. Re-input Entire Matrix\n");
        printf(" 3. Insert Row at Index\n");
        printf(" 4. Delete Row at Index\n");
        printf(" 5. Insert Column at Index\n");
        printf(" 6. Delete Column at Index\n");
        printf(" 7. Search for an Element\n");
        printf(" 8. Rotate 90 Degrees Clockwise\n");
        printf(" 9. Rotate 90 Degrees Counter-Clockwise\n");
        printf("10. Spiral Traversal\n");
        printf("11. Boundary Traversal\n");
        printf(" 0. Exit Program\n");
        printf("----------------------------------------------------\n");
        printf("Enter choice (0-11): ");

        if (scanf("%d", &choice) != 1) {
            printf("[ERROR] Invalid choice. Please enter a number.\n");
            clearInputBuffer();
            continue;
        }

        switch (choice) {
            case 1:
                displayMatrix(rows, cols, mat);
                break;

            case 2:
                inputMatrix(&rows, &cols, mat);
                break;

            case 3:
                if (rows >= MAX_ROWS) {
                    printf("[OVERFLOW] Maximum allowed rows (%d) reached.\n", MAX_ROWS);
                    break;
                }
                printf("Enter row index to insert at (0 to %d): ", rows);
                if (scanf("%d", &idx) == 1 && idx >= 0 && idx <= rows) {
                    printf("Enter %d values for the new row:\n", cols);
                    for (int j = 0; j < cols; j++) {
                        scanf("%d", &tempArr[j]);
                    }
                    if (insertRow(&rows, cols, mat, idx, tempArr)) {
                        printf("[SUCCESS] Row inserted at index %d.\n", idx);
                        displayMatrix(rows, cols, mat);
                    }
                } else {
                    printf("[ERROR] Invalid row index.\n");
                    clearInputBuffer();
                }
                break;

            case 4:
                if (rows <= 1) {
                    printf("[ERROR] Cannot delete the only remaining row.\n");
                    break;
                }
                printf("Enter row index to delete (0 to %d): ", rows - 1);
                if (scanf("%d", &idx) == 1 && idx >= 0 && idx < rows) {
                    if (deleteRow(&rows, cols, mat, idx)) {
                        printf("[SUCCESS] Row %d deleted.\n", idx);
                        displayMatrix(rows, cols, mat);
                    }
                } else {
                    printf("[ERROR] Invalid row index.\n");
                    clearInputBuffer();
                }
                break;

            case 5:
                if (cols >= MAX_COLS) {
                    printf("[OVERFLOW] Maximum allowed columns (%d) reached.\n", MAX_COLS);
                    break;
                }
                printf("Enter column index to insert at (0 to %d): ", cols);
                if (scanf("%d", &idx) == 1 && idx >= 0 && idx <= cols) {
                    printf("Enter %d values for the new column:\n", rows);
                    for (int i = 0; i < rows; i++) {
                        scanf("%d", &tempArr[i]);
                    }
                    if (insertCol(rows, &cols, mat, idx, tempArr)) {
                        printf("[SUCCESS] Column inserted at index %d.\n", idx);
                        displayMatrix(rows, cols, mat);
                    }
                } else {
                    printf("[ERROR] Invalid column index.\n");
                    clearInputBuffer();
                }
                break;

            case 6:
                if (cols <= 1) {
                    printf("[ERROR] Cannot delete the only remaining column.\n");
                    break;
                }
                printf("Enter column index to delete (0 to %d): ", cols - 1);
                if (scanf("%d", &idx) == 1 && idx >= 0 && idx < cols) {
                    if (deleteCol(rows, &cols, mat, idx)) {
                        printf("[SUCCESS] Column %d deleted.\n", idx);
                        displayMatrix(rows, cols, mat);
                    }
                } else {
                    printf("[ERROR] Invalid column index.\n");
                    clearInputBuffer();
                }
                break;

            case 7:
                printf("Enter element to search: ");
                if (scanf("%d", &target) == 1) {
                    if (searchElement(rows, cols, mat, target, &foundR, &foundC)) {
                        printf("[FOUND] Element %d located at Row %d, Column %d (0-indexed).\n", target, foundR, foundC);
                    } else {
                        printf("[NOT FOUND] Element %d does not exist in the matrix.\n", target);
                    }
                } else {
                    printf("[ERROR] Invalid input.\n");
                    clearInputBuffer();
                }
                break;

            case 8:
                rotate90Clockwise(&rows, &cols, mat);
                printf("[SUCCESS] Matrix rotated 90 degrees clockwise:\n");
                displayMatrix(rows, cols, mat);
                break;

            case 9:
                rotate90CounterClockwise(&rows, &cols, mat);
                printf("[SUCCESS] Matrix rotated 90 degrees counter-clockwise:\n");
                displayMatrix(rows, cols, mat);
                break;

            case 10:
                spiralTraversal(rows, cols, mat);
                break;

            case 11:
                boundaryTraversal(rows, cols, mat);
                break;

            case 0:
                printf("\nExiting Program 02. Goodbye!\n");
                break;

            default:
                printf("[ERROR] Unknown choice '%d'.\n", choice);
                break;
        }
    } while (choice != 0);

    return 0;
}

void clearInputBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void displayMatrix(int rows, int cols, const int mat[MAX_ROWS][MAX_COLS]) {
    if (rows <= 0 || cols <= 0) {
        printf("[MATRIX DISPLAY] Matrix is empty.\n");
        return;
    }
    printf("\n[MATRIX DISPLAY] Dimensions: %d x %d\n", rows, cols);
    for (int i = 0; i < rows; i++) {
        printf("  | ");
        for (int j = 0; j < cols; j++) {
            printf("%5d ", mat[i][j]);
        }
        printf("|\n");
    }
    printf("\n");
}

void inputMatrix(int *rows, int *cols, int mat[MAX_ROWS][MAX_COLS]) {
    int r, c;
    printf("Enter number of rows (1 to %d): ", MAX_ROWS);
    while (scanf("%d", &r) != 1 || r < 1 || r > MAX_ROWS) {
        printf("[ERROR] Invalid rows. Enter between 1 and %d: ", MAX_ROWS);
        clearInputBuffer();
    }
    printf("Enter number of columns (1 to %d): ", MAX_COLS);
    while (scanf("%d", &c) != 1 || c < 1 || c > MAX_COLS) {
        printf("[ERROR] Invalid columns. Enter between 1 and %d: ", MAX_COLS);
        clearInputBuffer();
    }

    *rows = r;
    *cols = c;

    printf("Enter the elements row-wise (%d x %d = %d elements):\n", r, c, r * c);
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            if (scanf("%d", &mat[i][j]) != 1) {
                printf("[ERROR] Bad input at (%d,%d). Setting to 0.\n", i, j);
                mat[i][j] = 0;
                clearInputBuffer();
            }
        }
    }
    displayMatrix(*rows, *cols, mat);
}

bool insertRow(int *rows, int cols, int mat[MAX_ROWS][MAX_COLS], int rowIdx, const int newRow[]) {
    if (*rows >= MAX_ROWS || rowIdx < 0 || rowIdx > *rows) return false;
    for (int i = *rows; i > rowIdx; i--) {
        for (int j = 0; j < cols; j++) {
            mat[i][j] = mat[i - 1][j];
        }
    }
    for (int j = 0; j < cols; j++) {
        mat[rowIdx][j] = newRow[j];
    }
    (*rows)++;
    return true;
}

bool deleteRow(int *rows, int cols, int mat[MAX_ROWS][MAX_COLS], int rowIdx) {
    if (*rows <= 0 || rowIdx < 0 || rowIdx >= *rows) return false;
    for (int i = rowIdx; i < *rows - 1; i++) {
        for (int j = 0; j < cols; j++) {
            mat[i][j] = mat[i + 1][j];
        }
    }
    (*rows)--;
    return true;
}

bool insertCol(int rows, int *cols, int mat[MAX_ROWS][MAX_COLS], int colIdx, const int newCol[]) {
    if (*cols >= MAX_COLS || colIdx < 0 || colIdx > *cols) return false;
    for (int j = *cols; j > colIdx; j--) {
        for (int i = 0; i < rows; i++) {
            mat[i][j] = mat[i][j - 1];
        }
    }
    for (int i = 0; i < rows; i++) {
        mat[i][colIdx] = newCol[i];
    }
    (*cols)++;
    return true;
}

bool deleteCol(int rows, int *cols, int mat[MAX_ROWS][MAX_COLS], int colIdx) {
    if (*cols <= 0 || colIdx < 0 || colIdx >= *cols) return false;
    for (int j = colIdx; j < *cols - 1; j++) {
        for (int i = 0; i < rows; i++) {
            mat[i][j] = mat[i][j + 1];
        }
    }
    (*cols)--;
    return true;
}

bool searchElement(int rows, int cols, const int mat[MAX_ROWS][MAX_COLS], int target, int *foundR, int *foundC) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (mat[i][j] == target) {
                *foundR = i;
                *foundC = j;
                return true;
            }
        }
    }
    return false;
}

void rotate90Clockwise(int *rows, int *cols, int mat[MAX_ROWS][MAX_COLS]) {
    int temp[MAX_ROWS][MAX_COLS];
    int newRows = *cols;
    int newCols = *rows;

    for (int i = 0; i < *rows; i++) {
        for (int j = 0; j < *cols; j++) {
            temp[j][*rows - 1 - i] = mat[i][j];
        }
    }
    *rows = newRows;
    *cols = newCols;
    for (int i = 0; i < *rows; i++) {
        for (int j = 0; j < *cols; j++) {
            mat[i][j] = temp[i][j];
        }
    }
}

void rotate90CounterClockwise(int *rows, int *cols, int mat[MAX_ROWS][MAX_COLS]) {
    int temp[MAX_ROWS][MAX_COLS];
    int newRows = *cols;
    int newCols = *rows;

    for (int i = 0; i < *rows; i++) {
        for (int j = 0; j < *cols; j++) {
            temp[*cols - 1 - j][i] = mat[i][j];
        }
    }
    *rows = newRows;
    *cols = newCols;
    for (int i = 0; i < *rows; i++) {
        for (int j = 0; j < *cols; j++) {
            mat[i][j] = temp[i][j];
        }
    }
}

void spiralTraversal(int rows, int cols, const int mat[MAX_ROWS][MAX_COLS]) {
    int top = 0, bottom = rows - 1;
    int left = 0, right = cols - 1;

    printf("\n[SPIRAL TRAVERSAL]:\n");
    while (top <= bottom && left <= right) {
        for (int j = left; j <= right; j++) {
            printf("%d ", mat[top][j]);
        }
        top++;

        for (int i = top; i <= bottom; i++) {
            printf("%d ", mat[i][right]);
        }
        right--;

        if (top <= bottom) {
            for (int j = right; j >= left; j--) {
                printf("%d ", mat[bottom][j]);
            }
            bottom--;
        }

        if (left <= right) {
            for (int i = bottom; i >= top; i--) {
                printf("%d ", mat[i][left]);
            }
            left++;
        }
    }
    printf("\n");
}

void boundaryTraversal(int rows, int cols, const int mat[MAX_ROWS][MAX_COLS]) {
    printf("\n[BOUNDARY TRAVERSAL]:\n");
    if (rows == 1) {
        for (int j = 0; j < cols; j++) printf("%d ", mat[0][j]);
    } else if (cols == 1) {
        for (int i = 0; i < rows; i++) printf("%d ", mat[i][0]);
    } else {
        for (int j = 0; j < cols; j++) printf("%d ", mat[0][j]);
        for (int i = 1; i < rows; i++) printf("%d ", mat[i][cols - 1]);
        for (int j = cols - 2; j >= 0; j--) printf("%d ", mat[rows - 1][j]);
        for (int i = rows - 2; i >= 1; i--) printf("%d ", mat[i][0]);
    }
    printf("\n");
}
