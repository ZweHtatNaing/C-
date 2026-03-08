// 04_double_pointers.cpp
// Topic: Pointer to Pointer (Double Pointer / **ptr)

#include <iostream>
using namespace std;

int main() {
    // --- 1. Normal variable ---
    int value = 42;

    // --- 2. First level pointer (single pointer) ---
    // ptr1 holds the address of 'value'
    int* ptr1 = &value;

    // --- 3. Second level pointer (double pointer / pointer-to-pointer) ---
    // ptr2 holds the address of ptr1 (which itself holds an address)
    int** ptr2 = &ptr1;

    // --- 4. Visualising the chain ---
    // value <-- ptr1 <-- ptr2
    cout << "value             : " << value  << endl;          // 42
    cout << "&value            : " << &value << endl;          // e.g. 0x7fff...
    cout << "ptr1              : " << ptr1   << endl;          // same as &value
    cout << "*ptr1             : " << *ptr1  << endl;          // 42
    cout << "ptr2              : " << ptr2   << endl;          // address of ptr1
    cout << "*ptr2             : " << *ptr2  << endl;          // same as ptr1
    cout << "**ptr2            : " << **ptr2 << endl;          // 42

    // --- 5. Modify 'value' through double pointer ---
    // **ptr2 first dereferences ptr2 to get ptr1,
    // then dereferences ptr1 to reach 'value'.
    **ptr2 = 100;
    cout << "value after **ptr2=100 : " << value << endl;  // 100

    // --- 6. Practical use: dynamic 2D array ---
    int rows = 3, cols = 3;

    // Allocate an array of 'rows' int pointers
    int** grid = new int*[rows];

    // For each row, allocate 'cols' ints
    for (int i = 0; i < rows; i++) {
        grid[i] = new int[cols];  // grid[i] points to one row
    }

    // Fill the grid: grid[i][j] = i * cols + j
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            grid[i][j] = i * cols + j;  // grid[i][j] is *(*(grid+i)+j)
        }
    }

    // Print the dynamically allocated 2D grid
    cout << "\nDynamic 2D grid:\n";
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }

    // --- 7. Clean up: always delete in reverse order ---
    // First delete each row array
    for (int i = 0; i < rows; i++) {
        delete[] grid[i];  // free each row
    }
    // Then delete the array of row-pointers
    delete[] grid;

    return 0;
}
