// 03_vector_modifiers.cpp
// Topic: Modifying a Vector
//        push_back, pop_back, insert, emplace_back, erase, clear, assign, resize, swap

#include <iostream>
#include <vector>
using namespace std;

// Helper: print a vector with a label
void print(const string& label, const vector<int>& v) {
    cout << label << " [size=" << v.size() << "]: ";
    for (int x : v) cout << x << " ";
    cout << endl;
}

int main() {
    // =====================================================================
    // ADDING ELEMENTS
    // =====================================================================

    // --- 1. push_back() ---
    // Appends a copy of the value to the END of the vector.
    // Amortised O(1) -- may reallocate if capacity is exceeded.
    vector<int> v;
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);
    print("After push_back x3", v);  // 10 20 30

    // --- 2. emplace_back() (C++11) ---
    // Constructs the element IN-PLACE at the end — avoids a copy/move.
    // Preferred over push_back for complex types (e.g., objects).
    v.emplace_back(40);  // identical to push_back for primitives
    v.emplace_back(50);
    print("After emplace_back x2", v);  // 10 20 30 40 50

    // --- 3. insert() — single element at a position ---
    // v.insert(iterator, value) inserts BEFORE the position.
    // O(n) because elements after the insertion point must shift.
    auto it = v.begin() + 2;   // iterator to index 2 (value 30)
    v.insert(it, 99);
    print("After insert at index 2", v);  // 10 20 99 30 40 50

    // --- 4. insert() — n copies of a value ---
    v.insert(v.begin(), 3, 0);  // insert 3 zeros at the front
    print("After insert 3 zeros at front", v);  // 0 0 0 10 20 99 30 40 50

    // --- 5. insert() — range from another vector ---
    vector<int> extra = {200, 300};
    v.insert(v.end(), extra.begin(), extra.end());  // append extra to the end
    print("After range insert at end", v);  // ... 200 300

    // --- 6. emplace() — in-place construct at a position (C++11) ---
    v.emplace(v.begin() + 1, 777);  // inserts 777 at index 1
    print("After emplace at index 1", v);

    // =====================================================================
    // REMOVING ELEMENTS
    // =====================================================================

    // --- 7. pop_back() ---
    // Removes the LAST element. O(1). Does NOT return the removed value.
    v.pop_back();
    print("After pop_back", v);

    // --- 8. erase() — single element ---
    // Removes the element at the given iterator position. O(n) shift.
    v.erase(v.begin());   // remove first element
    print("After erase first element", v);

    // --- 9. erase() — range [first, last) ---
    v.erase(v.begin(), v.begin() + 3);  // remove first 3 elements
    print("After erase first 3 elements", v);

    // --- 10. clear() ---
    // Removes ALL elements. Size becomes 0; capacity is unchanged.
    vector<int> temp = {1, 2, 3};
    cout << "\nBefore clear: size=" << temp.size() << " cap=" << temp.capacity() << endl;
    temp.clear();
    cout << "After  clear: size=" << temp.size() << " cap=" << temp.capacity() << endl;

    // =====================================================================
    // RESIZING
    // =====================================================================

    // --- 11. resize(n) ---
    // If n > current size: appends zero-initialised elements.
    // If n < current size: removes trailing elements.
    vector<int> rv = {1, 2, 3};
    rv.resize(6);          // grows: {1, 2, 3, 0, 0, 0}
    print("\nAfter resize(6)", rv);

    rv.resize(2);          // shrinks: {1, 2}
    print("After resize(2)", rv);

    // --- 12. resize(n, value) ---
    // Same as resize(n) but fills new elements with value instead of 0.
    rv.resize(5, 7);       // {1, 2, 7, 7, 7}
    print("After resize(5, 7)", rv);

    // =====================================================================
    // REPLACING / ASSIGNING
    // =====================================================================

    // --- 13. assign() --- replaces the entire contents
    vector<int> av;
    av.assign(4, 99);              // four 99s
    print("\nAfter assign(4, 99)", av);

    av.assign({5, 6, 7, 8, 9});   // from initialiser list
    print("After assign list", av);

    av.assign(rv.begin(), rv.end()); // copy from another vector
    print("After assign from rv", av);

    // =====================================================================
    // SWAPPING
    // =====================================================================

    // --- 14. swap() ---
    // Swaps the contents of two vectors in O(1) — no element copying.
    vector<int> a = {1, 2, 3};
    vector<int> b = {9, 8, 7, 6};
    cout << "\nBefore swap: ";
    print("a", a); print("b", b);
    a.swap(b);
    print("a after swap", a);   // was b
    print("b after swap", b);   // was a

    return 0;
}
