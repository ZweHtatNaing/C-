#include <iostream>
#include <vector>
using namespace std;

// ─────────────────────────────────────────────────────────
// FUNCTION TEMPLATES
// A template lets you write ONE function that works with
// ANY data type. The compiler generates the right version
// automatically based on the argument types.
// Syntax: template <typename T>
// ─────────────────────────────────────────────────────────

// Template function: works with int, double, string, etc.
template <typename T>
T getMax(T a, T b) {
    return (a > b) ? a : b; // returns the larger of the two values
}

// Template with two different type parameters
template <typename T, typename U>
void printPair(T first, U second) {
    cout << "(" << first << ", " << second << ")" << endl;
}

// Template function: prints all elements of any vector type
template <typename T>
void printVector(const vector<T>& vec) {
    for (const T& item : vec) {
        cout << item << " "; // works for vector<int>, vector<string>, etc.
    }
    cout << endl;
}

// Template function: swap two values of any type
template <typename T>
void swapValues(T& a, T& b) {
    T temp = a; // T adapts to whatever type is passed
    a = b;
    b = temp;
}

int main() {
    cout << "--- getMax with different types ---" << endl;
    cout << "getMax(3, 7)         = " << getMax(3, 7) << endl;         // int version
    cout << "getMax(3.14, 2.71)   = " << getMax(3.14, 2.71) << endl;   // double version
    cout << "getMax('a', 'z')     = " << getMax('a', 'z') << endl;     // char version

    cout << "\n--- printPair with mixed types ---" << endl;
    printPair("Age", 25);          // T=string, U=int
    printPair(3.14, "Pi");         // T=double, U=string
    printPair(true, 42);           // T=bool, U=int

    cout << "\n--- printVector with different types ---" << endl;
    vector<int>    ints    = {1, 2, 3, 4, 5};
    vector<double> doubles = {1.1, 2.2, 3.3};
    vector<string> words   = {"hello", "world"};

    printVector(ints);    // generates int version
    printVector(doubles); // generates double version
    printVector(words);   // generates string version

    cout << "\n--- swapValues with different types ---" << endl;
    int x = 10, y = 20;
    swapValues(x, y);
    cout << "After swap: x=" << x << " y=" << y << endl;

    string s1 = "hello", s2 = "world";
    swapValues(s1, s2);
    cout << "After swap: s1=" << s1 << " s2=" << s2 << endl;

    return 0;
}
