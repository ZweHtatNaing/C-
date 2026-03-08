#include <iostream>
using namespace std;

// Fibonacci Sequence: each number is the sum of the two numbers before it.
// Sequence: 0, 1, 1, 2, 3, 5, 8, 13, 21, ...
// This version uses iteration (loop) which is efficient.
// Time Complexity: O(n)

int fibonacci(int n) {
    if (n == 0) return 0; // first Fibonacci number is 0
    if (n == 1) return 1; // second Fibonacci number is 1

    int prev = 0; // holds the value two steps back
    int curr = 1; // holds the value one step back

    for (int i = 2; i <= n; i++) {
        int next = prev + curr; // next number = sum of the previous two
        prev     = curr;        // shift prev forward
        curr     = next;        // shift curr forward
    }

    return curr; // the nth Fibonacci number
}

int main() {
    int n = 10; // how many Fibonacci numbers to print

    cout << "Fibonacci sequence up to F(" << n << "):" << endl;
    for (int i = 0; i <= n; i++) {
        cout << "F(" << i << ") = " << fibonacci(i) << endl;
    }

    return 0;
}
