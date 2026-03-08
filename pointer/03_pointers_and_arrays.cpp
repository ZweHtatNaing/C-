// 03_pointers_and_arrays.cpp
// Topic: Relationship between Pointers and Arrays (1D and 2D)

#include <iostream>
using namespace std;

int main() {
    // ===== 1D ARRAY =====

    // --- 1. Declare a 1D array ---
    int arr[] = {5, 10, 15, 20, 25};

    // --- 2. Array name IS a pointer to the first element ---
    // 'arr' and '&arr[0]' are equivalent.
    cout << "arr (base address): " << arr      << endl;
    cout << "&arr[0]           : " << &arr[0]  << endl;  // same as above

    // --- 3. Access elements via pointer notation ---
    // arr[i] is exactly the same as *(arr + i)
    cout << "arr[2]            : " << arr[2]         << endl;  // 15
    cout << "*(arr + 2)        : " << *(arr + 2)     << endl;  // 15 (equivalent)

    // --- 4. Use a separate pointer to walk the array ---
    int* ptr = arr;  // ptr now points to arr[0]
    for (int i = 0; i < 5; i++) {
        // ptr[i]  == arr[i] == *(arr+i) -- all are identical
        cout << "ptr[" << i << "] = " << ptr[i] << endl;
    }

    // --- 5. Key difference: array name vs pointer ---
    // 'arr' is a constant pointer -- you CANNOT do arr++ (compile error).
    // 'ptr' is a regular pointer -- you CAN do ptr++.
    ptr++;               // OK: ptr now points to arr[1]
    cout << "After ptr++, *ptr: " << *ptr << endl;  // 10
    ptr = arr;           // reset ptr back to start

    // ===== 2D ARRAY =====

    // --- 6. Declare a 2D array (3 rows, 3 cols) ---
    int matrix[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    // --- 7. 'matrix' is a pointer to its first ROW ---
    // matrix[i] is a pointer to row i's first element.
    // matrix[i][j] == *(*(matrix + i) + j)
    cout << "\n2D Array elements:\n";
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            // *(*(matrix + i) + j) navigates: row i, then column j
            cout << *(*(matrix + i) + j) << " ";
        }
        cout << endl;
    }

    // --- 8. Traverse entire 2D array with a single int* ---
    // The memory layout of a 2D array is flat (row-major order).
    int* flatPtr = &matrix[0][0];  // pointer to the very first element
    cout << "\nFlat traversal: ";
    for (int i = 0; i < 9; i++) {
        cout << flatPtr[i] << " ";  // flatPtr[i] == *(flatPtr + i)
    }
    cout << endl;

    return 0;
}
