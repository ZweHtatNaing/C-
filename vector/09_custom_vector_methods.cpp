// 09_custom_vector_methods.cpp
// Topic: Building your own Create / Read / Update / Delete / Merge
//        and utility methods on top of std::vector.
//
// This file wraps std::vector inside a templated class called VecBox<T>
// and implements common operations from scratch so you can see exactly
// what happens under the hood.

#include <iostream>
#include <vector>
#include <algorithm>   // find, find_if, sort, unique, set_union, set_intersection
#include <stdexcept>   // out_of_range, invalid_argument
#include <string>
#include <sstream>     // ostringstream
using namespace std;

// =========================================================================
// VecBox<T>  —  a wrapper around std::vector<T> with rich custom methods
// =========================================================================
template <typename T>
class VecBox {
private:
    vector<T> data;   // the underlying storage

public:
    // =====================================================================
    //  CONSTRUCTORS
    // =====================================================================

    // Default: empty box
    VecBox() = default;

    // From initialiser list:  VecBox<int> v = {1, 2, 3};
    VecBox(initializer_list<T> list) : data(list) {}

    // From an existing vector
    explicit VecBox(const vector<T>& v) : data(v) {}

    // Fill constructor: n copies of value
    VecBox(size_t n, const T& value) : data(n, value) {}

    // =====================================================================
    //  CREATE  —  adding new elements
    // =====================================================================

    // Append one element to the end
    void append(const T& value) {
        data.push_back(value);
    }

    // Append multiple elements from an initialiser list
    void appendAll(initializer_list<T> list) {
        for (const T& item : list) data.push_back(item);
    }

    // Insert at a specific index  (0-based)
    // Throws out_of_range if index > size
    void insertAt(size_t index, const T& value) {
        if (index > data.size())
            throw out_of_range("insertAt: index " + to_string(index) +
                               " is out of range (size=" + to_string(data.size()) + ")");
        data.insert(data.begin() + index, value);
    }

    // Prepend (insert at the front)
    void prepend(const T& value) {
        data.insert(data.begin(), value);
    }

    // Fill the box with n copies of value, replacing all existing content
    void fill(size_t n, const T& value) {
        data.assign(n, value);
    }

    // =====================================================================
    //  READ  —  querying and retrieving elements
    // =====================================================================

    // Get element by index (throws if out of range)
    T& get(size_t index) {
        if (index >= data.size())
            throw out_of_range("get: index " + to_string(index) + " out of range");
        return data[index];
    }

    const T& get(size_t index) const {
        if (index >= data.size())
            throw out_of_range("get: index " + to_string(index) + " out of range");
        return data[index];
    }

    // First element
    T& first() {
        if (data.empty()) throw out_of_range("first: vector is empty");
        return data.front();
    }

    // Last element
    T& last() {
        if (data.empty()) throw out_of_range("last: vector is empty");
        return data.back();
    }

    // Find the INDEX of the first occurrence of value (-1 if not found)
    int indexOf(const T& value) const {
        for (size_t i = 0; i < data.size(); i++)
            if (data[i] == value) return static_cast<int>(i);
        return -1;
    }

    // Find the INDEX of the last occurrence of value (-1 if not found)
    int lastIndexOf(const T& value) const {
        for (int i = static_cast<int>(data.size()) - 1; i >= 0; i--)
            if (data[i] == value) return i;
        return -1;
    }

    // Check whether a value exists
    bool contains(const T& value) const {
        return indexOf(value) != -1;
    }

    // Count how many times a value appears
    int countOf(const T& value) const {
        int n = 0;
        for (const T& item : data) if (item == value) n++;
        return n;
    }

    // Return all elements that satisfy a predicate as a new VecBox
    template <typename Predicate>
    VecBox<T> filter(Predicate pred) const {
        VecBox<T> result;
        for (const T& item : data)
            if (pred(item)) result.append(item);
        return result;
    }

    // =====================================================================
    //  UPDATE  —  modifying existing elements
    // =====================================================================

    // Update element at a given index
    void updateAt(size_t index, const T& newValue) {
        if (index >= data.size())
            throw out_of_range("updateAt: index " + to_string(index) + " out of range");
        data[index] = newValue;
    }

    // Replace the FIRST occurrence of oldValue with newValue
    // Returns true if a replacement was made
    bool replaceFirst(const T& oldValue, const T& newValue) {
        for (T& item : data) {
            if (item == oldValue) {
                item = newValue;
                return true;
            }
        }
        return false;
    }

    // Replace ALL occurrences of oldValue with newValue
    // Returns the number of replacements made
    int replaceAll(const T& oldValue, const T& newValue) {
        int count = 0;
        for (T& item : data) {
            if (item == oldValue) {
                item = newValue;
                count++;
            }
        }
        return count;
    }

