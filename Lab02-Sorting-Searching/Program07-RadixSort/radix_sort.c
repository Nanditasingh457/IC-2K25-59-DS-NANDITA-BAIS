/**
 * Course: IC-307D Data Structures and Algorithms LAB
 * Unit 2: Sorting & Searching Algorithms
 * Program 07: Radix Sort (LSD with Counting Sort Subroutine)
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

int getMax(const int arr[], int n) {
    int mx = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > mx) mx = arr[i];
    }
    return mx;
}

void countSortByDigit(int arr[], int n, int exp, bool verbose) {
    int *output = (int *)malloc(n * sizeof(int));
    int count[10] = {0};

    // Frequency of digits at current place
    for (int i = 0; i < n; i++) {
        int digit = (arr[i] / exp) % 10;
        count[digit]++;
    }

    // Cumulative frequency
    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }

    // Build output array stably in reverse
    for (int i = n - 1; i >= 0; i--) {
        int digit = (arr[i] / exp) % 10;
        output[count[digit] - 1] = arr[i];
        count[digit]--;
    }

    // Copy back
    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }

    if (verbose) {
        printf("State after sorting by place value %d: ", exp);
        printArray(arr, n);
    }

    free(output);
}

void radixSort(int arr[], int n, bool verbose) {
    int maxVal = getMax(arr, n);

    for (int exp = 1; maxVal / exp > 0; exp *= 10) {
        countSortByDigit(arr, n, exp, verbose);
    }
}

int main(void) {
    int arr[MAX_SIZE];
    int n;

    printf("============================================================\n");
    printf("   IC-307D LAB 2 | Program 07: Radix Sort (LSD)             \n");
    printf("   Student: Nandita Bais | Roll No: IC-2K25-59              \n");
    printf("============================================================\n\n");

    printf("Enter number of elements (1 to %d, non-negative): ", MAX_SIZE);
    if (scanf("%d", &n) != 1 || n < 1 || n > MAX_SIZE) {
        printf("[ERROR] Invalid array size.\n");
        return 1;
    }

    printf("Enter %d non-negative integers:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
        if (arr[i] < 0) {
            printf("[WARNING] Negative integer %d detected. Converting to absolute value.\n", arr[i]);
            arr[i] = abs(arr[i]);
        }
    }

    printf("\nOriginal Array: ");
    printArray(arr, n);
    printf("\n--- Starting Radix Sort Digit-by-Digit Passes ---\n");

    radixSort(arr, n, true);

    printf("\nFinal Sorted Array: ");
    printArray(arr, n);
    printf("\nPerformance Metrics:\n");
    printf("  Time Complexity:   O(d * (n + b)) where d = digits, b = base (10)\n");
    printf("  Space Complexity:  O(n + b) Auxiliary Buffer\n");
    printf("  Stability:         Stable Sorting Algorithm\n");

    return 0;
}
