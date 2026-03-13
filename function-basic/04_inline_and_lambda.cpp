#include <iostream>
#include <vector>
#include <algorithm> // for sort(), for_each()
using namespace std;

// ─────────────────────────────────────────────────────────
// INLINE FUNCTIONS & LAMBDA FUNCTIONS
//
// Inline — hints to the compiler to copy the function body at
//           every call site, avoiding function call overhead.
//           Best for tiny, frequently-called functions.
//
// Lambda — an anonymous (unnamed) function defined right where it is used.
//           Syntax: [capture](params) { body }
// ─────────────────────────────────────────────────────────

// INLINE FUNCTION — defined with the 'inline' keyword
inline int square(int x) {
    return x * x; // compiler may replace square(5) with 5*5 directly
}

inline bool isPositive(int x) {
    return x > 0;
}

int main() {
    cout << "--- Inline Functions ---" << endl;
    cout << "square(6)       = " << square(6) << endl;
    cout << "isPositive(-3)  = " << (isPositive(-3) ? "Yes" : "No") << endl;
    cout << "isPositive(5)   = " << (isPositive(5)  ? "Yes" : "No") << endl;

    // ─────────────────────────────────────────────────────────
    // LAMBDA FUNCTIONS
    // ─────────────────────────────────────────────────────────
    cout << "\n--- Lambda Functions ---" << endl;

    // Basic lambda: no capture, stored in a variable
    auto greet = []() {
        cout << "Hello from a lambda!" << endl;
    };
    greet(); // call it like a regular function

    // Lambda with parameters and return value
    auto multiply = [](int a, int b) -> int {
        return a * b;
    };
    cout << "multiply(4, 5) = " << multiply(4, 5) << endl;

    // Lambda with capture: [=] captures all local variables by VALUE
    int factor = 3;
    auto multiplyByFactor = [=](int x) {
        return x * factor; // uses captured 'factor'
    };
    cout << "multiplyByFactor(7) = " << multiplyByFactor(7) << endl;

    // Lambda with capture by REFERENCE: [&] — can modify the captured variable
    int count = 0;
    auto increment = [&]() {
        count++; // modifies the original 'count' variable
    };
    increment();
    increment();
    cout << "count after 2 increments = " << count << endl;

    // Lambda used directly with STL algorithms
    cout << "\n--- Lambda with STL ---" << endl;
    vector<int> nums = {5, 2, 8, 1, 9, 3};

    sort(nums.begin(), nums.end(), [](int a, int b) {
        return a < b; // lambda tells sort() how to compare elements
    });

    cout << "Sorted: ";
    for_each(nums.begin(), nums.end(), [](int n) {
        cout << n << " "; // lambda prints each element
    });
    cout << endl;

    return 0;
}
