/**
 * Course: IC-307D Data Structures and Algorithms LAB
 * Unit 2: Sorting & Searching Algorithms
 * Program 08: Binary Search (Iterative, Recursive, and Occurrence Bounds)
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

int binarySearchIterative(const int arr[], int n, int target, int *comparisons) {
    int low = 0;
    int high = n - 1;
    *comparisons = 0;

    printf("\n--- Iterative Binary Search Trace ---\n");
    while (low <= high) {
        (*comparisons)++;
        int mid = low + (high - low) / 2;
        printf("Checking range [%d..%d], mid = %d (value = %d)\n", low, high, mid, arr[mid]);

        if (arr[mid] == target) {
            return mid;
        } else if (arr[mid] < target) {
            printf("  Target %d > %d, searching right sub-array [%d..%d]\n", target, arr[mid], mid + 1, high);
            low = mid + 1;
        } else {
            printf("  Target %d < %d, searching left sub-array [%d..%d]\n", target, arr[mid], low, mid - 1);
            high = mid - 1;
        }
    }
    return -1;
}

int binarySearchRecursive(const int arr[], int low, int high, int target, int *comparisons) {
    if (low > high) return -1;

    (*comparisons)++;
    int mid = low + (high - low) / 2;

    if (arr[mid] == target) return mid;
    if (arr[mid] > target) return binarySearchRecursive(arr, low, mid - 1, target, comparisons);
    return binarySearchRecursive(arr, mid + 1, high, target, comparisons);
}

int findFirstOccurrence(const int arr[], int n, int target) {
    int low = 0, high = n - 1;
    int result = -1;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] == target) {
            result = mid;
            high = mid - 1; // Keep searching left for earlier occurrence
        } else if (arr[mid] < target) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return result;
}

int findLastOccurrence(const int arr[], int n, int target) {
    int low = 0, high = n - 1;
    int result = -1;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] == target) {
            result = mid;
            low = mid + 1; // Keep searching right for later occurrence
        } else if (arr[mid] < target) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return result;
}

static int compareInts(const void *a, const void *b) {
    return (*(const int *)a - *(const int *)b);
}

int main(void) {
    int arr[MAX_SIZE];
    int n, target;
    int iterComparisons = 0, recComparisons = 0;

    printf("============================================================\n");
    printf("   IC-307D LAB 2 | Program 08: Binary Search (Complete Suite)\n");
    printf("   Student: Nandita Bais | Roll No: IC-2K25-59              \n");
    printf("============================================================\n\n");

    printf("Enter number of elements (1 to %d): ", MAX_SIZE);
    if (scanf("%d", &n) != 1 || n < 1 || n > MAX_SIZE) {
        printf("[ERROR] Invalid array size.\n");
        return 1;
    }

    printf("Enter %d integers (will be auto-sorted for Binary Search):\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    // Sort to guarantee preconditions for binary search
    qsort(arr, n, sizeof(int), compareInts);

    printf("\nSorted Array for Binary Search: ");
    printArray(arr, n);

    printf("\nEnter target integer to search: ");
    if (scanf("%d", &target) != 1) {
        printf("[ERROR] Invalid target.\n");
        return 1;
    }

    int iterResult = binarySearchIterative(arr, n, target, &iterComparisons);
    int recResult = binarySearchRecursive(arr, 0, n - 1, target, &recComparisons);
    int firstIdx = findFirstOccurrence(arr, n, target);
    int lastIdx = findLastOccurrence(arr, n, target);

    printf("\n================ SEARCH RESULTS ================\n");
    if (iterResult != -1) {
        printf(" Status:           FOUND\n");
        printf(" Index (Iterative): %d (Comparisons: %d)\n", iterResult, iterComparisons);
        printf(" Index (Recursive): %d (Comparisons: %d)\n", recResult, recComparisons);
        printf(" First Occurrence:  Index %d\n", firstIdx);
        printf(" Last Occurrence:   Index %d\n", lastIdx);
        printf(" Total Frequency:   %d occurrence(s)\n", (lastIdx - firstIdx + 1));
    } else {
        printf(" Status:           NOT FOUND\n");
        printf(" Total Comparisons:%d\n", iterComparisons);
    }
    printf(" Time Complexity:  Best O(1), Average O(log n), Worst O(log n)\n");
    printf(" Space Complexity: Iterative O(1), Recursive O(log n)\n");
    printf("================================================\n");

    return 0;
}
