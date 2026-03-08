// 09_null_void_const_pointers.cpp
// Topic: Null Pointers, Void Pointers, and Const Pointers
//        Also covers dangling pointers and wild pointers.

#include <iostream>
#include <cstring>  // for memcpy
using namespace std;

int main() {
    // ============================================================
    // PART 1: NULL POINTER
    // ============================================================

    // --- 1. What is a null pointer? ---
    // A pointer that points to NOTHING (address 0 / nullptr).
    // Use it to signal "this pointer is not yet valid".
    int* nullPtr = nullptr;  // modern C++ way (preferred over NULL or 0)
    cout << "nullPtr           : " << nullPtr << endl;  // 0x0

    // --- 2. Always check before dereferencing ---
    // Dereferencing a null pointer is UNDEFINED BEHAVIOUR (crash).
    if (nullPtr != nullptr) {
        cout << *nullPtr << endl;  // only safe inside this block
    } else {
        cout << "nullPtr is null -- not dereferencing" << endl;
    }

    // --- 3. Reset a pointer to null after deleting ---
    int* p = new int(5);
    delete p;
    p = nullptr;  // prevents accidental double-delete / dangling pointer use

    // ============================================================
    // PART 2: DANGLING & WILD POINTERS (what NOT to do)
    // ============================================================

    // --- 4. Dangling pointer: points to freed/out-of-scope memory ---
    // int* dangling = new int(10);
    // delete dangling;
    // *dangling = 5;  // UNDEFINED BEHAVIOUR -- memory no longer ours!

    // --- 5. Wild pointer: uninitialised pointer ---
    // int* wild;       // wild holds garbage address
    // *wild = 42;      // UNDEFINED BEHAVIOUR -- never do this!
    // Fix: always initialise: int* wild = nullptr;

    // ============================================================
    // PART 3: VOID POINTER
    // ============================================================

    // --- 6. void* can hold the address of ANY type ---
    // It is a generic pointer with NO type information.
    int    i   = 42;
    double d   = 3.14;
    char   ch  = 'A';

    void* vp = &i;   // point to an int
    cout << "\nvp holds int addr : " << vp << endl;

    vp = &d;         // now point to a double (no cast needed for assignment)
    vp = &ch;        // now point to a char

    // --- 7. You MUST cast before dereferencing a void* ---
    // The compiler does not know the type, so you must tell it.
    vp = &i;
    int* ip = static_cast<int*>(vp);   // cast void* back to int*
    cout << "Dereferenced void*: " << *ip << endl;  // 42

    // --- 8. Practical use: memcpy uses void* to copy raw bytes ---
    int src[] = {1, 2, 3};
    int dst[3];
    // memcpy works on void* so it can copy any type
    memcpy(dst, src, sizeof(src));
    cout << "memcpy result: " << dst[0] << " " << dst[1] << " " << dst[2] << endl;

    // ============================================================
    // PART 4: CONST POINTERS (four combinations)
    // ============================================================

    int x = 10, y = 20;

    // --- 9. Pointer to const int ---
    // You CANNOT change the value through the pointer, but can change WHERE it points.
    const int* ptr1 = &x;
    // *ptr1 = 99;    // ERROR: cannot modify value through ptr1
    ptr1 = &y;        // OK: we can point somewhere else
    cout << "\nptr1 (ptr-to-const): " << *ptr1 << endl;  // 20

    // --- 10. Const pointer to int ---
    // You CANNOT change WHERE it points, but CAN change the value through it.
    int* const ptr2 = &x;
    *ptr2 = 99;       // OK: modifying the value is allowed
    // ptr2 = &y;     // ERROR: cannot re-seat a const pointer
    cout << "ptr2 (const-ptr)  : " << *ptr2 << endl;  // 99

    // --- 11. Const pointer to const int ---
    // You can NEITHER change the value NOR change WHERE it points.
    const int* const ptr3 = &x;
    // *ptr3 = 5;     // ERROR
    // ptr3 = &y;     // ERROR
    cout << "ptr3 (const-ptr-to-const): " << *ptr3 << endl;  // 99

    // --- 12. Non-const pointer to non-const int ---
    // The default: can change both value and direction.
    int* ptr4 = &x;
    *ptr4 = 7;         // change value
    ptr4  = &y;        // change direction
    cout << "ptr4 (plain ptr)  : " << *ptr4 << endl;  // 20

    // Rule of thumb: read the declaration RIGHT-TO-LEFT
    // const int* p  -> p is a pointer to (const int)
    // int* const p  -> p is a const pointer to (int)
    // const int* const p -> p is a const pointer to (const int)

    return 0;
}
