// 08_function_pointers.cpp
// Topic: Function Pointers - storing and calling functions via pointers

#include <iostream>
#include <algorithm>  // for std::sort
using namespace std;

// --- Simple math functions to use as examples ---
int add(int a, int b) { return a + b; }
int sub(int a, int b) { return a - b; }
int mul(int a, int b) { return a * b; }

// --- A function that accepts a function pointer as a parameter ---
// Syntax: return_type (*paramName)(paramTypes)
// This lets you pass any compatible function as a callback.
int applyOp(int x, int y, int (*op)(int, int)) {
    return op(x, y);  // call the function through the pointer
}

// --- Comparator functions for sorting ---
// Must match the signature expected by std::sort's comparator: bool(T, T)
bool ascending(int a, int b) {
    return a < b;  // returns true if a should come BEFORE b
}

bool descending(int a, int b) {
    return a > b;  // returns true if a should come BEFORE b (i.e. larger first)
}

// --- A function that returns a function pointer ---
// Based on a char, return the matching math function.
// Return type: pointer to a function taking (int,int) returning int.
int (*getOperation(char op))(int, int) {
    if (op == '+') return add;
    if (op == '-') return sub;
    if (op == '*') return mul;
    return nullptr;  // unknown operator
}

int main() {
    // === 1. Declare a function pointer ===
    // Syntax: return_type (*name)(param_types) = &function;
    // The '&' is optional for functions -- just the name works too.
    int (*fp)(int, int) = &add;
    cout << "fp points to add: " << fp(3, 4) << endl;  // 7

    // === 2. Re-assign the pointer to a different function ===
    fp = sub;  // now fp points to sub
    cout << "fp points to sub: " << fp(10, 3) << endl;  // 7

    // === 3. Use a function pointer as a callback ===
    cout << "applyOp add: " << applyOp(5, 6, add) << endl;  // 11
    cout << "applyOp mul: " << applyOp(5, 6, mul) << endl;  // 30

    // === 4. Array of function pointers ===
    // Useful for dispatch tables (like a simple calculator).
    int (*ops[3])(int, int) = {add, sub, mul};
    const char* names[] = {"add", "sub", "mul"};
    for (int i = 0; i < 3; i++) {
        // ops[i] is a function pointer; call it like a normal function.
        cout << names[i] << "(8, 2) = " << ops[i](8, 2) << endl;
    }

    // === 5. Function pointer returned from another function ===
    int (*calc)(int, int) = getOperation('+');
    if (calc) {
        cout << "Operation '+': " << calc(7, 3) << endl;  // 10
    }

    // === 6. Using typedef to simplify function pointer syntax ===
    // Instead of repeating the verbose syntax, define a type alias.
    typedef int (*BinaryOp)(int, int);  // BinaryOp is now a type alias
    BinaryOp myOp = mul;
    cout << "myOp (mul) 4*5: " << myOp(4, 5) << endl;  // 20

    // === 7. Using 'using' (modern C++ alias) ===
    using Comparator = bool (*)(int, int);
    Comparator cmp = ascending;  // alias demo -- used conceptually, suppress warning
    (void)cmp;

    // === 8. std::sort with a function pointer comparator ===
    int arr[] = {5, 1, 4, 2, 3};
    sort(arr, arr + 5, ascending);  // sort ascending
    cout << "Sorted ascending: ";
    for (int x : arr) cout << x << " ";  // 1 2 3 4 5
    cout << endl;

    sort(arr, arr + 5, descending);  // sort descending
    cout << "Sorted descending: ";
    for (int x : arr) cout << x << " ";  // 5 4 3 2 1
    cout << endl;

    return 0;
}