    // Apply a transformation to every element in-place
    template <typename Transform>
    void applyAll(Transform func) {
        for (T& item : data) item = func(item);
    }

    // Apply a transformation only to elements that satisfy a predicate
    template <typename Predicate, typename Transform>
    void applyIf(Predicate pred, Transform func) {
        for (T& item : data)
            if (pred(item)) item = func(item);
    }

    // Swap elements at two indices
    void swapAt(size_t i, size_t j) {
        if (i >= data.size() || j >= data.size())
            throw out_of_range("swapAt: index out of range");
        swap(data[i], data[j]);
    }

    // =====================================================================
    //  DELETE  —  removing elements
    // =====================================================================

    // Remove element at a given index
    void removeAt(size_t index) {
        if (index >= data.size())
            throw out_of_range("removeAt: index " + to_string(index) + " out of range");
        data.erase(data.begin() + index);
    }

    // Remove the FIRST occurrence of value
    // Returns true if something was removed
    bool removeFirst(const T& value) {
        for (auto it = data.begin(); it != data.end(); ++it) {
            if (*it == value) {
                data.erase(it);
                return true;
            }
        }
        return false;
    }

    // Remove ALL occurrences of value
    // Returns the number of elements removed
    int removeAll(const T& value) {
        size_t before = data.size();
        data.erase(
            remove(data.begin(), data.end(), value),
            data.end()
        );
        return static_cast<int>(before - data.size());
    }

    // Remove all elements that satisfy a predicate
    template <typename Predicate>
    int removeIf(Predicate pred) {
        size_t before = data.size();
        data.erase(
            remove_if(data.begin(), data.end(), pred),
            data.end()
        );
        return static_cast<int>(before - data.size());
    }

    // Remove first element (pop front)
    void removeFirst() {
        if (data.empty()) throw out_of_range("removeFirst: vector is empty");
        data.erase(data.begin());
    }

    // Remove last element (pop back)
    void removeLast() {
        if (data.empty()) throw out_of_range("removeLast: vector is empty");
        data.pop_back();
    }

    // Remove elements in range [from, to)
    void removeRange(size_t from, size_t to) {
        if (from > to || to > data.size())
            throw out_of_range("removeRange: invalid range");
        data.erase(data.begin() + from, data.begin() + to);
    }

    // Remove all elements — size becomes 0
    void clear() {
        data.clear();
    }

    // Remove duplicate values (keeps first occurrence, order preserved)
    void removeDuplicates() {
        vector<T> seen;
        vector<T> result;
        for (const T& item : data) {
            if (find(seen.begin(), seen.end(), item) == seen.end()) {
                seen.push_back(item);
                result.push_back(item);
            }
        }
        data = move(result);
    }

    // =====================================================================
    //  MERGE  —  combining two VecBox objects
    // =====================================================================

    // Concatenate: append all elements of other at the end
    void merge(const VecBox<T>& other) {
        data.insert(data.end(), other.data.begin(), other.data.end());
    }

    // Return a NEW VecBox that is the concatenation of *this and other
    VecBox<T> merged(const VecBox<T>& other) const {
        VecBox<T> result(*this);
        result.merge(other);
        return result;
    }

    // Merge and remove duplicates (unique elements from both, order preserved)
    VecBox<T> mergeUnique(const VecBox<T>& other) const {
        VecBox<T> result(*this);
        for (const T& item : other.data)
            if (!result.contains(item)) result.append(item);
        return result;
    }

    // Set INTERSECTION: elements present in BOTH boxes (both must be sorted)
    VecBox<T> intersection(const VecBox<T>& other) const {
        VecBox<T> a(*this), b(other);
        a.sortAsc(); b.sortAsc();
        VecBox<T> result;
        set_intersection(a.data.begin(), a.data.end(),
                         b.data.begin(), b.data.end(),
                         back_inserter(result.data));
        return result;
    }

    // Set DIFFERENCE: elements in *this that are NOT in other (both must be sorted)
    VecBox<T> difference(const VecBox<T>& other) const {
        VecBox<T> a(*this), b(other);
        a.sortAsc(); b.sortAsc();
        VecBox<T> result;
        set_difference(a.data.begin(), a.data.end(),
                       b.data.begin(), b.data.end(),
                       back_inserter(result.data));
        return result;
    }

    // =====================================================================
    //  SORT  —  ordering elements
    // =====================================================================

    void sortAsc() {
        sort(data.begin(), data.end());
    }

    void sortDesc() {
        sort(data.begin(), data.end(), greater<T>());
    }

    template <typename Comparator>
    void sortBy(Comparator cmp) {
        sort(data.begin(), data.end(), cmp);
    }

