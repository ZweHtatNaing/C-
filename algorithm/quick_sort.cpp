#include <iostream>
using namespace std;

// Quick Sort: a divide-and-conquer algorithm.
// It picks a "pivot" element, then rearranges the array so all elements
// smaller than the pivot are on the left, and all greater are on the right.
// Then it recursively sorts both sides.
// Time Complexity: O(n log n) average, O(n^2) worst case.

// Partitions the array around a pivot and returns the pivot's final index
int partition(int arr[], int low, int high) {
    int pivot = arr[high]; // choose the last element as the pivot
    int i     = low - 1;  // i tracks the boundary of elements smaller than pivot

    for (int j = low; j < high; j++) {
        // If current element is smaller than or equal to pivot, swap it to the left side
        if (arr[j] <= pivot) {
            i++;                    // expand the smaller-elements boundary
            swap(arr[i], arr[j]);   // swap current element to the left side
        }
    }

    // Place the pivot in its correct sorted position
    swap(arr[i + 1], arr[high]);

    return i + 1; // return the pivot's final index
}

void quickSort(int arr[], int low, int high) {
    if (low >= high) return; // base case: one or zero elements, already sorted

    int pivotIndex = partition(arr, low, high); // place pivot in correct position

    quickSort(arr, low, pivotIndex - 1);  // recursively sort the left side
    quickSort(arr, pivotIndex + 1, high); // recursively sort the right side
}

int main() {
    int arr[] = {10, 7, 8, 9, 1, 5}; // unsorted array
    int size  = sizeof(arr) / sizeof(arr[0]);

    quickSort(arr, 0, size - 1);

    cout << "Sorted array: ";
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}
