// 10_smart_pointers.cpp
// Topic: Smart Pointers (C++11+)
//        unique_ptr, shared_ptr, weak_ptr
//        Smart pointers automatically manage memory (no manual delete needed).

#include <iostream>
#include <memory>   // required for all smart pointers
using namespace std;

// A simple class to observe construction / destruction
struct Animal {
    string name;
    Animal(const string& n) : name(n) {
        cout << "  [+] Animal created : " << name << endl;
    }
    ~Animal() {
        cout << "  [-] Animal destroyed: " << name << endl;
    }
    void speak() const { cout << "  " << name << " says hello!" << endl; }
};

// ============================================================
// PART 1: unique_ptr
// ============================================================
// Owns the resource EXCLUSIVELY. Cannot be copied, only moved.
// Resource is freed automatically when the unique_ptr goes out of scope.
void demoUniquePtr() {
    cout << "\n=== unique_ptr ===\n";

    // --- 1. Create a unique_ptr with make_unique (preferred) ---
    unique_ptr<Animal> up1 = make_unique<Animal>("Dog");

    // --- 2. Access the managed object with -> or * ---
    up1->speak();            // '->' works like a normal pointer
    (*up1).speak();          // dereference with '*'

    // --- 3. unique_ptr CANNOT be copied ---
    // unique_ptr<Animal> up2 = up1;  // ERROR: copy is deleted

    // --- 4. Ownership can be TRANSFERRED (moved) ---
    unique_ptr<Animal> up2 = std::move(up1);  // up1 is now empty (nullptr)
    if (!up1) cout << "  up1 is now empty after move\n";
    up2->speak();  // up2 now owns the Dog

    // --- 5. Release ownership without deleting ---
    Animal* rawPtr = up2.release();  // up2 is now empty; we own rawPtr manually
    cout << "  Released. up2 is empty: " << (up2 == nullptr) << endl;
    delete rawPtr;  // must manually delete because we released ownership

    // --- 6. unique_ptr for arrays ---
    unique_ptr<int[]> arr = make_unique<int[]>(5);  // array of 5 ints
    for (int i = 0; i < 5; i++) arr[i] = i * 2;
    cout << "  arr[3] = " << arr[3] << endl;  // 6
    // arr is freed automatically when it leaves scope

    cout << "  (up1's Dog is destroyed when up2 goes out of scope)\n";
}   // up2 goes out of scope here -> Dog is automatically destroyed

// ============================================================
// PART 2: shared_ptr
// ============================================================
// Shared OWNERSHIP: multiple shared_ptrs can point to the same resource.
// Uses a REFERENCE COUNT; resource is freed when count reaches 0.
void demoSharedPtr() {
    cout << "\n=== shared_ptr ===\n";

    // --- 7. Create a shared_ptr ---
    shared_ptr<Animal> sp1 = make_shared<Animal>("Cat");
    cout << "  use_count: " << sp1.use_count() << endl;  // 1

    // --- 8. Copying a shared_ptr increases the reference count ---
    shared_ptr<Animal> sp2 = sp1;  // both sp1 and sp2 own the Cat
    cout << "  use_count after copy: " << sp1.use_count() << endl;  // 2

    {
        shared_ptr<Animal> sp3 = sp1;  // a third owner
        cout << "  use_count inside block: " << sp1.use_count() << endl;  // 3
        sp3->speak();
    }   // sp3 goes out of scope; count drops to 2

    cout << "  use_count after block: " << sp1.use_count() << endl;  // 2

    sp2.reset();  // sp2 relinquishes ownership; count drops to 1
    cout << "  use_count after sp2.reset(): " << sp1.use_count() << endl;  // 1

    // Cat will be destroyed when sp1 goes out of scope
}   // sp1 goes out of scope -> Cat is destroyed

// ============================================================
// PART 3: weak_ptr
// ============================================================
// A NON-OWNING observer of a shared_ptr-managed resource.
// Does NOT increase the reference count.
// Used to BREAK CIRCULAR REFERENCES that would cause memory leaks.
void demoWeakPtr() {
    cout << "\n=== weak_ptr ===\n";

    shared_ptr<Animal> sp = make_shared<Animal>("Bird");
    cout << "  use_count: " << sp.use_count() << endl;  // 1

    // --- 9. Create a weak_ptr from a shared_ptr ---
    weak_ptr<Animal> wp = sp;  // wp observes sp but does NOT increase count
    cout << "  use_count after weak_ptr: " << sp.use_count() << endl;  // still 1

    // --- 10. Check if the resource still exists before using it ---
    if (!wp.expired()) {
        // lock() converts weak_ptr to a temporary shared_ptr (safe access)
        shared_ptr<Animal> temp = wp.lock();
        if (temp) {
            temp->speak();  // safe: resource is still alive
            cout << "  use_count during lock: " << sp.use_count() << endl;  // 2
        }
    }   // temp goes out of scope; count drops back to 1

    // --- 11. What happens when the resource is destroyed ---
    sp.reset();  // destroy the shared_ptr; reference count -> 0 -> Animal destroyed
    cout << "  wp.expired() after sp.reset(): " << wp.expired() << endl;  // true (1)
}

int main() {
    demoUniquePtr();
    demoSharedPtr();
    demoWeakPtr();

    cout << "\nDone. All smart-pointer managed resources freed automatically.\n";
    return 0;
}