    void reverse() {
        std::reverse(data.begin(), data.end());
    }

    // =====================================================================
    //  SPLIT  —  breaking into smaller VecBox objects
    // =====================================================================

    // Split into two halves: [0, mid) and [mid, end)
    pair<VecBox<T>, VecBox<T>> splitAt(size_t mid) const {
        if (mid > data.size())
            throw out_of_range("splitAt: index out of range");
        VecBox<T> left(vector<T>(data.begin(), data.begin() + mid));
        VecBox<T> right(vector<T>(data.begin() + mid, data.end()));
        return {left, right};
    }

    // Split into chunks of a given size
    vector<VecBox<T>> chunk(size_t chunkSize) const {
        if (chunkSize == 0) throw invalid_argument("chunk: size must be > 0");
        vector<VecBox<T>> chunks;
        for (size_t i = 0; i < data.size(); i += chunkSize) {
            size_t end = min(i + chunkSize, data.size());
            chunks.push_back(VecBox<T>(vector<T>(data.begin() + i, data.begin() + end)));
        }
        return chunks;
    }

    // Partition into two boxes: elements where pred is true, and where it's false
    pair<VecBox<T>, VecBox<T>> partition(function<bool(const T&)> pred) const {
        VecBox<T> yes, no;
        for (const T& item : data)
            (pred(item) ? yes : no).append(item);
        return {yes, no};
    }

    // =====================================================================
    //  UTILITY
    // =====================================================================

    size_t size()  const { return data.size(); }
    bool   empty() const { return data.empty(); }

    // Access the underlying std::vector (read-only)
    const vector<T>& toVector() const { return data; }

    // String representation
    string toString() const {
        ostringstream oss;
        oss << "[";
        for (size_t i = 0; i < data.size(); i++) {
            oss << data[i];
            if (i + 1 < data.size()) oss << ", ";
        }
        oss << "]";
        return oss.str();
    }

    // Print to cout with an optional label
    void print(const string& label = "") const {
        if (!label.empty()) cout << label << ": ";
        cout << toString() << endl;
    }

    // Equality check
    bool operator==(const VecBox<T>& other) const { return data == other.data; }
    bool operator!=(const VecBox<T>& other) const { return data != other.data; }

    // [] operator for direct access (no bounds check)
    T& operator[](size_t i) { return data[i]; }
    const T& operator[](size_t i) const { return data[i]; }
};


