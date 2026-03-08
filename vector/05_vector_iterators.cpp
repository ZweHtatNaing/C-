// 05_vector_iterators.cpp
// Topic: Iterators - begin/end, rbegin/rend, cbegin/cend,
//        iterator arithmetic, and all loop styles

#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> v = {10, 20, 30, 40, 50};

    // =====================================================================
    // ITERATOR OVERVIEW
    // An iterator is an object that points to an element inside a container.
    // It behaves similarly to a pointer and supports:
    //   *it         -- dereference (get the value)
    //   it++/it--   -- advance or retreat by one element
    //   it + n      -- jump n elements forward
    //   it1 - it2   -- distance between two iterators
    //   it1 == it2  -- check if both point to the same position
    // =====================================================================

    // --- 1. begin() and end() ---
    // begin() points to the FIRST element.
    // end()   points ONE PAST the last element (sentinel — do not dereference).
    vector<int>::iterator it = v.begin();
    cout << "First element via begin(): " << *it << endl;  // 10

    // Advance the iterator:
    ++it;
    cout << "After ++it            : " << *it << endl;  // 20

    it = it + 2;
    cout << "After it + 2          : " << *it << endl;  // 40

    // --- 2. Forward loop with iterators ---
    cout << "\nForward iterator loop: ";
    for (auto iter = v.begin(); iter != v.end(); ++iter) {
        cout << *iter << " ";   // dereference to get the value
    }
    cout << endl;

    // --- 3. Modify elements through an iterator ---
    for (auto iter = v.begin(); iter != v.end(); ++iter) {
        *iter *= 2;   // double each element
    }
    cout << "After doubling: ";
    for (int x : v) cout << x << " ";
    cout << endl;

    // Restore original values:
    v = {10, 20, 30, 40, 50};

    // --- 4. rbegin() and rend() --- (reverse iterators)
    // rbegin() points to the LAST element.
    // rend()   points ONE BEFORE the first element (sentinel).
    cout << "\nReverse iterator loop: ";
    for (auto rit = v.rbegin(); rit != v.rend(); ++rit) {
        // Note: ++ on a reverse iterator moves BACKWARDS through the container
        cout << *rit << " ";   // 50 40 30 20 10
    }
    cout << endl;

    // --- 5. cbegin() / cend() --- (const iterators, C++11)
    // Returns a const_iterator — you can read but NOT modify elements.
    cout << "\nConst iterator loop: ";
    for (auto cit = v.cbegin(); cit != v.cend(); ++cit) {
        cout << *cit << " ";
        // *cit = 0;  // ERROR: const_iterator is read-only
    }
    cout << endl;

    // --- 6. crbegin() / crend() --- (const reverse iterators)
    cout << "Const reverse loop: ";
    for (auto crit = v.crbegin(); crit != v.crend(); ++crit) {
        cout << *crit << " ";
    }
    cout << endl;

    // --- 7. Iterator arithmetic ---
    auto first = v.begin();
    auto last  = v.end();

    cout << "\nDistance (end - begin) : " << (last - first) << endl;  // 5

    auto mid = v.begin() + v.size() / 2;  // point to middle element
    cout << "Middle element         : " << *mid << endl;  // 30

    // --- 8. std::advance and std::distance (from <iterator>) ---
    // advance(it, n) moves an iterator by n steps (works for non-random iterators too).
    // distance(it1, it2) returns the number of steps from it1 to it2.
    auto it2 = v.begin();
    advance(it2, 3);   // move 3 steps forward
    cout << "After advance(it, 3)   : " << *it2 << endl;  // 40

    cout << "distance(begin, it2)   : " << distance(v.begin(), it2) << endl;  // 3

    // --- 9. Using auto for clean iterator syntax (C++11) ---
    // 'auto' deduces the iterator type automatically.
    auto autoIt = v.begin();
    cout << "\nauto iterator value: " << *autoIt << endl;

    // --- 10. Range-based for loop (modern, preferred) ---
    // Internally uses begin()/end() — cleaner syntax for simple traversal.
    cout << "\nRange-for (value copy): ";
    for (int x : v) cout << x << " ";
    cout << endl;

    cout << "Range-for (const ref) : ";
    for (const int& x : v) cout << x << " ";   // efficient for large types
    cout << endl;

    cout << "Range-for (ref modify): ";
    for (int& x : v) x += 5;    // add 5 to each element
    for (int x : v) cout << x << " ";
    cout << endl;

    // --- 11. Invalidation warning ---
    // Iterators are INVALIDATED after:
    //   - push_back / emplace_back (if reallocation occurs)
    //   - insert / erase
    // Always re-obtain iterators after modifying the vector.
    cout << "\n(Iterators may be invalidated after push_back/insert/erase)" << endl;

    return 0;
}
