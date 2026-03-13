#include <iostream>
using namespace std;

// ─────────────────────────────────────────────────────────
// PASS BY VALUE, REFERENCE, AND POINTER
//
// Pass by Value   — function gets a COPY, original is unchanged
// Pass by Reference — function gets the ORIGINAL, changes affect it
// Pass by Pointer — function gets a memory address, can modify original
// ─────────────────────────────────────────────────────────

// Pass by VALUE: a copy of x is made, original is NOT changed
void doubleByValue(int x) {
    x = x * 2; // only modifies the local copy
    cout << "  Inside doubleByValue: x = " << x << endl;
}

// Pass by REFERENCE: uses the original variable directly
void doubleByRef(int& x) { // & means "reference to"
    x = x * 2; // directly modifies the original variable
    cout << "  Inside doubleByRef: x = " << x << endl;
}

// Pass by POINTER: receives the memory address of the variable
void doubleByPtr(int* x) { // * means "pointer to"
    *x = *x * 2; // dereference with * to access and modify the actual value
    cout << "  Inside doubleByPtr: x = " << *x << endl;
}

// Practical use: swap two values using references
void swap(int& a, int& b) {
    int temp = a; // save a temporarily
    a = b;        // put b's value into a
    b = temp;     // put saved a into b
}

int main() {
    int num = 10;

    cout << "--- Pass by Value ---" << endl;
    cout << "Before: " << num << endl;
    doubleByValue(num);           // num is unchanged
    cout << "After:  " << num << endl; // still 10

    cout << "\n--- Pass by Reference ---" << endl;
    cout << "Before: " << num << endl;
    doubleByRef(num);             // num IS changed
    cout << "After:  " << num << endl; // now 20

    cout << "\n--- Pass by Pointer ---" << endl;
    cout << "Before: " << num << endl;
    doubleByPtr(&num);            // pass the ADDRESS of num with &
    cout << "After:  " << num << endl; // now 40

    cout << "\n--- Swap using References ---" << endl;
    int a = 5, b = 99;
    cout << "Before: a=" << a << " b=" << b << endl;
    swap(a, b);
    cout << "After:  a=" << a << " b=" << b << endl;

    return 0;
}
