// 06_vector_algorithms.cpp
// Topic: Using <algorithm> with vectors
//        sort, reverse, find, count, fill, transform,
//        min/max_element, accumulate, unique, remove_if

#include <iostream>
#include <vector>
#include <algorithm>   // sort, reverse, find, count, fill, transform,
                       // min_element, max_element, unique, remove_if
#include <numeric>     // accumulate, iota
using namespace std;

void print(const string& label, const vector<int>& v) {
    cout << label << ": ";
    for (int x : v) cout << x << " ";
    cout << endl;
}

int main() {
    // =====================================================================
    // SORTING
    // =====================================================================

    // --- 1. sort() — ascending (default) ---
    // Uses introsort (hybrid quicksort + heapsort). Average O(n log n).
    vector<int> v = {5, 2, 8, 1, 9, 3};
    sort(v.begin(), v.end());
    print("sort ascending", v);   // 1 2 3 5 8 9

    // --- 2. sort() — descending with comparator ---
    sort(v.begin(), v.end(), greater<int>());
    print("sort descending", v);  // 9 8 5 3 2 1

    // --- 3. sort() — custom lambda comparator ---
    // Sort by absolute value:
    vector<int> mixed = {-3, 1, -7, 4, -2};
    sort(mixed.begin(), mixed.end(), [](int a, int b) {
        return abs(a) < abs(b);   // ascending absolute value
    });
    print("sort by |value|", mixed);  // 1 -2 -3 4 -7

    // --- 4. stable_sort() — preserves relative order of equal elements ---
    vector<pair<int,string>> data = {{2,"B"},{1,"A"},{2,"A"},{1,"B"}};
    stable_sort(data.begin(), data.end(), [](auto& a, auto& b){
        return a.first < b.first;   // sort by the int key
    });
    cout << "stable_sort by key: ";
    for (auto& p : data) cout << "(" << p.first << "," << p.second << ") ";
    cout << endl;

    // =====================================================================
    // REVERSING
    // =====================================================================

    // --- 5. reverse() ---
    vector<int> rv = {1, 2, 3, 4, 5};
    reverse(rv.begin(), rv.end());
    print("reverse", rv);  // 5 4 3 2 1

    // =====================================================================
    // SEARCHING
    // =====================================================================

    // --- 6. find() — linear search, returns iterator ---
    vector<int> sv = {10, 20, 30, 40, 50};
    auto pos = find(sv.begin(), sv.end(), 30);
    if (pos != sv.end())
        cout << "\nfind(30): found at index " << (pos - sv.begin()) << endl;
    else
        cout << "find: not found" << endl;

    // --- 7. find_if() — search with a predicate ---
    auto it = find_if(sv.begin(), sv.end(), [](int x){ return x > 25; });
    if (it != sv.end())
        cout << "find_if(x>25): first match = " << *it << endl;  // 30

    // --- 8. binary_search() — O(log n), vector MUST be sorted ---
    // Returns true/false only (no position).
    cout << "binary_search(30): " << boolalpha
         << binary_search(sv.begin(), sv.end(), 30) << endl;  // true

    // --- 9. lower_bound / upper_bound --- (sorted vectors only)
    // lower_bound: first position where value could be inserted (>= value)
    // upper_bound: first position strictly after all occurrences (> value)
    auto lo = lower_bound(sv.begin(), sv.end(), 30);
    auto hi = upper_bound(sv.begin(), sv.end(), 30);
    cout << "lower_bound(30) index: " << (lo - sv.begin()) << endl;  // 2
    cout << "upper_bound(30) index: " << (hi - sv.begin()) << endl;  // 3

    // =====================================================================
    // COUNTING
    // =====================================================================

    // --- 10. count() ---
    vector<int> nums = {1, 2, 2, 3, 2, 4, 2};
    cout << "\ncount(2): " << count(nums.begin(), nums.end(), 2) << endl;  // 4

    // --- 11. count_if() ---
    int evens = count_if(nums.begin(), nums.end(), [](int x){ return x % 2 == 0; });
    cout << "count_if(even): " << evens << endl;  // 4 (2,2,2,4,2)

    // =====================================================================
    // FILLING & GENERATING
    // =====================================================================

    // --- 12. fill() ---
    vector<int> fv(5);
    fill(fv.begin(), fv.end(), 7);
    print("\nfill(7)", fv);  // 7 7 7 7 7

    // --- 13. fill_n() ---
    fill_n(fv.begin(), 3, 0);  // fill first 3 elements with 0
    print("fill_n(3, 0)", fv);  // 0 0 0 7 7

    // --- 14. iota() — sequential values ---
    vector<int> seq(6);
    iota(seq.begin(), seq.end(), 1);  // 1, 2, 3, 4, 5, 6
    print("iota(1..6)", seq);

    // =====================================================================
    // TRANSFORMING
    // =====================================================================

    // --- 15. transform() — apply a function to each element ---
    vector<int> src = {1, 2, 3, 4, 5};
    vector<int> dst(src.size());
    transform(src.begin(), src.end(), dst.begin(),
              [](int x){ return x * x; });  // square each element
    print("transform(x*x)", dst);  // 1 4 9 16 25

    // transform with two input ranges:
    vector<int> a = {1,2,3}, b = {10,20,30}, c(3);
    transform(a.begin(), a.end(), b.begin(), c.begin(),
              [](int x, int y){ return x + y; });  // element-wise addition
    print("transform(a+b)", c);  // 11 22 33

    // =====================================================================
    // MIN / MAX
    // =====================================================================

    // --- 16. min_element / max_element --- returns an iterator
    vector<int> mv = {3, 1, 4, 1, 5, 9, 2, 6};
    auto minIt = min_element(mv.begin(), mv.end());
    auto maxIt = max_element(mv.begin(), mv.end());
    cout << "\nmin = " << *minIt << " at index " << (minIt - mv.begin()) << endl;
    cout << "max = " << *maxIt << " at index " << (maxIt - mv.begin()) << endl;

    // =====================================================================
    // ACCUMULATE / SUM
    // =====================================================================

    // --- 17. accumulate() — fold a range with a binary operation ---
    vector<int> nums2 = {1, 2, 3, 4, 5};
    int sum     = accumulate(nums2.begin(), nums2.end(), 0);       // sum
    int product = accumulate(nums2.begin(), nums2.end(), 1,
                             [](int acc, int x){ return acc * x; }); // product
    cout << "\naccumulate sum     = " << sum     << endl;  // 15
    cout << "accumulate product = " << product << endl;  // 120

    // =====================================================================
    // REMOVING DUPLICATES & FILTERING
    // =====================================================================

    // --- 18. unique() — remove consecutive duplicates ---
    // The vector must be SORTED first for all duplicates to be removed.
    // unique() moves duplicates to the end and returns an iterator to the
    // new logical end; you then erase the garbage at the end.
    vector<int> dup = {1, 1, 2, 3, 3, 3, 4, 5, 5};
    auto newEnd = unique(dup.begin(), dup.end());
    dup.erase(newEnd, dup.end());   // erase the moved-from elements
    print("unique", dup);           // 1 2 3 4 5

    // --- 19. remove_if() — erase-remove idiom ---
    // remove_if shifts "kept" elements forward; returns new logical end.
    // Must pair with erase() to actually shrink the vector.
    vector<int> vals = {1, 2, 3, 4, 5, 6, 7, 8};
    vals.erase(
        remove_if(vals.begin(), vals.end(), [](int x){ return x % 2 == 0; }),
        vals.end()
    );
    print("erase-remove_if (odds only)", vals);  // 1 3 5 7

    // =====================================================================
    // CHECKING CONDITIONS
    // =====================================================================

    // --- 20. all_of / any_of / none_of ---
    vector<int> pv = {2, 4, 6, 8};
    cout << "\nall_of even  : " << boolalpha << all_of(pv.begin(), pv.end(),  [](int x){ return x%2==0; }) << endl; // true
    cout << "any_of > 5   : " << any_of(pv.begin(),  pv.end(),  [](int x){ return x>5; })   << endl; // true
    cout << "none_of odd  : " << none_of(pv.begin(), pv.end(),  [](int x){ return x%2!=0; }) << endl; // true

    return 0;
}
