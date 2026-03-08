// 04_vector_capacity.cpp
// Topic: Size vs Capacity - size(), capacity(), empty(),
//        reserve(), resize(), shrink_to_fit()

#include <iostream>
#include <vector>
using namespace std;

int main() {
    // =====================================================================
    // SIZE vs CAPACITY
    //
    //  size()     = number of elements currently stored
    //  capacity() = number of elements the allocated buffer CAN hold
    //               before a reallocation is needed
    //
    //  Memory layout (capacity=8, size=4):
    //  [ A | B | C | D | _ | _ | _ | _ ]
    //    <---   size   ---> <-- spare -->
    //    <----------  capacity  -------->
    // =====================================================================

    // --- 1. Default construction: size=0, capacity=0 ---
    vector<int> v;
    cout << "Empty vector  | size=" << v.size()
         << "  capacity=" << v.capacity() << endl;

    // --- 2. Watch capacity grow as we push_back ---
    // The standard typically DOUBLES capacity when the buffer is full
    // (implementation-defined, but usually x2 growth).
    cout << "\npush_back growth pattern:" << endl;
    size_t lastCap = 0;
    for (int i = 1; i <= 20; i++) {
        v.push_back(i);
        if (v.capacity() != lastCap) {
            cout << "  size=" << v.size()
                 << "  capacity=" << v.capacity()
                 << "  (reallocation!)" << endl;
            lastCap = v.capacity();
        }
    }

    // --- 3. size() ---
    // Returns the number of elements currently stored.
    cout << "\nv.size()     : " << v.size()     << endl;  // 20

    // --- 4. capacity() ---
    // Returns the total allocated slots (>= size).
    cout << "v.capacity() : " << v.capacity() << endl;  // implementation-defined (e.g. 32)

    // --- 5. empty() ---
    // Returns true only when size() == 0. Prefer over (size() == 0).
    cout << "v.empty()    : " << boolalpha << v.empty() << endl;  // false

    vector<int> empty_v;
    cout << "empty_v.empty(): " << empty_v.empty() << endl;  // true

    // --- 6. max_size() ---
    // The theoretical maximum number of elements the vector could ever hold
    // (limited by the system's addressable memory).
    cout << "v.max_size() : " << v.max_size() << endl;

    // =====================================================================
    // CONTROLLING CAPACITY
    // =====================================================================

    // --- 7. reserve(n) ---
    // Pre-allocates memory for at least n elements.
    // Does NOT change size(). Avoids repeated reallocations when
    // you know (or can estimate) the final size in advance.
    vector<int> rv;
    rv.reserve(100);  // allocate buffer for 100 elements
    cout << "\nAfter reserve(100) | size=" << rv.size()
         << "  capacity=" << rv.capacity() << endl;  // size=0, cap>=100

    // Now fill it — no reallocations will happen up to 100 elements:
    for (int i = 0; i < 50; i++) rv.push_back(i);
    cout << "After 50 push_backs | size=" << rv.size()
         << "  capacity=" << rv.capacity() << endl;  // size=50, cap>=100

    // reserve() is a no-op if n <= current capacity:
    rv.reserve(10);  // ignored — current capacity already > 10
    cout << "After reserve(10)   | capacity=" << rv.capacity() << endl;  // unchanged

    // --- 8. shrink_to_fit() ---
    // Non-binding request to reduce capacity to match size().
    // The implementation may or may not honour it.
    rv.shrink_to_fit();
    cout << "After shrink_to_fit | size=" << rv.size()
         << "  capacity=" << rv.capacity() << endl;  // ideally size == capacity

    // --- 9. The "swap trick" — guaranteed shrink (pre-C++11) ---
    // Swap with a freshly constructed vector that holds the same data.
    // The temporary dies immediately, releasing the excess memory.
    vector<int> big(1000);
    big.resize(3);
    cout << "\nBig after resize(3) | size=" << big.size()
         << "  cap=" << big.capacity() << endl;

    vector<int>(big).swap(big);   // copy into temp, swap, temp destroyed
    cout << "After swap trick    | size=" << big.size()
         << "  cap=" << big.capacity() << endl;  // cap = 3

    // --- 10. Performance guideline: use reserve() to avoid reallocations ---
    // Without reserve: multiple reallocations when filling a large vector.
    // With    reserve: zero reallocations.
    vector<int> slow, fast;
    fast.reserve(10000);

    // Both end up identical, but 'fast' never reallocates:
    for (int i = 0; i < 10000; i++) {
        slow.push_back(i);
        fast.push_back(i);
    }
    cout << "\nslow.size()=" << slow.size()
         << "  slow.capacity()=" << slow.capacity() << endl;
    cout << "fast.size()=" << fast.size()
         << "  fast.capacity()=" << fast.capacity() << endl;

    return 0;
}
