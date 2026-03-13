#include <iostream>
using namespace std;

// ─────────────────────────────────────────────────────────
// INHERITANCE
// A child class inherits attributes and methods from a parent class.
// Promotes code reuse — no need to rewrite shared behaviour.
//
// Syntax: class Child : public Parent { ... };
// ─────────────────────────────────────────────────────────

// BASE (PARENT) class
class Animal {
protected:
    // protected — accessible in this class AND in child classes
    string name;
    int    age;

public:
    Animal(string n, int a) : name(n), age(a) { // initialiser list syntax
        cout << "Animal created: " << name << endl;
    }

    // A method available to all animals
    void breathe() {
        cout << name << " is breathing." << endl;
    }

    void displayInfo() {
        cout << "Name: " << name << " | Age: " << age << endl;
    }
};

// DERIVED (CHILD) class — inherits everything from Animal
class Dog : public Animal {
private:
    string breed; // Dog has its own extra attribute

public:
    // Child constructor calls the parent constructor using : Animal(n, a)
    Dog(string n, int a, string b) : Animal(n, a), breed(b) {
        cout << "Dog created: " << name << " (" << breed << ")" << endl;
    }

    // Dog's own method — not in Animal
    void bark() {
        cout << name << " says: Woof!" << endl;
    }

    void displayInfo() { // overrides the parent's displayInfo
        Animal::displayInfo();                      // call parent version first
        cout << "Breed: " << breed << endl;         // then add extra info
    }
};

// Another child class inheriting from Animal
class Bird : public Animal {
private:
    bool canFly;

public:
    Bird(string n, int a, bool fly) : Animal(n, a), canFly(fly) {
        cout << "Bird created: " << name << endl;
    }

    void displayInfo() {
        Animal::displayInfo();
        cout << "Can fly: " << (canFly ? "Yes" : "No") << endl;
    }

    void chirp() {
        cout << name << " says: Tweet!" << endl;
    }
};

int main() {
    cout << "--- Creating objects ---" << endl;
    Dog  dog("Buddy", 3, "Labrador");
    Bird bird("Tweety", 1, true);

    cout << "\n--- Dog ---" << endl;
    dog.displayInfo(); // calls Dog's overridden version
    dog.breathe();     // inherited from Animal
    dog.bark();        // Dog-specific method

    cout << "\n--- Bird ---" << endl;
    bird.displayInfo(); // calls Bird's overridden version
    bird.breathe();     // inherited from Animal
    bird.chirp();       // Bird-specific method

    return 0;
}
