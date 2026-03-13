#include <iostream>
using namespace std;

// ─────────────────────────────────────────────────────────
// STATIC MEMBERS
// A static member belongs to the CLASS, not to any single object.
// All objects share the same static variable or method.
//
// Use cases:
//   - Counting how many objects have been created
//   - Shared configuration or utility functions
// ─────────────────────────────────────────────────────────

class Student {
private:
    string name;
    int    id;

    static int studentCount; // shared across ALL Student objects

public:
    // Constructor increments the shared counter each time a student is created
    Student(string n) : name(n) {
        studentCount++;        // increment the class-wide count
        id = studentCount;     // assign a unique id based on the count
        cout << "Student #" << id << " created: " << name << endl;
    }

    // Destructor decrements the counter when a student is destroyed
    ~Student() {
        studentCount--;
        cout << "Student destroyed: " << name << " (remaining: " << studentCount << ")" << endl;
    }

    // Static method — can be called WITHOUT creating an object
    // Note: static methods can ONLY access static members
    static int getCount() {
        return studentCount;
    }

    void displayInfo() {
        cout << "ID: " << id << " | Name: " << name << endl;
    }
};

// Define (and initialise) the static member OUTSIDE the class
int Student::studentCount = 0;

// ─────────────────────────────────────────────────────────
// Static inside a function — retains its value between calls
// ─────────────────────────────────────────────────────────
void callCounter() {
    static int callCount = 0; // initialised only once, persists across calls
    callCount++;
    cout << "callCounter() called " << callCount << " time(s)." << endl;
}

int main() {
    // Call static method WITHOUT any object — using class name
    cout << "Students at start: " << Student::getCount() << endl;

    Student s1("Alice");
    Student s2("Bob");
    Student s3("Charlie");

    cout << "\nCurrent student count: " << Student::getCount() << endl;

    cout << "\n--- Student info ---" << endl;
    s1.displayInfo();
    s2.displayInfo();
    s3.displayInfo();

    cout << "\n--- Static local variable in function ---" << endl;
    callCounter(); // 1
    callCounter(); // 2
    callCounter(); // 3

    cout << "\n--- End of main (destructors run) ---" << endl;
    return 0;
}
