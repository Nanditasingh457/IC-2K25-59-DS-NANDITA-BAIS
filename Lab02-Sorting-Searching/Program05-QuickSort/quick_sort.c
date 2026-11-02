/**
 * Course: IC-307D Data Structures and Algorithms LAB
 * Unit 2: Sorting & Searching Algorithms
 * Program 05: Quick Sort (Partitioning, Pivot Analysis, Recursion Tracing)
 * 
 * Student Name: Nandita Bais
 * Roll Number: IC-2K25-59
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 100

static long long totalComparisons = 0;
static long long totalSwaps = 0;

void printArray(const int arr[], int n) {
    printf("[ ");
    for (int i = 0; i < n; i++) {
        printf("%d%s", arr[i], (i == n - 1) ? "" : ", ");
    }
    printf(" ]\n");
}

static void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
    totalSwaps++;
}

int partition(int arr[], int low, int high, bool verbose) {
    int pivot = arr[high]; // Last element as pivot
    int i = low - 1;

    if (verbose) {
        printf("Partitioning subarray [%d..%d] with Pivot = %d\n", low, high, pivot);
    }

    for (int j = low; j < high; j++) {
        totalComparisons++;
        if (arr[j] <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);

    if (verbose) {
        printf("Pivot placed at index %d -> Subarray state: ", i + 1);
        printArray(arr, high + 1);
    }

    return i + 1;
}

void quickSort(int arr[], int low, int high, bool verbose) {
    if (low < high) {
        int pi = partition(arr, low, high, verbose);
        quickSort(arr, low, pi - 1, verbose);
        quickSort(arr, pi + 1, high, verbose);
    }
}

int main(void) {
    int arr[MAX_SIZE];
    int n;

    printf("============================================================\n");
    printf("   IC-307D LAB 2 | Program 05: Quick Sort (Partitioning)    \n");
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
    printf("\n--- Starting Quick Sort Tracing ---\n");

    totalComparisons = 0;
    totalSwaps = 0;
    quickSort(arr, 0, n - 1, true);

    printf("\nFinal Sorted Array: ");
    printArray(arr, n);
    printf("\nPerformance Metrics:\n");
    printf("  Total Comparisons: %lld\n", totalComparisons);
    printf("  Total Swaps:       %lld\n", totalSwaps);
    printf("  Time Complexity:   Best O(n log n), Average O(n log n), Worst O(n^2)\n");
    printf("  Space Complexity:  O(log n) Recursive Call Stack\n");

    return 0;
}
