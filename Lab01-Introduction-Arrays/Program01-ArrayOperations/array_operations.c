/**
 * Course: IC-307D Data Structures and Algorithms LAB
 * Unit 1: Introduction to Data Structures & Arrays
 * Program 01: 1D Array Operations (Insert, Delete, Search, Rotate, Reverse)
 * 
 * Student Name: Nandita Bais
 * Roll Number: IC-2K25-59
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_CAPACITY 100

// Function Prototypes
void displayArray(const int arr[], int size);
bool insertAtPosition(int arr[], int *size, int capacity, int element, int position);
bool insertAtBeginning(int arr[], int *size, int capacity, int element);
bool insertAtEnd(int arr[], int *size, int capacity, int element);
bool deleteByIndex(int arr[], int *size, int index, int *deletedValue);
bool deleteByValue(int arr[], int *size, int value);
int linearSearch(const int arr[], int size, int target);
int binarySearch(const int arr[], int size, int target);
void rotateLeft(int arr[], int size, int k);
void rotateRight(int arr[], int size, int k);
void reverseArray(int arr[], int size);
bool isSorted(const int arr[], int size);
void clearInputBuffer(void);

int main(void) {
    int arr[MAX_CAPACITY];
    int size = 0;
    int choice;
    int val, pos, index, k;

    printf("============================================================\n");
    printf("   IC-307D LAB 1 | Program 01: 1D Array Operations          \n");
    printf("   Student: Nandita Bais | Roll No: IC-2K25-59              \n");
    printf("============================================================\n\n");

    // Initialize with user-defined initial size
    printf("Enter initial number of elements (0 to %d): ", MAX_CAPACITY);
    if (scanf("%d", &size) != 1 || size < 0 || size > MAX_CAPACITY) {
        printf("[ERROR] Invalid initial size! Initializing empty array.\n");
        clearInputBuffer();
        size = 0;
    } else if (size > 0) {
        printf("Enter %d integers separated by spaces:\n", size);
        for (int i = 0; i < size; i++) {
            if (scanf("%d", &arr[i]) != 1) {
                printf("[ERROR] Invalid input at element %d. Setting to 0.\n", i);
                arr[i] = 0;
                clearInputBuffer();
            }
        }
    }

    do {
        printf("\n------------- 1D ARRAY OPERATIONS MENU -------------\n");
        printf(" 1. Display Array\n");
        printf(" 2. Insert Element at Beginning\n");
        printf(" 3. Insert Element at End\n");
        printf(" 4. Insert Element at Specific Position (0 to size)\n");
        printf(" 5. Delete Element by Index\n");
        printf(" 6. Delete First Occurrence of Value\n");
        printf(" 7. Linear Search for an Element\n");
        printf(" 8. Binary Search (Requires Sorted Array)\n");
        printf(" 9. Left Rotate by K Positions\n");
        printf("10. Right Rotate by K Positions\n");
        printf("11. Reverse Array\n");
        printf(" 0. Exit Program\n");
        printf("----------------------------------------------------\n");
        printf("Enter your choice (0-11): ");

        if (scanf("%d", &choice) != 1) {
            printf("[ERROR] Invalid choice. Please enter a valid number.\n");
            clearInputBuffer();
            continue;
        }

        switch (choice) {
            case 1:
                displayArray(arr, size);
                break;

            case 2:
                printf("Enter value to insert at beginning: ");
                if (scanf("%d", &val) == 1) {
                    if (insertAtBeginning(arr, &size, MAX_CAPACITY, val)) {
                        printf("[SUCCESS] Inserted %d at beginning.\n", val);
                        displayArray(arr, size);
                    }
                } else {
                    printf("[ERROR] Invalid integer value.\n");
                    clearInputBuffer();
                }
                break;

            case 3:
                printf("Enter value to insert at end: ");
                if (scanf("%d", &val) == 1) {
                    if (insertAtEnd(arr, &size, MAX_CAPACITY, val)) {
                        printf("[SUCCESS] Inserted %d at end.\n", val);
                        displayArray(arr, size);
                    }
                } else {
                    printf("[ERROR] Invalid integer value.\n");
                    clearInputBuffer();
                }
                break;

            case 4:
                printf("Enter position (0 to %d): ", size);
                if (scanf("%d", &pos) == 1) {
                    printf("Enter value to insert: ");
                    if (scanf("%d", &val) == 1) {
                        if (insertAtPosition(arr, &size, MAX_CAPACITY, val, pos)) {
                            printf("[SUCCESS] Inserted %d at position %d.\n", val, pos);
                            displayArray(arr, size);
                        }
                    } else {
                        printf("[ERROR] Invalid value.\n");
                        clearInputBuffer();
                    }
                } else {
                    printf("[ERROR] Invalid position.\n");
                    clearInputBuffer();
                }
                break;

            case 5:
                if (size == 0) {
                    printf("[ERROR] Array is empty (Underflow)!\n");
                    break;
                }
                printf("Enter index to delete (0 to %d): ", size - 1);
                if (scanf("%d", &index) == 1) {
                    int deletedVal;
                    if (deleteByIndex(arr, &size, index, &deletedVal)) {
                        printf("[SUCCESS] Deleted element %d from index %d.\n", deletedVal, index);
                        displayArray(arr, size);
                    }
                } else {
                    printf("[ERROR] Invalid index.\n");
                    clearInputBuffer();
                }
                break;

            case 6:
                if (size == 0) {
                    printf("[ERROR] Array is empty!\n");
                    break;
                }
                printf("Enter value to delete: ");
                if (scanf("%d", &val) == 1) {
                    if (deleteByValue(arr, &size, val)) {
                        printf("[SUCCESS] Element %d found and deleted.\n", val);
                        displayArray(arr, size);
                    } else {
                        printf("[NOT FOUND] Element %d does not exist in array.\n", val);
                    }
                } else {
                    printf("[ERROR] Invalid value.\n");
                    clearInputBuffer();
                }
                break;

            case 7:
                if (size == 0) {
                    printf("[INFO] Array is empty.\n");
                    break;
                }
                printf("Enter target value for Linear Search: ");
                if (scanf("%d", &val) == 1) {
                    int foundIndex = linearSearch(arr, size, val);
                    if (foundIndex != -1) {
                        printf("[FOUND] Element %d found at index %d (0-indexed position %d).\n", val, foundIndex, foundIndex);
                    } else {
                        printf("[NOT FOUND] Element %d is not in the array.\n", val);
                    }
                } else {
                    printf("[ERROR] Invalid input.\n");
                    clearInputBuffer();
                }
                break;

            case 8:
                if (size == 0) {
                    printf("[INFO] Array is empty.\n");
                    break;
                }
                if (!isSorted(arr, size)) {
                    printf("[WARNING] Array is not sorted in ascending order. Binary Search requires sorted array.\n");
                    printf("Please sort the array first or use Linear Search.\n");
                    break;
                }
                printf("Enter target value for Binary Search: ");
                if (scanf("%d", &val) == 1) {
                    int foundIndex = binarySearch(arr, size, val);
                    if (foundIndex != -1) {
                        printf("[FOUND] Element %d found at index %d via Binary Search.\n", val, foundIndex);
                    } else {
                        printf("[NOT FOUND] Element %d is not present in the array.\n", val);
                    }
                } else {
                    printf("[ERROR] Invalid input.\n");
                    clearInputBuffer();
                }
                break;

            case 9:
                if (size == 0) {
                    printf("[INFO] Array is empty.\n");
                    break;
                }
                printf("Enter number of positions to rotate left (k): ");
                if (scanf("%d", &k) == 1) {
                    rotateLeft(arr, size, k);
                    printf("[SUCCESS] Array rotated left by %d positions.\n", k);
                    displayArray(arr, size);
                } else {
                    printf("[ERROR] Invalid rotation count.\n");
                    clearInputBuffer();
                }
                break;

            case 10:
                if (size == 0) {
                    printf("[INFO] Array is empty.\n");
                    break;
                }
                printf("Enter number of positions to rotate right (k): ");
                if (scanf("%d", &k) == 1) {
                    rotateRight(arr, size, k);
                    printf("[SUCCESS] Array rotated right by %d positions.\n", k);
                    displayArray(arr, size);
                } else {
                    printf("[ERROR] Invalid rotation count.\n");
                    clearInputBuffer();
                }
                break;

            case 11:
                if (size == 0) {
                    printf("[INFO] Array is empty.\n");
                    break;
                }
                reverseArray(arr, size);
                printf("[SUCCESS] Array reversed successfully.\n");
                displayArray(arr, size);
                break;

            case 0:
                printf("\nExiting Program 01. Thank you!\n");
                break;

            default:
                printf("[ERROR] Unknown option '%d'. Enter a choice from 0 to 11.\n", choice);
                break;
        }
    } while (choice != 0);

    return 0;
}

// Function implementations

void clearInputBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void displayArray(const int arr[], int size) {
    if (size == 0) {
        printf("[ARRAY DISPLAY] Array is currently empty: [ ]\n");
        return;
    }
    printf("[ARRAY DISPLAY] Size = %d/%d Elements: [ ", size, MAX_CAPACITY);
    for (int i = 0; i < size; i++) {
        printf("%d%s", arr[i], (i == size - 1) ? "" : ", ");
    }
    printf(" ]\n");
}

bool insertAtPosition(int arr[], int *size, int capacity, int element, int position) {
    if (*size >= capacity) {
        printf("[OVERFLOW] Cannot insert. Maximum capacity (%d) reached.\n", capacity);
        return false;
    }
    if (position < 0 || position > *size) {
        printf("[INVALID INDEX] Position %d out of valid range [0, %d].\n", position, *size);
        return false;
    }
    for (int i = *size; i > position; i--) {
        arr[i] = arr[i - 1];
    }
    arr[position] = element;
    (*size)++;
    return true;
}

bool insertAtBeginning(int arr[], int *size, int capacity, int element) {
    return insertAtPosition(arr, size, capacity, element, 0);
}

bool insertAtEnd(int arr[], int *size, int capacity, int element) {
    return insertAtPosition(arr, size, capacity, element, *size);
}

bool deleteByIndex(int arr[], int *size, int index, int *deletedValue) {
    if (*size <= 0) {
        printf("[UNDERFLOW] Cannot delete from empty array.\n");
        return false;
    }
    if (index < 0 || index >= *size) {
        printf("[INVALID INDEX] Index %d is out of bounds [0, %d].\n", index, *size - 1);
        return false;
    }
    *deletedValue = arr[index];
    for (int i = index; i < *size - 1; i++) {
        arr[i] = arr[i + 1];
    }
    (*size)--;
    return true;
}

bool deleteByValue(int arr[], int *size, int value) {
    int index = linearSearch(arr, *size, value);
    if (index == -1) {
        return false;
    }
    int dummy;
    return deleteByIndex(arr, size, index, &dummy);
}

int linearSearch(const int arr[], int size, int target) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == target) {
            return i;
        }
    }
    return -1;
}

int binarySearch(const int arr[], int size, int target) {
    int low = 0;
    int high = size - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] == target) {
            return mid;
        } else if (arr[mid] < target) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return -1;
}

static void reverseRange(int arr[], int start, int end) {
    while (start < end) {
        int temp = arr[start];
        arr[start] = arr[end];
        arr[end] = temp;
        start++;
        end--;
    }
}

void rotateLeft(int arr[], int size, int k) {
    if (size <= 1) return;
    k = ((k % size) + size) % size; // handle negative or k > size
    if (k == 0) return;

    // Using reversal algorithm O(n) time, O(1) space
    reverseRange(arr, 0, k - 1);
    reverseRange(arr, k, size - 1);
    reverseRange(arr, 0, size - 1);
}

void rotateRight(int arr[], int size, int k) {
    if (size <= 1) return;
    k = ((k % size) + size) % size;
    if (k == 0) return;

    // Right rotate by k is equivalent to left rotate by (size - k)
    rotateLeft(arr, size, size - k);
}

void reverseArray(int arr[], int size) {
    if (size <= 1) return;
    reverseRange(arr, 0, size - 1);
}

bool isSorted(const int arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            return false;
        }
    }
    return true;
}
