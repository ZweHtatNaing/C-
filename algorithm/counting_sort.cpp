#include <iostream>
#include <vector>
using namespace std;

// Counting Sort: counts how many times each value appears,
// then reconstructs the sorted array from those counts.
// Works best when the range of values is small and known.
// Time Complexity: O(n + k), where k is the range of values.
// Note: only works with non-negative integers.

void countingSort(int arr[], int size) {
    // Find the maximum value in the array to know the count array size
    int maxVal = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] > maxVal) maxVal = arr[i];
    }

    // Create a count array of zeros, with one slot for each possible value
    vector<int> count(maxVal + 1, 0);

    // Count how many times each value appears in the input array
    for (int i = 0; i < size; i++) {
        count[arr[i]]++; // increment the count for this value
    }

    // Rebuild the sorted array using the counts
    int index = 0; // position to write next value in original array
    for (int val = 0; val <= maxVal; val++) {
        while (count[val] > 0) {     // place 'val' as many times as it appeared
            arr[index] = val;
            index++;
            count[val]--;
        }
    }
}

int main() {
    int arr[] = {4, 2, 2, 8, 3, 3, 1}; // unsorted array with small range of values
    int size  = sizeof(arr) / sizeof(arr[0]);

    countingSort(arr, size);

    cout << "Sorted array: ";
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}
