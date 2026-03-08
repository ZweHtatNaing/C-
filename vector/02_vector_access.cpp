// 02_vector_access.cpp
// Topic: Accessing Elements - [], at(), front(), back(), data()

#include <iostream>
#include <vector>
#include <stdexcept>   // for std::out_of_range
using namespace std;

int main() {
    vector<int> v = {10, 20, 30, 40, 50};

    // =====================================================================
    // ELEMENT ACCESS METHODS
    // =====================================================================

    // --- 1. operator[] (subscript) ---
    // Fast, NO bounds checking. Undefined behaviour if index is out of range.
    cout << "v[0]  : " << v[0] << endl;   // 10
    cout << "v[4]  : " << v[4] << endl;   // 50

    // Write through [] as well:
    v[2] = 99;
    cout << "v[2] after assignment: " << v[2] << endl;  // 99
    v[2] = 30;  // restore

    // --- 2. at() ---
    // Same as [] but performs bounds checking.
    // Throws std::out_of_range if index >= size().
    cout << "\nv.at(1) : " << v.at(1) << endl;  // 20

    // Safe bounds-check demo:
    try {
        cout << v.at(10) << endl;  // index 10 doesn't exist
    } catch (const out_of_range& e) {
        cout << "out_of_range caught: " << e.what() << endl;
    }

    // --- 3. front() ---
    // Returns a reference to the FIRST element.
    // Undefined behaviour on an empty vector.
    cout << "\nv.front() : " << v.front() << endl;  // 10

    v.front() = 5;   // modify through the reference
    cout << "v.front() after assignment: " << v.front() << endl;  // 5
    v.front() = 10;  // restore

    // --- 4. back() ---
    // Returns a reference to the LAST element.
    cout << "\nv.back() : " << v.back() << endl;  // 50

    v.back() = 99;
    cout << "v.back() after assignment: " << v.back() << endl;  // 99
    v.back() = 50;  // restore

    // --- 5. data() ---
    // Returns a raw pointer to the underlying contiguous array.
    // Useful when you need to pass to C-style APIs.
    int* raw = v.data();
    cout << "\nraw pointer v.data()[0] : " << raw[0] << endl;   // 10
    cout << "raw pointer v.data()[3] : " << raw[3] << endl;   // 40

    // Modify through the raw pointer:
    raw[0] = 77;
    cout << "v[0] after raw modification: " << v[0] << endl;  // 77
    v[0] = 10;  // restore

    // --- 6. Const correctness ---
    // With a const vector, you get const references — no modification allowed.
    const vector<int> cv = {100, 200, 300};
    cout << "\ncv[0]     : " << cv[0]      << endl;  // 100
    cout << "cv.at(1)  : " << cv.at(1)   << endl;  // 200
    cout << "cv.front(): " << cv.front() << endl;  // 100
    cout << "cv.back() : " << cv.back()  << endl;  // 300
    // cv[0] = 5;  // ERROR: cannot modify a const vector

    // --- 7. Accessing in a range-based for loop ---
    cout << "\nRange-for (copy)     : ";
    for (int x : v) cout << x << " ";   // each x is a copy
    cout << endl;

    cout << "Range-for (reference): ";
    for (int& x : v) cout << x << " ";  // x is a reference; modification is possible
    cout << endl;

    cout << "Range-for (const ref): ";
    for (const int& x : v) cout << x << " ";  // read-only, avoids copying
    cout << endl;

    // --- 8. Accessing with index loop ---
    cout << "\nIndex loop: ";
    for (size_t i = 0; i < v.size(); i++) {
        cout << "v[" << i << "]=" << v[i] << " ";
    }
    cout << endl;

    return 0;
}
