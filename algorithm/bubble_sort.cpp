#include <iostream>
using namespace std;

// Bubble Sort: repeatedly swaps adjacent elements if they are in the wrong order.
// After each pass, the largest unsorted element "bubbles up" to its correct position.
// Time Complexity: O(n^2) — not ideal for large data, but simple to understand.

void bubbleSort(int arr[], int size) {
    // Outer loop: each pass places one element in its correct position
    for (int i = 0; i < size - 1; i++) {

        // Inner loop: compare adjacent pairs up to the unsorted portion
        for (int j = 0; j < size - 1 - i; j++) {

            // If the current element is greater than the next, swap them
            if (arr[j] > arr[j + 1]) {
                int temp   = arr[j];      // save current element temporarily
                arr[j]     = arr[j + 1];  // move smaller element to the left
                arr[j + 1] = temp;        // put the saved element on the right
            }
        }
    }
}

int main() {
    int arr[] = {64, 34, 25, 12, 22, 11, 90}; // unsorted array
    int size  = sizeof(arr) / sizeof(arr[0]);  // calculate number of elements

    bubbleSort(arr, size); // sort the array

    cout << "Sorted array: ";
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " "; // print each sorted element
    }
    cout << endl;

    return 0;
}
