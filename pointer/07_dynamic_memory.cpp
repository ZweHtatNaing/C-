// 07_dynamic_memory.cpp
// Topic: Dynamic Memory Allocation with new / delete
//        Heap memory, memory leaks, and safe patterns

#include <iostream>
using namespace std;

int main() {
    // ===== SINGLE VARIABLE =====

    // --- 1. Allocate a single int on the HEAP ---
    // 'new int' allocates sizeof(int) bytes on the heap and returns a pointer to it.
    int* p = new int;

    // --- 2. Assign a value to the heap-allocated int ---
    *p = 55;  // write through the pointer
    cout << "Heap int value    : " << *p << endl;  // 55

    // --- 3. Allocate and initialise in one step ---
    int* q = new int(99);   // allocates AND initialises to 99
    cout << "Heap int init     : " << *q << endl;  // 99

    // --- 4. Free the allocated memory ---
    // 'delete' returns the memory to the OS. Always delete what you new.
    delete p;   // free the memory p pointed to
    delete q;   // free the memory q pointed to

    // --- 5. Set to nullptr after delete (avoids dangling pointer bugs) ---
    p = nullptr;
    q = nullptr;

    // ===== ARRAYS ON THE HEAP =====

    // --- 6. Allocate an array of ints on the heap ---
    // 'new int[n]' allocates space for n ints and returns a pointer to the first.
    int size = 5;
    int* arr = new int[size];

    // --- 7. Fill the dynamic array ---
    for (int i = 0; i < size; i++) {
        arr[i] = (i + 1) * 10;  // arr[i] is *(arr + i)
    }

    // --- 8. Print the dynamic array ---
    cout << "Dynamic array: ";
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";  // 10 20 30 40 50
    }
    cout << endl;

    // --- 9. Free the dynamic array ---
    // Use 'delete[]' (with brackets) for arrays -- never plain 'delete'.
    delete[] arr;
    arr = nullptr;

    // ===== STRUCT ON THE HEAP =====

    // --- 10. Allocate a struct on the heap ---
    struct Point { int x, y; };

    Point* pt = new Point;   // allocate a Point struct on the heap
    pt->x = 3;               // '->' dereferences pointer AND accesses member
    pt->y = 7;               // equivalent to (*pt).y = 7
    cout << "Point: (" << pt->x << ", " << pt->y << ")" << endl;

    delete pt;               // free the struct
    pt = nullptr;

    // ===== MEMORY LEAK DEMO (commented out) =====
    // If you comment-in the code below and never delete it, that's a memory leak.
    // int* leak = new int(42);
    // /* forgot to: delete leak; */

    // ===== ZERO-INITIALISED ARRAY =====

    // --- 11. Value-initialise (zero) a heap array ---
    // 'new int[n]()' initialises all elements to 0.
    int* zeros = new int[4]();
    cout << "Zero-initialised: ";
    for (int i = 0; i < 4; i++) cout << zeros[i] << " ";  // 0 0 0 0
    cout << endl;
    delete[] zeros;

    return 0;
}
