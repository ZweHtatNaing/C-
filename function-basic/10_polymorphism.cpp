#include <iostream>
using namespace std;

// ─────────────────────────────────────────────────────────
// POLYMORPHISM
// "One interface, many forms."
// A base class pointer can point to a derived class object
// and call the correct overridden method at runtime.
//
// virtual  — marks a method as overridable in child classes
// override — (optional) confirms we are overriding a virtual method
// Pure virtual (= 0) — forces child classes to implement the method
// ─────────────────────────────────────────────────────────

// Abstract base class — has at least one pure virtual method
class Shape {
public:
    string color;

    Shape(string c) : color(c) {}

    // Pure virtual — every Shape MUST implement this
    virtual double area() = 0;

    // Virtual method — can be overridden but has a default
    virtual void describe() {
        cout << "I am a " << color << " shape. Area = " << area() << endl;
    }

    virtual ~Shape() {} // virtual destructor — important for polymorphism
};

// Concrete class — implements area()
class Circle : public Shape {
private:
    double radius;

public:
    Circle(string c, double r) : Shape(c), radius(r) {}

    double area() override { // override keyword confirms this overrides Shape::area()
        return 3.14159 * radius * radius;
    }

    void describe() override {
        cout << "Circle  | color=" << color << " radius=" << radius
             << " area=" << area() << endl;
    }
};

class Rectangle : public Shape {
private:
    double width, height;

public:
    Rectangle(string c, double w, double h) : Shape(c), width(w), height(h) {}

    double area() override {
        return width * height;
    }

    void describe() override {
        cout << "Rect    | color=" << color << " " << width << "x" << height
             << " area=" << area() << endl;
    }
};

class Triangle : public Shape {
private:
    double base, height;

public:
    Triangle(string c, double b, double h) : Shape(c), base(b), height(h) {}

    double area() override {
        return 0.5 * base * height;
    }

    void describe() override {
        cout << "Triangle| color=" << color << " base=" << base
             << " height=" << height << " area=" << area() << endl;
    }
};

int main() {
    // Store different Shape types through a base-class POINTER
    // This is the essence of polymorphism
    Shape* shapes[] = {
        new Circle("red", 5.0),
        new Rectangle("blue", 4.0, 6.0),
        new Triangle("green", 3.0, 8.0)
    };

    cout << "--- Polymorphic describe() ---" << endl;
    for (Shape* s : shapes) {
        s->describe(); // calls the CORRECT version based on the actual type
    }

    cout << "\n--- Total area ---" << endl;
    double total = 0;
    for (Shape* s : shapes) {
        total += s->area(); // each shape calculates its own area
    }
    cout << "Total area = " << total << endl;

    // Clean up heap memory
    for (Shape* s : shapes) delete s;

    return 0;
}
