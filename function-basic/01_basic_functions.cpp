#include <iostream>
using namespace std;

// ─────────────────────────────────────────────────────────
// BASIC FUNCTIONS
// A function is a reusable block of code that performs a task.
// Structure: returnType functionName(parameters) { body }
// ─────────────────────────────────────────────────────────

// Function with no parameters and no return value (void)
void greet() {
    cout << "Hello, World!" << endl;
}

// Function with parameters and a return value
int add(int a, int b) {
    return a + b; // returns the sum of a and b
}

// Function that returns a double
double square(double x) {
    return x * x; // returns x squared
}

// Function declaration (prototype) — tells the compiler this function exists
// before we define it below main()
bool isEven(int n);

int main() {
    greet(); // call the void function — just executes it

    int result = add(3, 7); // call add() and store the returned value
    cout << "3 + 7 = " << result << endl;

    cout << "5.0 squared = " << square(5.0) << endl;

    cout << "Is 4 even? " << (isEven(4) ? "Yes" : "No") << endl;
    cout << "Is 7 even? " << (isEven(7) ? "Yes" : "No") << endl;

    return 0;
}

// Function defined AFTER main — works because we declared it above
bool isEven(int n) {
    return n % 2 == 0; // true if remainder when divided by 2 is 0
}
