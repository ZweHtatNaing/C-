#include <iostream>
using namespace std;

// Selection Sort: divides the array into sorted and unsorted parts.
// On each pass, it finds the smallest element in the unsorted part
// and moves it to the end of the sorted part.
// Time Complexity: O(n^2)

void selectionSort(int arr[], int size) {
    // Outer loop: move the boundary of the sorted portion forward each pass
    for (int i = 0; i < size - 1; i++) {

        int minIndex = i; // assume the first unsorted element is the smallest

        // Inner loop: search for the actual smallest element in the unsorted portion
        for (int j = i + 1; j < size; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j; // update index if a smaller element is found
            }
        }

        // Swap the found minimum element with the first unsorted element
        if (minIndex != i) {                    // only swap if needed
            int temp        = arr[i];           // save the current element
            arr[i]          = arr[minIndex];    // put the minimum in sorted position
            arr[minIndex]   = temp;             // put the old element in unsorted area
        }
    }
}

int main() {
    int arr[] = {29, 10, 14, 37, 13}; // unsorted array
    int size  = sizeof(arr) / sizeof(arr[0]);

    selectionSort(arr, size);

    cout << "Sorted array: ";
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}
