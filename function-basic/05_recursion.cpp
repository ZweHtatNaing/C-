#include <iostream>
using namespace std;

// ─────────────────────────────────────────────────────────
// RECURSION
// A function that calls ITSELF to solve a smaller version
// of the same problem.
//
// Every recursive function needs:
//   1. Base case  — when to STOP (prevents infinite loop)
//   2. Recursive case — how to reduce the problem each call
// ─────────────────────────────────────────────────────────

// Example 1: Factorial — n! = n * (n-1) * ... * 1
int factorial(int n) {
    if (n <= 1) return 1;        // base case: stop here
    return n * factorial(n - 1); // recursive case: call itself with n-1
}

// Example 2: Fibonacci — F(n) = F(n-1) + F(n-2)
int fibonacci(int n) {
    if (n == 0) return 0;                        // base case 1
    if (n == 1) return 1;                        // base case 2
    return fibonacci(n - 1) + fibonacci(n - 2);  // recursive case
}

// Example 3: Sum of digits — e.g. 123 → 1+2+3 = 6
int sumDigits(int n) {
    if (n == 0) return 0;              // base case: no digits left
    return (n % 10) + sumDigits(n / 10); // last digit + sum of remaining digits
}

// Example 4: Power — base^exp
double power(double base, int exp) {
    if (exp == 0) return 1;               // base case: anything^0 = 1
    return base * power(base, exp - 1);   // recursive case: base * base^(exp-1)
}

// Example 5: Countdown — shows how recursion unwinds after the base case
void countdown(int n) {
    if (n <= 0) {                         // base case
        cout << "  Go!" << endl;
        return;
    }
    cout << "  " << n << "..." << endl;
    countdown(n - 1);                     // call itself with smaller n
    // code here runs as the call stack UNWINDS (after base case)
}

int main() {
    cout << "--- Factorial ---" << endl;
    cout << "5! = " << factorial(5) << endl;  // 120
    cout << "7! = " << factorial(7) << endl;  // 5040

    cout << "\n--- Fibonacci ---" << endl;
    for (int i = 0; i <= 8; i++) {
        cout << "F(" << i << ") = " << fibonacci(i) << endl;
    }

    cout << "\n--- Sum of Digits ---" << endl;
    cout << "sumDigits(123) = " << sumDigits(123) << endl; // 6
    cout << "sumDigits(456) = " << sumDigits(456) << endl; // 15

    cout << "\n--- Power ---" << endl;
    cout << "2^10 = " << power(2, 10) << endl; // 1024
    cout << "3^4  = " << power(3, 4)  << endl; // 81

    cout << "\n--- Countdown ---" << endl;
    countdown(5);

    return 0;
}
