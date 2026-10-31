/**
 * Course: IC-307D Data Structures and Algorithms LAB
 * Unit 2: Sorting & Searching Algorithms
 * Program 01: Bubble Sort (Optimized with Pass Tracing)
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

void bubbleSort(int arr[], int n, long long *comparisons, long long *swaps, bool verbose) {
    *comparisons = 0;
    *swaps = 0;

    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;
        if (verbose) printf("--- Pass %d ---\n", i + 1);

        for (int j = 0; j < n - 1 - i; j++) {
            (*comparisons)++;
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                (*swaps)++;
                swapped = true;
            }
        }

        if (verbose) {
            printf("State after Pass %d: ", i + 1);
            printArray(arr, n);
        }

        // Early exit optimization for already sorted arrays
        if (!swapped) {
            if (verbose) printf("Optimization Triggered: No swaps occurred in pass %d. Array is fully sorted!\n", i + 1);
            break;
        }
    }
}

int main(void) {
    int arr[MAX_SIZE];
    int n;
    long long comparisons = 0, swaps = 0;

    printf("============================================================\n");
    printf("   IC-307D LAB 2 | Program 01: Bubble Sort (Optimized)      \n");
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
    printf("\n--- Starting Bubble Sort Tracing ---\n");

    bubbleSort(arr, n, &comparisons, &swaps, true);

    printf("\nFinal Sorted Array: ");
    printArray(arr, n);
    printf("\nPerformance Metrics:\n");
    printf("  Total Comparisons: %lld\n", comparisons);
    printf("  Total Swaps:       %lld\n", swaps);
    printf("  Time Complexity:   Best O(n), Average O(n^2), Worst O(n^2)\n");
    printf("  Space Complexity:  O(1) Auxiliary\n");

    return 0;
}
