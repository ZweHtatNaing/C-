# C++ Vectors

`std::vector` is a dynamic array from the C++ Standard Library. Unlike plain C arrays, a vector grows and shrinks automatically, always stores elements contiguously in memory, and manages its own heap allocation.

```cpp
#include <vector>
using namespace std;
```

---

## Table of Contents

1. [Basics — Declaration & Initialization](#1-basics--declaration--initialization)
2. [Element Access](#2-element-access)
3. [Modifiers](#3-modifiers)
4. [Size vs Capacity](#4-size-vs-capacity)
5. [Iterators](#5-iterators)
6. [Algorithms](#6-algorithms)
7. [2D Vectors](#7-2d-vectors)
8. [Vector of Objects](#8-vector-of-objects)
9. [Quick Reference](#quick-reference)
10. [Common Pitfalls](#common-pitfalls)

---

## 1. Basics — Declaration & Initialization

**File:** `01_vector_basics.cpp`

| Constructor | Result |
|---|---|
| `vector<int> v` | Empty vector |
| `vector<int> v(5, 10)` | `{10, 10, 10, 10, 10}` |
| `vector<int> v = {1,2,3}` | `{1, 2, 3}` |
| `vector<int> v(4)` | `{0, 0, 0, 0}` (zero-init) |
| `vector<int> v(other)` | Deep copy of `other` |
| `vector<int> v(other.begin()+1, other.end())` | Range copy |
| `vector<int> v(move(other))` | Move — `other` becomes empty |

```cpp
vector<int>    iv = {1, 2, 3};
vector<double> dv = {1.1, 2.2};
vector<string> sv = {"hello", "world"};
vector<bool>   bv = {true, false, true};

// 2D vector
vector<vector<int>> matrix = {{1,2},{3,4}};
```

---

## 2. Element Access

**File:** `02_vector_access.cpp`

| Method | Description | Bounds Check |
|---|---|---|
| `v[i]` | Access element at index `i` | No — UB if out of range |
| `v.at(i)` | Access element at index `i` | Yes — throws `std::out_of_range` |
| `v.front()` | First element | No |
| `v.back()` | Last element | No |
| `v.data()` | Raw pointer to underlying array | — |

```cpp
vector<int> v = {10, 20, 30};

v[0];         // 10 (fast, no check)
v.at(1);      // 20 (safe, throws on bad index)
v.front();    // 10
v.back();     // 30
v.data();     // int* to first element

v[1] = 99;    // modify via []
v.front() = 5; // modify via front()
```

**Prefer `const&` in loops for efficiency:**
```cpp
for (const int& x : v) cout << x;   // no copy, read-only
for (int& x : v) x *= 2;            // modify in place
```

---

## 3. Modifiers

**File:** `03_vector_modifiers.cpp`

### Adding Elements

| Method | Description | Complexity |
|---|---|---|
| `v.push_back(val)` | Append a copy to the end | Amortised O(1) |
| `v.emplace_back(args...)` | Construct in-place at the end | Amortised O(1) |
| `v.insert(it, val)` | Insert before position `it` | O(n) |
| `v.insert(it, n, val)` | Insert `n` copies before `it` | O(n) |
| `v.insert(it, first, last)` | Insert range before `it` | O(n) |
| `v.emplace(it, args...)` | Construct in-place before `it` | O(n) |

### Removing Elements

| Method | Description | Complexity |
|---|---|---|
| `v.pop_back()` | Remove last element | O(1) |
| `v.erase(it)` | Remove element at `it` | O(n) |
| `v.erase(first, last)` | Remove range `[first, last)` | O(n) |
| `v.clear()` | Remove all elements (size→0) | O(n) |

### Resizing & Replacing

```cpp
v.resize(6);        // grow with zeros
v.resize(6, 7);     // grow with value 7
v.resize(2);        // shrink, drops trailing elements
v.assign(4, 99);    // replace contents with four 99s
v.assign({1,2,3});  // replace with initialiser list
v.swap(other);      // swap contents in O(1)
```

> **Tip:** Prefer `emplace_back` over `push_back` for objects — it constructs directly in-place without a temporary.

---

## 4. Size vs Capacity

**File:** `04_vector_capacity.cpp`

```
Memory layout  (size=4, capacity=8):
[ A | B | C | D | _ | _ | _ | _ ]
  <---  size  --->  <- spare slots->
  <---------  capacity  ---------->
```

| Method | Description |
|---|---|
| `v.size()` | Number of elements currently stored |
| `v.capacity()` | Slots allocated before next reallocation |
| `v.empty()` | `true` if `size() == 0` |
| `v.max_size()` | Theoretical maximum elements |
| `v.reserve(n)` | Pre-allocate for at least `n` elements |
| `v.shrink_to_fit()` | Request `capacity` → `size` (non-binding) |

```cpp
vector<int> v;
v.reserve(1000);          // one allocation, no reallocations during fill
for (int i = 0; i < 1000; i++) v.push_back(i);
```

**When capacity is exceeded, the vector typically doubles its buffer (O(log n) total reallocations).**

---

## 5. Iterators

**File:** `05_vector_iterators.cpp`

| Iterator | Points to |
|---|---|
| `v.begin()` | First element |
| `v.end()` | One past the last (sentinel — don't dereference) |
| `v.rbegin()` | Last element (reverse) |
| `v.rend()` | One before first (reverse sentinel) |
| `v.cbegin()` / `v.cend()` | Const iterators (read-only) |

```cpp
// Forward loop
for (auto it = v.begin(); it != v.end(); ++it)
    cout << *it;

// Reverse loop
for (auto it = v.rbegin(); it != v.rend(); ++it)
    cout << *it;

// Iterator arithmetic
auto mid = v.begin() + v.size() / 2;   // middle element
auto dist = v.end() - v.begin();        // == v.size()
advance(it, 3);                         // move 3 steps
distance(v.begin(), it);                // steps from begin to it
```

> **Warning:** Iterators are **invalidated** after `push_back`, `insert`, or `erase` if a reallocation occurs. Always re-obtain iterators after modifying the vector.

---

## 6. Algorithms

**File:** `06_vector_algorithms.cpp`

Combine `#include <algorithm>` and `#include <numeric>` with vectors:

### Sorting
```cpp
sort(v.begin(), v.end());                       // ascending
sort(v.begin(), v.end(), greater<int>());       // descending
sort(v.begin(), v.end(), [](int a, int b){ return abs(a) < abs(b); }); // custom
stable_sort(v.begin(), v.end(), cmp);           // preserves equal-element order
```

### Searching
```cpp
find(v.begin(), v.end(), 30);                   // linear search → iterator
find_if(v.begin(), v.end(), [](int x){ return x > 25; });
binary_search(v.begin(), v.end(), 30);          // true/false (sorted only)
lower_bound(v.begin(), v.end(), 30);            // first >= 30 (sorted)
upper_bound(v.begin(), v.end(), 30);            // first >  30 (sorted)
```

### Counting & Checking
```cpp
count(v.begin(), v.end(), 2);                   // count occurrences
count_if(v.begin(), v.end(), [](int x){ return x%2==0; });
all_of(v.begin(), v.end(), pred);
any_of(v.begin(), v.end(), pred);
none_of(v.begin(), v.end(), pred);
```

### Transforming
```cpp
reverse(v.begin(), v.end());
fill(v.begin(), v.end(), 7);
iota(v.begin(), v.end(), 1);                    // 1, 2, 3, ...
transform(v.begin(), v.end(), dst.begin(), [](int x){ return x*x; });
```

### Aggregating
```cpp
accumulate(v.begin(), v.end(), 0);              // sum
accumulate(v.begin(), v.end(), 1, [](int a, int b){ return a*b; }); // product
*min_element(v.begin(), v.end());
*max_element(v.begin(), v.end());
```

### Erase-Remove Idiom
```cpp
// Remove all even numbers
v.erase(remove_if(v.begin(), v.end(), [](int x){ return x%2==0; }), v.end());

// Remove consecutive duplicates (sort first for all duplicates)
v.erase(unique(v.begin(), v.end()), v.end());
```

---

## 7. 2D Vectors

**File:** `07_2d_vectors.cpp`

```cpp
// Fixed-size grid (rows x cols), filled with 0
vector<vector<int>> grid(rows, vector<int>(cols, 0));

// Access
grid[r][c]          // fast, no bounds check
grid.at(r).at(c)    // safe, throws out_of_range

// Dimensions
grid.size()         // number of rows
grid[0].size()      // number of columns in row 0

// Add / remove a row
grid.push_back(vector<int>(cols, 0));
grid.pop_back();

// Add / remove a column
for (auto& row : grid) row.push_back(0);
for (auto& row : grid) row.pop_back();
```

**Ragged (jagged) grid — each row can have a different length:**
```cpp
vector<vector<int>> triangle(5);
for (int r = 0; r < 5; r++)
    triangle[r].resize(r + 1);   // row 0 has 1 element, row 4 has 5
```

---

## 8. Vector of Objects

**File:** `08_vector_of_objects.cpp`

```cpp
struct Student {
    string name; int age; double gpa;
    Student(string n, int a, double g) : name(n), age(a), gpa(g) {}
};

vector<Student> v;
v.push_back(Student("Alice", 20, 3.9));  // copy
v.emplace_back("Bob", 22, 3.2);          // in-place (preferred)

// Sort by GPA descending
sort(v.begin(), v.end(), [](const Student& a, const Student& b){
    return a.gpa > b.gpa;
});

// Find by name
auto it = find_if(v.begin(), v.end(), [](const Student& s){
    return s.name == "Alice";
});

// Remove with predicate
v.erase(remove_if(v.begin(), v.end(), [](const Student& s){
    return s.age < 21;
}), v.end());
```

> **Always pass vectors of objects by `const&` to functions** to avoid expensive copying.

---

## Quick Reference

```cpp
// Creation
vector<int> v;                // empty
vector<int> v(5, 0);          // {0,0,0,0,0}
vector<int> v = {1,2,3};      // initialiser list

// Size & capacity
v.size()      v.capacity()    v.empty()    v.reserve(n)

// Access
v[i]          v.at(i)         v.front()    v.back()    v.data()

// Add
v.push_back(x)    v.emplace_back(x)    v.insert(it, x)

// Remove
v.pop_back()      v.erase(it)          v.clear()

// Resize / replace
v.resize(n)    v.resize(n, val)    v.assign(n, val)    v.swap(other)

// Iteration
for (int x : v)              // value copy
for (const int& x : v)       // const ref (preferred)
for (int& x : v)             // mutable ref
for (auto it = v.begin(); it != v.end(); ++it)
```

---

## Common Pitfalls

| Pitfall | Description | Fix |
|---|---|---|
| **Out-of-bounds `[]`** | `v[i]` with `i >= v.size()` is undefined behaviour | Use `v.at(i)` or check bounds manually |
| **Iterator invalidation** | Iterators go stale after `push_back`/`insert`/`erase` | Re-obtain iterators after modifying the vector |
| **Accessing empty vector** | `v.front()` or `v.back()` on an empty vector is UB | Check `!v.empty()` first |
| **`delete` vs `delete[]`** | N/A for vector — it manages memory automatically | Just let the vector go out of scope |
| **Copying large vectors** | Passing by value creates a full copy | Pass by `const&` or `&` |
| **`size()` is unsigned** | `v.size() - 1` underflows to a huge number when `v` is empty | Check `!v.empty()` before using `size() - 1` |
| **Sorting then invalidating** | `erase-remove` on a non-sorted vector leaves some duplicates | Sort before calling `unique()` |
