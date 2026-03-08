// 01_vector_basics.cpp
// Topic: Vector Basics - Declaration, Initialization, and Core Concepts

#include <iostream>
#include <vector>
using namespace std;

int main() {
    // =====================================================================
    // WHAT IS A VECTOR?
    // A std::vector is a dynamic array from the C++ Standard Library.
    // Unlike plain arrays, a vector:
    //   - Can grow or shrink at runtime
    //   - Manages its own memory automatically
    //   - Always stores elements contiguously in memory
    // =====================================================================

    // --- 1. Default constructor: empty vector ---
    vector<int> v1;
    cout << "v1 size     : " << v1.size() << endl;  // 0

    // --- 2. Vector with n copies of a value ---
    // vector<type>(count, value)
    vector<int> v2(5, 10);  // {10, 10, 10, 10, 10}
    cout << "v2          : ";
    for (int x : v2) cout << x << " ";
    cout << endl;

    // --- 3. Initializer-list construction (C++11) ---
    vector<int> v3 = {1, 2, 3, 4, 5};
    cout << "v3          : ";
    for (int x : v3) cout << x << " ";
    cout << endl;

    // --- 4. Vector with n default-initialised elements ---
    // Each int is zero-initialised.
    vector<int> v4(4);  // {0, 0, 0, 0}
    cout << "v4 (default): ";
    for (int x : v4) cout << x << " ";
    cout << endl;

    // --- 5. Copy constructor ---
    vector<int> v5(v3);  // deep copy of v3
    cout << "v5 (copy)   : ";
    for (int x : v5) cout << x << " ";
    cout << endl;

    // --- 6. Range constructor: copy from another container range ---
    // Constructs from the range [first, last)
    vector<int> v6(v3.begin() + 1, v3.end() - 1);  // {2, 3, 4}
    cout << "v6 (range)  : ";
    for (int x : v6) cout << x << " ";
    cout << endl;

    // --- 7. Assignment operator ---
    vector<int> v7;
    v7 = {100, 200, 300};  // replaces contents entirely
    cout << "v7 (assign) : ";
    for (int x : v7) cout << x << " ";
    cout << endl;

    // --- 8. Move constructor (C++11): transfer ownership without copying ---
    vector<int> source = {9, 8, 7};
    vector<int> v8(move(source));  // source is now empty after the move
    cout << "v8 (moved)  : ";
    for (int x : v8) cout << x << " ";
    cout << endl;
    cout << "source after move size: " << source.size() << endl;  // 0

    // --- 9. Different element types ---
    vector<double> dv = {1.1, 2.2, 3.3};
    vector<string> sv = {"apple", "banana", "cherry"};
    vector<bool>   bv = {true, false, true};

    cout << "\ndouble vector: ";
    for (double d : dv) cout << d << " ";
    cout << endl;

    cout << "string vector: ";
    for (const string& s : sv) cout << s << " ";
    cout << endl;

    cout << "bool   vector: ";
    for (bool b : bv) cout << boolalpha << b << " ";
    cout << endl;

    // --- 10. Nested / 2D vector (brief preview) ---
    vector<vector<int>> matrix = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    cout << "\n2D vector [1][2] = " << matrix[1][2] << endl;  // 6

    return 0;
}