// =========================================================================
//  MAIN  —  demonstrate every method
// =========================================================================
int main() {
    cout << "========================================\n";
    cout << "  VecBox<T> — Custom Vector Methods Demo\n";
    cout << "========================================\n\n";

    // -----------------------------------------------------------------------
    //  CREATE
    // -----------------------------------------------------------------------
    cout << "--- CREATE ---\n";

    VecBox<int> v = {3, 1, 4, 1, 5, 9, 2, 6};
    v.print("Initial");

    v.append(7);
    v.print("After append(7)");

    v.appendAll({10, 11, 12});
    v.print("After appendAll({10,11,12})");

    v.insertAt(2, 99);
    v.print("After insertAt(2, 99)");

    v.prepend(0);
    v.print("After prepend(0)");

    VecBox<int> filled;
    filled.fill(5, 3);
    filled.print("fill(5, 3)");

    // -----------------------------------------------------------------------
    //  READ
    // -----------------------------------------------------------------------
    cout << "\n--- READ ---\n";

    cout << "get(0)        = " << v.get(0)            << "\n";
    cout << "first()       = " << v.first()           << "\n";
    cout << "last()        = " << v.last()            << "\n";
    cout << "indexOf(9)    = " << v.indexOf(9)        << "\n";   // first 9
    cout << "lastIndexOf(1)= " << v.lastIndexOf(1)    << "\n";
    cout << "contains(99)  = " << boolalpha << v.contains(99) << "\n";
    cout << "countOf(1)    = " << v.countOf(1)        << "\n";

    // filter: keep only values > 5
    v.filter([](int x){ return x > 5; }).print("filter(x > 5)");

    // -----------------------------------------------------------------------
    //  UPDATE
    // -----------------------------------------------------------------------
    cout << "\n--- UPDATE ---\n";

    v.print("Before updates");

    v.updateAt(0, 100);
    v.print("After updateAt(0, 100)");

    bool replaced = v.replaceFirst(99, 77);
    cout << "replaceFirst(99→77): " << replaced << "\n";
    v.print("After replaceFirst");

    int cnt = v.replaceAll(1, 88);
    cout << "replaceAll(1→88): replaced " << cnt << " times\n";
    v.print("After replaceAll");

    // multiply every element by 2
    v.applyAll([](int x){ return x * 2; });
    v.print("After applyAll(x*2)");

    // add 1 only to elements > 10
    v.applyIf([](int x){ return x > 10; }, [](int x){ return x + 1; });
    v.print("After applyIf(x>10, x+1)");

    v.swapAt(0, 1);
    v.print("After swapAt(0, 1)");

    // -----------------------------------------------------------------------
    //  DELETE
    // -----------------------------------------------------------------------
    cout << "\n--- DELETE ---\n";

    VecBox<int> d = {10, 20, 30, 20, 40, 20, 50};
    d.print("Before deletes");

    d.removeAt(2);
    d.print("After removeAt(2)");

    d.removeFirst(20);
    d.print("After removeFirst(20)");

    int removed = d.removeAll(20);
    cout << "removeAll(20): removed " << removed << " elements\n";
    d.print("After removeAll(20)");

    d.removeFirst();
    d.print("After removeFirst()");

    d.removeLast();
    d.print("After removeLast()");

    VecBox<int> rd = {1, 2, 3, 4, 5, 6, 7, 8};
    rd.removeRange(2, 5);     // removes indices 2,3,4 → values 3,4,5
    rd.print("After removeRange(2,5)");

    int ri = rd.removeIf([](int x){ return x % 2 == 0; });
    cout << "removeIf(even): removed " << ri << " elements\n";
    rd.print("After removeIf(even)");

    VecBox<int> dup = {1, 2, 2, 3, 1, 4, 3};
    dup.removeDuplicates();
    dup.print("After removeDuplicates");

    // -----------------------------------------------------------------------
    //  MERGE
    // -----------------------------------------------------------------------
    cout << "\n--- MERGE ---\n";

    VecBox<int> a = {1, 2, 3};
    VecBox<int> b = {4, 5, 6};

    VecBox<int> ab = a.merged(b);
    ab.print("merged (a + b)");

    VecBox<int> x = {1, 2, 3, 4};
    VecBox<int> y = {3, 4, 5, 6};

    x.mergeUnique(y).print("mergeUnique (x ∪ y, no dups)");
    x.intersection(y).print("intersection (x ∩ y)");
    x.difference(y).print("difference (x - y)");

    // -----------------------------------------------------------------------
    //  SORT
    // -----------------------------------------------------------------------
    cout << "\n--- SORT ---\n";

    VecBox<int> sv = {5, 2, 8, 1, 9, 3};
    sv.sortAsc();   sv.print("sortAsc");
    sv.sortDesc();  sv.print("sortDesc");

    sv.sortBy([](int a, int b){ return (a % 3) < (b % 3); });
    sv.print("sortBy(a%3 < b%3)");

    sv.reverse();
    sv.print("reverse");

    // -----------------------------------------------------------------------
    //  SPLIT
    // -----------------------------------------------------------------------
    cout << "\n--- SPLIT ---\n";

    VecBox<int> sp = {1, 2, 3, 4, 5, 6, 7, 8};
    auto [left, right] = sp.splitAt(4);
    left.print("splitAt(4) → left");
    right.print("splitAt(4) → right");

    auto chunks = sp.chunk(3);
    for (size_t i = 0; i < chunks.size(); i++)
        chunks[i].print("chunk[" + to_string(i) + "]");

    auto [evens, odds] = sp.partition([](const int& x){ return x % 2 == 0; });
    evens.print("partition → evens");
    odds.print("partition → odds");

    // -----------------------------------------------------------------------
    //  UTILITY
    // -----------------------------------------------------------------------
    cout << "\n--- UTILITY ---\n";

    VecBox<int> uv = {4, 5, 6};
    cout << "size()   = " << uv.size()  << "\n";
    cout << "empty()  = " << boolalpha << uv.empty() << "\n";
    cout << "toString = " << uv.toString() << "\n";

    VecBox<int> uv2 = {4, 5, 6};
    cout << "uv == uv2: " << (uv == uv2) << "\n";
    uv2.append(7);
    cout << "uv == uv2 after append: " << (uv == uv2) << "\n";

    // -----------------------------------------------------------------------
    //  STRING SPECIALISATION DEMO
    // -----------------------------------------------------------------------
    cout << "\n--- STRING SPECIALISATION ---\n";

    VecBox<string> words = {"banana", "apple", "cherry", "date", "apple"};
    words.print("Original strings");

    words.sortAsc();
    words.print("sortAsc");

    words.removeAll("apple");
    words.print("After removeAll(\"apple\")");

    words.replaceFirst("banana", "blueberry");
    words.print("After replaceFirst(\"banana\"→\"blueberry\")");

    words.filter([](const string& s){ return s.size() > 5; }).print("filter(len > 5)");

    return 0;
}
