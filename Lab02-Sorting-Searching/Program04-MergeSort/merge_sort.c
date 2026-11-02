/**
 * Course: IC-307D Data Structures and Algorithms LAB
 * Unit 2: Sorting & Searching Algorithms
 * Program 04: Merge Sort (Divide and Conquer with Recursion Tracing)
 * 
 * Student Name: Nandita Bais
 * Roll Number: IC-2K25-59
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 100

static long long totalComparisons = 0;
static long long totalMerges = 0;

void printArray(const int arr[], int n) {
    printf("[ ");
    for (int i = 0; i < n; i++) {
        printf("%d%s", arr[i], (i == n - 1) ? "" : ", ");
    }
    printf(" ]\n");
}

void printSubArray(const int arr[], int left, int right) {
    printf("[ ");
    for (int i = left; i <= right; i++) {
        printf("%d%s", arr[i], (i == right) ? "" : ", ");
    }
    printf(" ]");
}

void merge(int arr[], int left, int mid, int right, bool verbose) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));

    if (!L || !R) {
        printf("[FATAL ERROR] Memory allocation failed during merge!\n");
        free(L);
        free(R);
        return;
    }

    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    totalMerges++;

    while (i < n1 && j < n2) {
        totalComparisons++;
        if (L[i] <= R[j]) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }

    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];

    if (verbose) {
        printf("Merged indices [%d..%d] and [%d..%d] -> Result: ", left, mid, mid + 1, right);
        printSubArray(arr, left, right);
        printf("\n");
    }

    free(L);
    free(R);
}

void mergeSort(int arr[], int left, int right, bool verbose) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        if (verbose) {
            printf("Dividing subarray [%d..%d] into [%d..%d] and [%d..%d]\n", left, right, left, mid, mid + 1, right);
        }

        mergeSort(arr, left, mid, verbose);
        mergeSort(arr, mid + 1, right, verbose);
        merge(arr, left, mid, right, verbose);
    }
}

int main(void) {
    int arr[MAX_SIZE];
    int n;

    printf("============================================================\n");
    printf("   IC-307D LAB 2 | Program 04: Merge Sort (Divide & Conquer)\n");
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
    printf("\n--- Starting Recursive Merge Sort Tracing ---\n");

    totalComparisons = 0;
    totalMerges = 0;
    mergeSort(arr, 0, n - 1, true);

    printf("\nFinal Sorted Array: ");
    printArray(arr, n);
    printf("\nPerformance Metrics:\n");
    printf("  Total Comparisons: %lld\n", totalComparisons);
    printf("  Total Merge Steps: %lld\n", totalMerges);
    printf("  Time Complexity:   Best O(n log n), Average O(n log n), Worst O(n log n)\n");
    printf("  Space Complexity:  O(n) Auxiliary Buffer\n");

    return 0;
}
