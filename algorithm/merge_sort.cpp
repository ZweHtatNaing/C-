#include <iostream>
using namespace std;

// Merge Sort: a divide-and-conquer algorithm.
// It splits the array in half recursively until each part has one element,
// then merges the parts back together in sorted order.
// Time Complexity: O(n log n) — efficient and stable.

// Merges two sorted halves: arr[left..mid] and arr[mid+1..right]
void merge(int arr[], int left, int mid, int right) {
    int leftSize  = mid - left + 1;  // size of the left half
    int rightSize = right - mid;     // size of the right half

    // Create temporary arrays to hold the two halves
    int leftArr[leftSize], rightArr[rightSize];

    // Copy data into the temporary arrays
    for (int i = 0; i < leftSize; i++)  leftArr[i]  = arr[left + i];
    for (int i = 0; i < rightSize; i++) rightArr[i] = arr[mid + 1 + i];

    int i = 0, j = 0;       // indices for leftArr and rightArr
    int k = left;            // index for the merged position in arr

    // Compare elements from both halves and place the smaller one first
    while (i < leftSize && j < rightSize) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k] = leftArr[i]; // left element is smaller, place it
            i++;
        } else {
            arr[k] = rightArr[j]; // right element is smaller, place it
            j++;
        }
        k++;
    }

    // Copy any remaining elements from leftArr (if any)
    while (i < leftSize)  { arr[k] = leftArr[i];  i++; k++; }

    // Copy any remaining elements from rightArr (if any)
    while (j < rightSize) { arr[k] = rightArr[j]; j++; k++; }
}

// Recursively splits and sorts the array
void mergeSort(int arr[], int left, int right) {
    if (left >= right) return; // base case: a single element is already sorted

    int mid = left + (right - left) / 2; // find the midpoint

    mergeSort(arr, left, mid);       // sort the left half
    mergeSort(arr, mid + 1, right);  // sort the right half
    merge(arr, left, mid, right);    // merge the two sorted halves
}

int main() {
    int arr[] = {38, 27, 43, 3, 9, 82, 10}; // unsorted array
    int size  = sizeof(arr) / sizeof(arr[0]);

    mergeSort(arr, 0, size - 1);

    cout << "Sorted array: ";
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}
