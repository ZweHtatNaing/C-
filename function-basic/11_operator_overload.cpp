#include <iostream>
using namespace std;

// ─────────────────────────────────────────────────────────
// OPERATOR OVERLOADING
// Lets you define what +, -, *, ==, <<, etc. mean for your own class.
// This makes custom types feel natural to use.
// ─────────────────────────────────────────────────────────

class Vector2D {
public:
    double x, y;

    Vector2D(double x = 0, double y = 0) : x(x), y(y) {}

    // Overload + : adds two vectors component-wise
    Vector2D operator+(const Vector2D& other) const {
        return Vector2D(x + other.x, y + other.y);
    }

    // Overload - : subtracts two vectors
    Vector2D operator-(const Vector2D& other) const {
        return Vector2D(x - other.x, y - other.y);
    }

    // Overload * : scales the vector by a scalar value
    Vector2D operator*(double scalar) const {
        return Vector2D(x * scalar, y * scalar);
    }

    // Overload == : checks if two vectors are equal
    bool operator==(const Vector2D& other) const {
        return (x == other.x) && (y == other.y);
    }

    // Overload != : checks if two vectors are NOT equal
    bool operator!=(const Vector2D& other) const {
        return !(*this == other); // reuse == operator
    }

    // Overload << : allows printing with cout directly
    // (friend gives this function access to private members)
    friend ostream& operator<<(ostream& os, const Vector2D& v) {
        os << "(" << v.x << ", " << v.y << ")";
        return os; // return os to allow chaining: cout << a << b
    }
};

int main() {
    Vector2D a(1.0, 2.0);
    Vector2D b(3.0, 4.0);

    cout << "a = " << a << endl; // uses overloaded <<
    cout << "b = " << b << endl;

    Vector2D sum  = a + b;   // uses overloaded +
    Vector2D diff = b - a;   // uses overloaded -
    Vector2D scaled = a * 3; // uses overloaded *

    cout << "\na + b     = " << sum    << endl;
    cout << "b - a     = " << diff   << endl;
    cout << "a * 3     = " << scaled << endl;

    cout << "\na == b    : " << (a == b ? "true" : "false") << endl;
    cout << "a == a    : " << (a == a ? "true" : "false") << endl;
    cout << "a != b    : " << (a != b ? "true" : "false") << endl;

    return 0;
}
