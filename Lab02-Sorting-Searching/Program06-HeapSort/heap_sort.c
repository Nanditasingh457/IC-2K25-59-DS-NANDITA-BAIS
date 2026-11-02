/**
 * Course: IC-307D Data Structures and Algorithms LAB
 * Unit 2: Sorting & Searching Algorithms
 * Program 06: Heap Sort (Max-Heap Construction and Extraction)
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
    int temp = *a;
    *a = *b;
    *b = temp;
    totalSwaps++;
}

void heapify(int arr[], int n, int i, bool verbose) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n) {
        totalComparisons++;
        if (arr[left] > arr[largest]) {
            largest = left;
        }
    }

    if (right < n) {
        totalComparisons++;
        if (arr[right] > arr[largest]) {
            largest = right;
        }
    }

    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        if (verbose) {
            printf("Heapify adjustment: swapped index %d (%d) with index %d (%d)\n", i, arr[largest], largest, arr[i]);
        }
        heapify(arr, n, largest, verbose);
    }
}

void heapSort(int arr[], int n, bool verbose) {
    if (verbose) printf("\n--- Phase 1: Building Max-Heap ---\n");
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i, verbose);
    }

    if (verbose) {
        printf("Max-Heap built successfully: ");
        printArray(arr, n);
        printf("\n--- Phase 2: Extracting Root and Heapifying ---\n");
    }

    for (int i = n - 1; i > 0; i--) {
        swap(&arr[0], &arr[i]);
        if (verbose) {
            printf("Moved maximum (%d) to index %d: ", arr[i], i);
            printArray(arr, n);
        }
        heapify(arr, i, 0, verbose);
    }
}

int main(void) {
    int arr[MAX_SIZE];
    int n;

    printf("============================================================\n");
    printf("   IC-307D LAB 2 | Program 06: Heap Sort (Max-Heap)         \n");
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

    totalComparisons = 0;
    totalSwaps = 0;
    heapSort(arr, n, true);

    printf("\nFinal Sorted Array: ");
    printArray(arr, n);
    printf("\nPerformance Metrics:\n");
    printf("  Total Comparisons: %lld\n", totalComparisons);
    printf("  Total Swaps:       %lld\n", totalSwaps);
    printf("  Time Complexity:   Best O(n log n), Average O(n log n), Worst O(n log n)\n");
    printf("  Space Complexity:  O(1) Auxiliary (In-place)\n");

    return 0;
}
