#include <iostream>
using namespace std;

// ─────────────────────────────────────────────────────────
// BASIC CLASS
// A class bundles data (attributes) and behaviour (methods)
// into one unit.
//
// Constructor  — called automatically when an object is created
// Destructor   — called automatically when an object is destroyed
// ─────────────────────────────────────────────────────────

class Car {
public:
    // Attributes (data members)
    string brand;
    string model;
    int    year;

    // Default constructor — no arguments needed
    Car() {
        brand = "Unknown";
        model = "Unknown";
        year  = 0;
        cout << "Car created (default)" << endl;
    }

    // Parameterized constructor — sets values at creation time
    Car(string b, string m, int y) {
        brand = b;
        model = m;
        year  = y;
        cout << "Car created: " << brand << " " << model << endl;
    }

    // Copy constructor — creates a new object as a copy of an existing one
    Car(const Car& other) {
        brand = other.brand;
        model = other.model;
        year  = other.year;
        cout << "Car copied: " << brand << " " << model << endl;
    }

    // Destructor — runs when the object goes out of scope or is deleted
    ~Car() {
        cout << "Car destroyed: " << brand << " " << model << endl;
    }

    // Method (member function) — an action the object can perform
    void displayInfo() {
        cout << year << " " << brand << " " << model << endl;
    }

    void startEngine() {
        cout << brand << " engine started: Vroom!" << endl;
    }
};

int main() {
    cout << "--- Creating objects ---" << endl;
    Car defaultCar;                         // calls default constructor
    Car myCar("Toyota", "Corolla", 2022);   // calls parameterized constructor
    Car copiedCar = myCar;                  // calls copy constructor

    cout << "\n--- Calling methods ---" << endl;
    myCar.displayInfo();    // access method with dot operator
    myCar.startEngine();

    cout << "\n--- Copied car ---" << endl;
    copiedCar.displayInfo();

    cout << "\n--- End of main (destructors run) ---" << endl;
    // Destructors are called automatically here in reverse order
    return 0;
}
