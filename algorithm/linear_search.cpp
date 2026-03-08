#include <iostream>
using namespace std;

// Linear Search: checks each element one by one from left to right.
// Simple but can be slow for large arrays since it may check every element.
// Time Complexity: O(n) — works on both sorted and unsorted arrays.

int linearSearch(int arr[], int size, int target) {
    // Loop through every element in the array
    for (int i = 0; i < size; i++) {

        if (arr[i] == target) {
            return i; // found the target — return its index
        }
    }

    return -1; // target was not found in the array
}

int main() {
    int arr[]  = {5, 3, 8, 1, 9, 2}; // unsorted array
    int size   = sizeof(arr) / sizeof(arr[0]);
    int target = 9; // element we are searching for

    int result = linearSearch(arr, size, target);

    if (result != -1) {
        cout << "Element " << target << " found at index " << result << endl;
    } else {
        cout << "Element " << target << " not found." << endl;
    }

    return 0;
}
