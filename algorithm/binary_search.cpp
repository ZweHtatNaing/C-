#include <iostream>
using namespace std;

// Binary Search: works only on SORTED arrays.
// It repeatedly cuts the search range in half by comparing
// the target with the middle element.
// Time Complexity: O(log n) — much faster than linear search for large arrays.

int binarySearch(int arr[], int size, int target) {
    int left  = 0;        // start of the search range
    int right = size - 1; // end of the search range

    while (left <= right) {
        int mid = left + (right - left) / 2; // find the middle index (avoids overflow)

        if (arr[mid] == target) {
            return mid; // found the target at the middle index
        }

        if (arr[mid] < target) {
            left = mid + 1; // target is in the RIGHT half, discard left
        } else {
            right = mid - 1; // target is in the LEFT half, discard right
        }
    }

    return -1; // target was not found
}

int main() {
    int arr[]  = {2, 5, 8, 12, 16, 23, 38, 56, 72, 91}; // must be sorted
    int size   = sizeof(arr) / sizeof(arr[0]);
    int target = 23; // element we are searching for

    int result = binarySearch(arr, size, target);

    if (result != -1) {
        cout << "Element " << target << " found at index " << result << endl;
    } else {
        cout << "Element " << target << " not found." << endl;
    }

    return 0;
}
