/**
 * Course: IC-307D Data Structures and Algorithms LAB
 * Unit 2: Sorting & Searching Algorithms
 * Program 02: Selection Sort (With Pass Tracing and Metrics)
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

void selectionSort(int arr[], int n, long long *comparisons, long long *swaps, bool verbose) {
    *comparisons = 0;
    *swaps = 0;

    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        if (verbose) printf("--- Pass %d: Searching minimum from index %d to %d ---\n", i + 1, i, n - 1);

        for (int j = i + 1; j < n; j++) {
            (*comparisons)++;
            if (arr[j] < arr[minIdx]) {
                minIdx = j;
            }
        }

        if (minIdx != i) {
            int temp = arr[i];
            arr[i] = arr[minIdx];
            arr[minIdx] = temp;
            (*swaps)++;
            if (verbose) printf("Swapped element %d at index %d with minimum %d at index %d.\n", arr[minIdx], i, arr[i], minIdx);
        } else {
            if (verbose) printf("Element %d at index %d is already in correct minimum position.\n", arr[i], i);
        }

        if (verbose) {
            printf("Array state after Pass %d: ", i + 1);
            printArray(arr, n);
        }
    }
}

int main(void) {
    int arr[MAX_SIZE];
    int n;
    long long comparisons = 0, swaps = 0;

    printf("============================================================\n");
    printf("   IC-307D LAB 2 | Program 02: Selection Sort               \n");
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
    printf("\n--- Starting Selection Sort Tracing ---\n");

    selectionSort(arr, n, &comparisons, &swaps, true);

    printf("\nFinal Sorted Array: ");
    printArray(arr, n);
    printf("\nPerformance Metrics:\n");
    printf("  Total Comparisons: %lld\n", comparisons);
    printf("  Total Swaps:       %lld\n", swaps);
    printf("  Time Complexity:   Best O(n^2), Average O(n^2), Worst O(n^2)\n");
    printf("  Space Complexity:  O(1) Auxiliary\n");

    return 0;
}
