#include <iostream>
using namespace std;

// Insertion Sort: builds the sorted array one element at a time.
// It picks each element and inserts it into its correct position
// among the already-sorted elements — similar to sorting playing cards.
// Time Complexity: O(n^2), but very efficient for nearly sorted data.

void insertionSort(int arr[], int size) {
    // Start from the second element; the first element is trivially sorted
    for (int i = 1; i < size; i++) {

        int key = arr[i]; // the element we want to place correctly
        int j   = i - 1; // start comparing with the element just before key

        // Shift elements that are greater than key one position to the right
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j]; // move the larger element one step right
            j--;                 // move left to compare the next element
        }

        arr[j + 1] = key; // insert key into its correct sorted position
    }
}

int main() {
    int arr[] = {12, 11, 13, 5, 6}; // unsorted array
    int size  = sizeof(arr) / sizeof(arr[0]);

    insertionSort(arr, size);

    cout << "Sorted array: ";
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}
