#include <iostream>
using namespace std;

// Factorial: calculates n! = n * (n-1) * (n-2) * ... * 1
// Example: 5! = 5 * 4 * 3 * 2 * 1 = 120
// Uses recursion — a function that calls itself with a smaller input.
// Time Complexity: O(n)

int factorial(int n) {
    // Base case: factorial of 0 or 1 is 1
    if (n <= 1) return 1;

    // Recursive case: n! = n * (n-1)!
    return n * factorial(n - 1);
}

int main() {
    int number = 6; // find the factorial of this number

    cout << number << "! = " << factorial(number) << endl; // print result

    return 0;
}
