/**
 * Course: IC-307D Data Structures and Algorithms LAB
 * Unit 2: Sorting & Searching Algorithms Analysis Suite
 * Benchmark: Empirical Execution Time Comparison of Sorting Algorithms
 * 
 * Compares:
 *   1. Bubble Sort
 *   2. Selection Sort
 *   3. Insertion Sort
 *   4. Merge Sort
 *   5. Quick Sort
 *   6. Heap Sort
 *   7. Radix Sort
 * 
 * Tested On:
 *   - Random Data
 *   - Sorted Data (Ascending)
 *   - Reverse-Sorted Data (Descending)
 *   - Sizes: 1000, 2500, 5000, 10000 elements
 * 
 * Student Name: Nandita Bais
 * Roll Number: IC-2K25-59
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>

// High-resolution timer for Windows
double getHighResTimeMs(LARGE_INTEGER start, LARGE_INTEGER end, LARGE_INTEGER freq) {
    return (double)(end.QuadPart - start.QuadPart) * 1000.0 / (double)freq.QuadPart;
}

// Sorting Algorithm Implementations

void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int swapped = 0;
        for (int j = 0; j < n - 1 - i; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = 1;
            }
        }
        if (!swapped) break;
    }
}

void selectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIdx]) minIdx = j;
        }
        if (minIdx != i) {
            int temp = arr[i];
            arr[i] = arr[minIdx];
            arr[minIdx] = temp;
        }
    }
}

void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

static void mergeSub(int arr[], int l, int m, int r, int temp[]) {
    int i = l, j = m + 1, k = l;
    while (i <= m && j <= r) {
        if (arr[i] <= arr[j]) temp[k++] = arr[i++];
        else temp[k++] = arr[j++];
    }
    while (i <= m) temp[k++] = arr[i++];
    while (j <= r) temp[k++] = arr[j++];
    for (i = l; i <= r; i++) arr[i] = temp[i];
}

static void mergeSortRec(int arr[], int l, int r, int temp[]) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSortRec(arr, l, m, temp);
        mergeSortRec(arr, m + 1, r, temp);
        mergeSub(arr, l, m, r, temp);
    }
}

void mergeSort(int arr[], int n) {
    int *temp = (int *)malloc(n * sizeof(int));
    if (temp) {
        mergeSortRec(arr, 0, n - 1, temp);
        free(temp);
    }
}

static int partition(int arr[], int low, int high) {
    // Median of three pivot choice to prevent O(n^2) stack blowup on sorted data
    int mid = low + (high - low) / 2;
    if (arr[mid] < arr[low]) { int t = arr[low]; arr[low] = arr[mid]; arr[mid] = t; }
    if (arr[high] < arr[low]) { int t = arr[low]; arr[low] = arr[high]; arr[high] = t; }
    if (arr[high] < arr[mid]) { int t = arr[mid]; arr[mid] = arr[high]; arr[high] = t; }
    int t = arr[mid]; arr[mid] = arr[high]; arr[high] = t;

    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            int temp = arr[i]; arr[i] = arr[j]; arr[j] = temp;
        }
    }
    int temp = arr[i + 1]; arr[i + 1] = arr[high]; arr[high] = temp;
    return i + 1;
}

static void quickSortRec(int arr[], int low, int high) {
    while (low < high) {
        int pi = partition(arr, low, high);
        if (pi - low < high - pi) {
            quickSortRec(arr, low, pi - 1);
            low = pi + 1;
        } else {
            quickSortRec(arr, pi + 1, high);
            high = pi - 1;
        }
    }
}

void quickSort(int arr[], int n) {
    quickSortRec(arr, 0, n - 1);
}

static void heapify(int arr[], int n, int i) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    if (l < n && arr[l] > arr[largest]) largest = l;
    if (r < n && arr[r] > arr[largest]) largest = r;
    if (largest != i) {
        int temp = arr[i]; arr[i] = arr[largest]; arr[largest] = temp;
        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) heapify(arr, n, i);
    for (int i = n - 1; i > 0; i--) {
        int temp = arr[0]; arr[0] = arr[i]; arr[i] = temp;
        heapify(arr, i, 0);
    }
}

static void countSortRadix(int arr[], int n, int exp, int output[]) {
    int count[10] = {0};
    for (int i = 0; i < n; i++) count[(arr[i] / exp) % 10]++;
    for (int i = 1; i < 10; i++) count[i] += count[i - 1];
    for (int i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }
    for (int i = 0; i < n; i++) arr[i] = output[i];
}

void radixSort(int arr[], int n) {
    int mx = arr[0];
    for (int i = 1; i < n; i++) if (arr[i] > mx) mx = arr[i];
    int *output = (int *)malloc(n * sizeof(int));
    if (!output) return;
    for (int exp = 1; mx / exp > 0; exp *= 10) {
        countSortRadix(arr, n, exp, output);
    }
    free(output);
}

// Data Generators
void generateData(int arr[], int n, const char *type) {
    if (strcmp(type, "Random") == 0) {
        for (int i = 0; i < n; i++) arr[i] = rand() % 50000;
    } else if (strcmp(type, "Sorted") == 0) {
        for (int i = 0; i < n; i++) arr[i] = i * 2;
    } else if (strcmp(type, "Reverse") == 0) {
        for (int i = 0; i < n; i++) arr[i] = (n - i) * 2;
    }
}

typedef void (*SortFunc)(int arr[], int n);

int main(void) {
    LARGE_INTEGER freq, start, end;
    QueryPerformanceFrequency(&freq);
    srand(42);

    int sizes[] = {1000, 2500, 5000, 10000};
    int numSizes = sizeof(sizes) / sizeof(sizes[0]);

    const char *types[] = {"Random", "Sorted", "Reverse"};
    int numTypes = 3;

    const char *algos[] = {
        "Bubble Sort", "Selection Sort", "Insertion Sort",
        "Merge Sort", "Quick Sort", "Heap Sort", "Radix Sort"
    };
    SortFunc funcs[] = {
        bubbleSort, selectionSort, insertionSort,
        mergeSort, quickSort, heapSort, radixSort
    };
    int numAlgos = 7;

    FILE *fp = fopen("benchmark_results.csv", "w");
    if (!fp) {
        printf("[ERROR] Failed to create benchmark_results.csv\n");
        return 1;
    }

    fprintf(fp, "Algorithm,DataType,Size,TimeMs\n");
    printf("========================================================================\n");
    printf("   IC-307D LAB 2 | Sorting Empirical Benchmark Suite                    \n");
    printf("   Student: Nandita Bais | Roll No: IC-2K25-59                          \n");
    printf("========================================================================\n\n");

    for (int t = 0; t < numTypes; t++) {
        printf("\n>>> Testing Input Type: %s <<<\n", types[t]);
        printf("%-16s | %-6s | %-12s\n", "Algorithm", "Size", "Time (ms)");
        printf("-----------------+--------+-------------\n");

        for (int s = 0; s < numSizes; s++) {
            int n = sizes[s];
            int *masterArr = (int *)malloc(n * sizeof(int));
            int *workArr = (int *)malloc(n * sizeof(int));

            generateData(masterArr, n, types[t]);

            for (int a = 0; a < numAlgos; a++) {
                memcpy(workArr, masterArr, n * sizeof(int));

                QueryPerformanceCounter(&start);
                funcs[a](workArr, n);
                QueryPerformanceCounter(&end);

                double ms = getHighResTimeMs(start, end, freq);
                fprintf(fp, "%s,%s,%d,%.4f\n", algos[a], types[t], n, ms);
                printf("%-16s | %-6d | %10.4f ms\n", algos[a], n, ms);
            }
            free(masterArr);
            free(workArr);
        }
    }

    fclose(fp);
    printf("\n[SUCCESS] Benchmark completed. Results saved to benchmark_results.csv\n");
    return 0;
}
