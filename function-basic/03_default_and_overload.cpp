#include <iostream>
using namespace std;

// ─────────────────────────────────────────────────────────
// DEFAULT PARAMETERS & FUNCTION OVERLOADING
//
// Default Parameters — assign a fallback value if caller skips that argument
// Function Overloading — multiple functions with the SAME name but DIFFERENT parameters
// ─────────────────────────────────────────────────────────

// DEFAULT PARAMETERS
// If the caller doesn't pass 'separator', it defaults to ", "
void printList(string a, string b, string separator = ", ") {
    cout << a << separator << b << endl;
}

// Multiple default parameters (defaults must be on the RIGHT side)
void createProfile(string name, int age = 18, string role = "User") {
    cout << "Name: " << name << " | Age: " << age << " | Role: " << role << endl;
}

// ─────────────────────────────────────────────────────────
// FUNCTION OVERLOADING
// Same function name, different parameter types or counts.
// The compiler picks the right version based on the arguments.
// ─────────────────────────────────────────────────────────

// Version 1: adds two ints
int add(int a, int b) {
    return a + b;
}

// Version 2: adds two doubles
double add(double a, double b) {
    return a + b;
}

// Version 3: adds three ints
int add(int a, int b, int c) {
    return a + b + c;
}

// Version 4: concatenates two strings
string add(string a, string b) {
    return a + b;
}

int main() {
    cout << "--- Default Parameters ---" << endl;
    printList("Apple", "Banana");            // uses default separator ", "
    printList("Apple", "Banana", " and ");   // overrides default separator

    createProfile("Alice");                  // uses both defaults
    createProfile("Bob", 25);               // overrides age only
    createProfile("Carol", 30, "Admin");    // overrides both

    cout << "\n--- Function Overloading ---" << endl;
    cout << "add(2, 3)           = " << add(2, 3) << endl;         // calls int version
    cout << "add(2.5, 3.5)       = " << add(2.5, 3.5) << endl;     // calls double version
    cout << "add(1, 2, 3)        = " << add(1, 2, 3) << endl;      // calls 3-param version
    cout << "add(\"Hello \",\"World\")= " << add(string("Hello "), string("World")) << endl; // string version

    return 0;
}
