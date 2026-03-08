// 05_pointers_and_functions.cpp
// Topic: Passing Pointers to Functions (Pass-by-Pointer)
//        and Returning Pointers from Functions

#include <iostream>
using namespace std;

// --- Function 1: Pass by VALUE (no effect on original) ---
// A copy of 'x' is made; the original is unchanged.
void passByValue(int x) {
    x = 999;  // only the local copy is modified
    (void)x;  // suppress unused-variable warning: intentional demo
}

// --- Function 2: Pass by POINTER (modifies original) ---
// We pass the ADDRESS of the variable, so the function can change the original.
void passByPointer(int* ptr) {
    *ptr = 999;  // dereference ptr to write to the original variable
}

// --- Function 3: Swap two integers using pointers ---
// Classic example of why pass-by-pointer is useful.
void swap(int* a, int* b) {
    int temp = *a;  // store value at address a
    *a = *b;        // write value at address b into address a
    *b = temp;      // write stored value into address b
}

// --- Function 4: Return a pointer to a static/heap variable ---
// WARNING: Never return a pointer to a LOCAL variable (dangling pointer).
// Here we use 'static' so the variable persists after the function returns.
int* getStaticValue() {
    static int result = 77;  // 'static' keeps it alive beyond the function call
    return &result;           // safe to return this address
}

// --- Function 5: Receive a double pointer to modify a pointer itself ---
// Useful when a function needs to change WHERE the caller's pointer points.
void allocateMemory(int** pp, int val) {
    *pp = new int(val);  // allocate int on heap and make the caller's pointer point to it
}

int main() {
    // === Pass by Value ===
    int n = 10;
    passByValue(n);
    cout << "After passByValue : " << n << endl;  // still 10, unchanged

    // === Pass by Pointer ===
    passByPointer(&n);  // pass the address of n
    cout << "After passByPointer: " << n << endl;  // now 999

    // === Swap ===
    int x = 5, y = 8;
    cout << "\nBefore swap: x=" << x << " y=" << y << endl;
    swap(&x, &y);  // pass addresses so the function can modify both
    cout << "After swap : x=" << x << " y=" << y << endl;

    // === Return Pointer ===
    int* p = getStaticValue();  // p points to the static variable inside the function
    cout << "\nStatic value via pointer: " << *p << endl;  // 77
    *p = 88;                    // modify the static variable through the pointer
    cout << "After modifying via ptr : " << *getStaticValue() << endl;  // 88

    // === Double Pointer to allocate ===
    int* dynPtr = nullptr;      // currently points to nothing
    allocateMemory(&dynPtr, 42);  // function sets dynPtr to a newly allocated int
    cout << "\nDynamic value: " << *dynPtr << endl;  // 42
    delete dynPtr;              // free the heap memory when done

    return 0;
}
