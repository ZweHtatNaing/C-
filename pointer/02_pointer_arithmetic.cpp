// 02_pointer_arithmetic.cpp
// Topic: Pointer Arithmetic - incrementing, decrementing, difference, comparison

#include <iostream>
using namespace std;

int main() {
    // --- 1. Create an integer array ---
    // Arrays are stored in contiguous memory, making them perfect for pointer arithmetic.
    int nums[] = {10, 20, 30, 40, 50};

    // --- 2. Point to the first element of the array ---
    // 'nums' by itself decays to a pointer to its first element.
    int* ptr = nums;

    // --- 3. Print initial state ---
    cout << "ptr points to     : " << *ptr << endl;  // 10

    // --- 4. Increment the pointer (move to the next element) ---
    // ptr++ advances the address by sizeof(int) bytes (usually 4).
    ptr++;
    cout << "After ptr++       : " << *ptr << endl;  // 20

    // --- 5. Add an integer offset to the pointer ---
    // ptr + 2 skips ahead 2 elements (8 bytes for int).
    ptr = ptr + 2;
    cout << "After ptr + 2     : " << *ptr << endl;  // 40

    // --- 6. Decrement the pointer ---
    ptr--;
    cout << "After ptr--       : " << *ptr << endl;  // 30

    // --- 7. Subtract an integer offset ---
    ptr = ptr - 1;
    cout << "After ptr - 1     : " << *ptr << endl;  // 20

    // --- 8. Pointer difference ---
    // Subtracting two pointers gives the number of ELEMENTS between them.
    int* start = nums;          // points to nums[0]
    int* end   = nums + 4;      // points to nums[4]
    ptrdiff_t diff = end - start;  // ptrdiff_t is the safe type for pointer differences
    cout << "Elements between  : " << diff << endl;  // 4

    // --- 9. Pointer comparison ---
    // Pointers can be compared with <, >, ==, != to check relative positions.
    if (start < end)
        cout << "start is before end in memory" << endl;

    // --- 10. Traverse the entire array with a pointer ---
    cout << "All elements: ";
    for (int* p = nums; p < nums + 5; p++) {
        // p < nums + 5 means "stop when we pass the last element"
        cout << *p << " ";  // dereference to print the value
    }
    cout << endl;

    return 0;
}
