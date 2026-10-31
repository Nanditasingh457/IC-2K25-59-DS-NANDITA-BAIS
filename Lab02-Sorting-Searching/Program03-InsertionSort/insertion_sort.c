/**
 * Course: IC-307D Data Structures and Algorithms LAB
 * Unit 2: Sorting & Searching Algorithms
 * Program 03: Insertion Sort (With Pass Tracing and Metrics)
 * 
 * Student Name: Nandita Bais
 * Roll Number: IC-2K25-59
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 100

void printArray(const int arr[], int n) {
    printf("[ ");
    for (int i = 0; i < n; i++) {
        printf("%d%s", arr[i], (i == n - 1) ? "" : ", ");
    }
    printf(" ]\n");
}

void insertionSort(int arr[], int n, long long *comparisons, long long *shifts, bool verbose) {
    *comparisons = 0;
    *shifts = 0;

    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        if (verbose) printf("--- Pass %d: Inserting key = %d into sorted sub-array [0..%d] ---\n", i, key, i - 1);

        while (j >= 0) {
            (*comparisons)++;
            if (arr[j] > key) {
                arr[j + 1] = arr[j];
                (*shifts)++;
                j--;
            } else {
                break;
            }
        }
        arr[j + 1] = key;

        if (verbose) {
            printf("Array state after inserting key %d at position %d: ", key, j + 1);
            printArray(arr, n);
        }
    }
}

int main(void) {
    int arr[MAX_SIZE];
    int n;
    long long comparisons = 0, shifts = 0;

    printf("============================================================\n");
    printf("   IC-307D LAB 2 | Program 03: Insertion Sort               \n");
    printf("   Student: Nandita Bais | Roll No: IC-2K25-59              \n");
    printf("============================================================\n\n");

    printf("Enter number of elements (1 to %d): ", MAX_SIZE);
    if (scanf("%d", &n) != 1 || n < 1 || n > MAX_SIZE) {
        printf("[ERROR] Invalid array size.\n");
        return 1;
    }

    printf("Enter %d integers:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    printf("\nOriginal Array: ");
    printArray(arr, n);
    printf("\n--- Starting Insertion Sort Tracing ---\n");

    insertionSort(arr, n, &comparisons, &shifts, true);

    printf("\nFinal Sorted Array: ");
    printArray(arr, n);
    printf("\nPerformance Metrics:\n");
    printf("  Total Comparisons: %lld\n", comparisons);
    printf("  Total Shifts:      %lld\n", shifts);
    printf("  Time Complexity:   Best O(n), Average O(n^2), Worst O(n^2)\n");
    printf("  Space Complexity:  O(1) Auxiliary\n");

    return 0;
}
