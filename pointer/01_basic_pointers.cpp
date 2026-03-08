// 01_basic_pointers.cpp
// Topic: Basic Pointer Concepts - Declaration, Initialization, Dereferencing

#include <iostream>
using namespace std;

int main() {
    // --- 1. Declare a normal integer variable ---
    int age = 25;

    // --- 2. Declare a pointer to int ---
    // A pointer stores the MEMORY ADDRESS of another variable.
    // Syntax: <type>* <pointer_name>
    int* ptr;

    // --- 3. Assign the address of 'age' to the pointer ---
    // The '&' (address-of) operator gives the memory address of a variable.
    ptr = &age;

    // --- 4. Print the value of 'age' ---
    cout << "Value of age      : " << age << endl;

    // --- 5. Print the memory address of 'age' ---
    // '&age' and 'ptr' both hold the same address.
    cout << "Address of age    : " << &age << endl;

    // --- 6. Print what the pointer holds (the address) ---
    cout << "Value of ptr      : " << ptr << endl;

    // --- 7. Dereference the pointer ---
    // '*ptr' means "go to the address stored in ptr and read the value there".
    cout << "Dereferenced ptr  : " << *ptr << endl;

    // --- 8. Modify the original variable through the pointer ---
    // Writing to '*ptr' changes the value at the address ptr points to.
    *ptr = 30;
    cout << "age after *ptr=30 : " << age << endl;  // age is now 30

    // --- 9. Size of a pointer ---
    // On a 64-bit system a pointer is 8 bytes regardless of the type it points to.
    cout << "sizeof(int)       : " << sizeof(int)  << " bytes" << endl;
    cout << "sizeof(ptr)       : " << sizeof(ptr)  << " bytes" << endl;

    // --- 10. Pointer to double ---
    double price = 9.99;
    double* dPtr = &price;   // dPtr holds the address of 'price'
    cout << "price             : " << *dPtr << endl;  // dereference to get 9.99

    return 0;
}
