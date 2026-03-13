# Function & Class Concepts in C++

A beginner-friendly collection covering all the essential function and class concepts in C++ programming.
Each file is self-contained with line-by-line comments.

---

## Files Overview

| # | File | Concept |
|---|------|---------|
| 01 | `01_basic_functions.cpp` | Function declaration, definition, return types |
| 02 | `02_pass_by_value_ref_ptr.cpp` | Pass by value, reference, and pointer |
| 03 | `03_default_and_overload.cpp` | Default parameters & function overloading |
| 04 | `04_inline_and_lambda.cpp` | Inline functions & lambda functions |
| 05 | `05_recursion.cpp` | Recursive functions |
| 06 | `06_templates.cpp` | Function templates |
| 07 | `07_basic_class.cpp` | Class, constructors, destructor |
| 08 | `08_encapsulation.cpp` | Encapsulation, access specifiers, getters/setters |
| 09 | `09_inheritance.cpp` | Inheritance, method overriding |
| 10 | `10_polymorphism.cpp` | Polymorphism, virtual functions, abstract class |
| 11 | `11_operator_overload.cpp` | Operator overloading |
| 12 | `12_static_members.cpp` | Static variables and static methods |

---

## Concepts Explained

### 01 — Basic Functions
The building block of all programs. A function has a name, optional parameters, and a return type.
- `void` — returns nothing
- `int`, `double`, `string`, etc. — returns a value
- **Declaration (prototype)** — tells the compiler a function exists before its definition

### 02 — Pass by Value, Reference, Pointer
Controls whether a function works on a copy or the original variable.

| Method | Syntax | Modifies original? | Use when |
|--------|--------|-------------------|----------|
| By Value | `void f(int x)` | No | you don't want changes to affect the caller |
| By Reference | `void f(int& x)` | Yes | you want to modify the original |
| By Pointer | `void f(int* x)` | Yes | working with raw memory or optional values |

### 03 — Default Parameters & Overloading
- **Default parameters** — provide a fallback value if the caller skips an argument
- **Overloading** — same function name, different parameter types/count; the compiler picks the right one

### 04 — Inline & Lambda Functions
- **Inline** — hints to the compiler to expand the function body at the call site (good for tiny functions)
- **Lambda** — anonymous function defined inline: `[capture](params) { body }`
  - `[=]` captures variables by value
  - `[&]` captures variables by reference

### 05 — Recursion
A function that calls itself. Requires:
1. **Base case** — when to stop
2. **Recursive case** — how to reduce the problem each step

### 06 — Function Templates
Write one function that works for any data type.
```cpp
template <typename T>
T getMax(T a, T b) { return (a > b) ? a : b; }
```
The compiler generates the correct version based on the arguments passed.

### 07 — Basic Class
A class groups data (attributes) and behaviour (methods) together.
- **Default constructor** — called when no arguments are given
- **Parameterized constructor** — called with arguments to set initial values
- **Copy constructor** — called when creating a new object from an existing one
- **Destructor** — called automatically when an object is destroyed

### 08 — Encapsulation
Hide internal data and expose only what is needed.
- `private` — accessible only inside the class
- `public` — accessible from anywhere
- `protected` — accessible inside the class and its subclasses
- **Getters** — read private data safely
- **Setters** — write private data with validation

### 09 — Inheritance
A child class reuses and extends a parent class.
```cpp
class Dog : public Animal { ... };
```
- Child inherits all `public` and `protected` members
- Child can **override** parent methods for its own behaviour
- Call parent method explicitly with `Parent::method()`

### 10 — Polymorphism
One base-class pointer, many possible types at runtime.
- `virtual` — marks a method as overridable
- `override` — confirms the method overrides a virtual one
- **Pure virtual** (`= 0`) — forces every child class to implement the method (abstract class)

### 11 — Operator Overloading
Define custom behaviour for operators (`+`, `-`, `*`, `==`, `<<`, etc.) on your own class.
```cpp
Vector2D operator+(const Vector2D& other) const { ... }
```

### 12 — Static Members
Belong to the **class**, not any single object. Shared across all instances.
- `static int count` — one variable for all objects
- `static void method()` — callable without creating an object: `Class::method()`
- Static local variable inside a function — retains its value between calls

---

## How to Compile & Run

```bash
g++ -std=c++14 01_basic_functions.cpp -o out && ./out
```

Replace the filename to run any example.
