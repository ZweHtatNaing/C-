# C++ Pointers

A pointer is a variable that stores the **memory address** of another variable. Pointers are one of the most powerful features of C++ — they enable direct memory access, dynamic allocation, and efficient data manipulation.

---

## Table of Contents

1. [Basic Concepts](#1-basic-concepts)
2. [Pointer Arithmetic](#2-pointer-arithmetic)
3. [Pointers and Arrays](#3-pointers-and-arrays)
4. [Double Pointers](#4-double-pointers)
5. [Pointers and Functions](#5-pointers-and-functions)
6. [Pointers and Strings](#6-pointers-and-strings)
7. [Dynamic Memory](#7-dynamic-memory)
8. [Function Pointers](#8-function-pointers)
9. [Common Pitfalls](#common-pitfalls)

---

## 1. Basic Concepts

**File:** `01_basic_pointers.cpp`

| Operator | Meaning |
|----------|---------|
| `&var`   | Address-of — gives the memory address of `var` |
| `*ptr`   | Dereference — reads/writes the value at the address stored in `ptr` |

```cpp
int age = 25;
int* ptr = &age;   // ptr holds the address of age

cout << ptr;    // prints the address (e.g. 0x7fff...)
cout << *ptr;   // prints 25  (dereference)

*ptr = 30;      // modifies age through the pointer
cout << age;    // 30
```

**Key facts:**
- A pointer's type must match the variable it points to (`int*` for `int`, `double*` for `double`, etc.).
- On a 64-bit system, every pointer is **8 bytes** regardless of what type it points to.

---

## 2. Pointer Arithmetic

**File:** `02_pointer_arithmetic.cpp`

When you add or subtract an integer from a pointer, it moves by **that many elements** (not bytes).

```cpp
int nums[] = {10, 20, 30, 40, 50};
int* ptr = nums;   // points to nums[0]

ptr++;             // now points to nums[1] (advances 4 bytes for int)
ptr = ptr + 2;     // now points to nums[3]
ptr--;             // now points to nums[2]
```

| Operation | Effect |
|-----------|--------|
| `ptr++`   | Move to next element |
| `ptr--`   | Move to previous element |
| `ptr + n` | Move forward n elements |
| `ptr - n` | Move backward n elements |
| `p2 - p1` | Number of elements between two pointers (`ptrdiff_t`) |
| `p1 < p2` | Compare positions in memory |

**Traversing an array with a pointer:**
```cpp
for (int* p = nums; p < nums + 5; p++) {
    cout << *p << " ";   // 10 20 30 40 50
}
```

---

## 3. Pointers and Arrays

**File:** `03_pointers_and_arrays.cpp`

An array name **decays** to a pointer to its first element. These expressions are equivalent:

```cpp
int arr[] = {5, 10, 15, 20, 25};

arr[2]       // subscript notation
*(arr + 2)   // pointer notation — identical result: 15
```

**Array name vs pointer variable:**

| | Array name (`arr`) | Pointer variable (`ptr`) |
|---|---|---|
| Holds address of first element | Yes | Yes |
| Can be incremented (`++`) | No (compile error) | Yes |
| `sizeof` returns | Full array size | Size of one pointer (8 bytes) |

**2D arrays** use double indirection:
```cpp
int matrix[3][3] = {{1,2,3},{4,5,6},{7,8,9}};
// matrix[i][j]  ==  *(*(matrix + i) + j)
```

---

## 4. Double Pointers

**File:** `04_double_pointers.cpp`

A **double pointer** (`**ptr`) stores the address of another pointer. The chain looks like:

```
value  <──  ptr1  <──  ptr2
  42       &value      &ptr1
```

```cpp
int value = 42;
int*  ptr1 = &value;
int** ptr2 = &ptr1;

cout << **ptr2;    // 42  (dereference twice)
**ptr2 = 100;      // modifies value through two levels of indirection
```

**Primary use case — dynamic 2D arrays:**
```cpp
int** grid = new int*[rows];
for (int i = 0; i < rows; i++)
    grid[i] = new int[cols];

// ... use grid[i][j] ...

for (int i = 0; i < rows; i++) delete[] grid[i];
delete[] grid;
```

---

## 5. Pointers and Functions

**File:** `05_pointers_and_functions.cpp`

### Pass-by-Pointer vs Pass-by-Value

```cpp
void passByValue(int x)   { x = 999; }      // copy — original unchanged
void passByPointer(int* p){ *p = 999; }     // modifies the original

int n = 10;
passByValue(n);         // n is still 10
passByPointer(&n);      // n is now 999
```

### Classic Swap

```cpp
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}
swap(&x, &y);   // pass addresses
```

### Returning Pointers

```cpp
// Safe: return pointer to static or heap-allocated variable
int* getStaticValue() {
    static int result = 77;
    return &result;          // static persists after the function returns
}

// UNSAFE: never return a pointer to a local variable
// int* bad() { int x = 5; return &x; }  // dangling pointer!
```

### Double Pointer to Modify a Pointer

```cpp
void allocate(int** pp, int val) {
    *pp = new int(val);   // makes the caller's pointer point to new heap memory
}

int* p = nullptr;
allocate(&p, 42);         // p now points to heap int with value 42
delete p;
```

---

## 6. Pointers and Strings

**File:** `06_pointers_and_strings.cpp`

A C-style string is a `char` array terminated by `'\0'`. A `char*` points to its first character.

```cpp
char name[] = "Hello";          // mutable char array
const char* greeting = "World"; // pointer to string literal (read-only)
```

**Traversal:**
```cpp
for (const char* p = name; *p != '\0'; p++) {
    cout << *p;   // prints each character
}
```

**Common `<cstring>` functions:**

| Function | Description |
|----------|-------------|
| `strlen(s)` | Length of string (excludes `'\0'`) |
| `strcpy(dst, src)` | Copy `src` into `dst` |
| `strcmp(s1, s2)` | Compare; returns 0 if equal |

**Array of strings:**
```cpp
const char* fruits[] = {"Apple", "Banana", "Cherry"};
// fruits[i] is a char* pointing to each string literal
```

---

## 7. Dynamic Memory

**File:** `07_dynamic_memory.cpp`

Use `new` / `delete` to allocate memory on the **heap** at runtime.

### Single Variable

```cpp
int* p = new int(99);   // allocate and initialise
cout << *p;             // 99
delete p;               // free
p = nullptr;            // avoid dangling pointer
```

### Array

```cpp
int* arr = new int[5];  // allocate array
arr[0] = 10;            // use like a normal array
delete[] arr;           // MUST use delete[] for arrays
arr = nullptr;
```

### Struct / Object

```cpp
struct Point { int x, y; };
Point* pt = new Point;
pt->x = 3;   // '->' dereferences and accesses member
pt->y = 7;   // equivalent to (*pt).y = 7
delete pt;
```

### Rules

| Rule | Reason |
|------|--------|
| Every `new` must have a `delete` | Prevent memory leaks |
| Every `new[]` must have `delete[]` | Using plain `delete` on an array is undefined behaviour |
| Set pointer to `nullptr` after `delete` | Prevent dangling-pointer bugs |
| Never `delete` a stack variable | Only heap memory should be freed |

---

## 8. Function Pointers

**File:** `08_function_pointers.cpp`

A function pointer stores the address of a function so it can be called indirectly or passed as an argument.

**Declaration syntax:**
```cpp
int (*fp)(int, int) = &add;   // fp points to a function taking two ints, returning int
cout << fp(3, 4);              // 7  — call through the pointer
```

**As a callback parameter:**
```cpp
int applyOp(int x, int y, int (*op)(int, int)) {
    return op(x, y);   // call whichever function was passed
}

applyOp(5, 6, add);   // 11
applyOp(5, 6, mul);   // 30
```

**Array of function pointers (dispatch table):**
```cpp
int (*ops[3])(int, int) = {add, sub, mul};
ops[0](8, 2);   // 10
ops[1](8, 2);   // 6
ops[2](8, 2);   // 16
```

**Simplify with `typedef` or `using`:**
```cpp
typedef int (*BinaryOp)(int, int);   // C-style alias
using BinaryOp = int (*)(int, int);  // modern C++ alias

BinaryOp myOp = mul;
myOp(4, 5);   // 20
```

---

## Common Pitfalls

| Pitfall | Description | Fix |
|---------|-------------|-----|
| **Dangling pointer** | Pointer to memory that has been freed or gone out of scope | Set to `nullptr` after `delete`; never return pointers to locals |
| **Null pointer dereference** | Dereferencing a `nullptr` causes a crash | Always check `if (ptr != nullptr)` before dereferencing |
| **Memory leak** | `new` without a matching `delete` | Ensure every allocation has a corresponding deallocation |
| **Buffer overflow** | Writing past the end of an allocated block | Track sizes; prefer `std::vector` / `std::string` |
| **Modifying a string literal** | `const char*` literals are read-only | Use a `char[]` array if you need to modify the string |
| **Wrong delete** | Using `delete` instead of `delete[]` for arrays | Match `new[]` with `delete[]` |

---

## Quick Reference

```
Variable:   int x = 10;
Pointer:    int* p = &x;    // p holds address of x
Address:    &x              // memory address of x
Deref:      *p              // value at address p (= 10)
Modify:     *p = 20;        // x is now 20
Arrow:      pt->member      // (*pt).member for structs/classes
Double ptr: int** pp = &p;  // pointer to a pointer
```
