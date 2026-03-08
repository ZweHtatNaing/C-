// 06_pointers_and_strings.cpp
// Topic: Pointers and C-style Strings (char arrays and char pointers)

#include <iostream>
#include <cstring>   // for strlen, strcpy, strcmp
using namespace std;

// --- Function: count characters manually using a char pointer ---
int myStrLen(const char* s) {
    const char* p = s;    // p starts at the first character
    while (*p != '\0') {  // '\0' is the null terminator that ends a C-string
        p++;              // advance pointer to the next character
    }
    return p - s;         // pointer difference = number of characters
}

// --- Function: print a string in reverse using pointer arithmetic ---
void printReverse(const char* s) {
    int len = myStrLen(s);
    const char* end = s + len - 1;  // point to the last real character (before '\0')
    while (end >= s) {
        cout << *end;  // print character at current position
        end--;         // move backward
    }
    cout << endl;
}

int main() {
    // --- 1. C-style string as a char array ---
    // The compiler automatically appends '\0' at the end.
    char name[] = "Hello";
    cout << "char array: " << name << endl;  // prints: Hello

    // --- 2. C-style string via char pointer (string literal) ---
    // Literals are stored in read-only memory; you CANNOT modify them.
    const char* greeting = "World";
    cout << "char* literal : " << greeting << endl;

    // --- 3. Traverse a string character by character with a pointer ---
    cout << "Characters: ";
    for (const char* p = name; *p != '\0'; p++) {
        // *p != '\0' is the loop condition; '\0' marks the end of the string
        cout << *p << " ";
    }
    cout << endl;

    // --- 4. Use our custom strlen ---
    cout << "Length of name    : " << myStrLen(name) << endl;  // 5
    cout << "strlen confirms   : " << strlen(name)   << endl;  // 5

    // --- 5. Modify characters through the char array pointer ---
    // 'name' is a char array, so individual characters are writable.
    name[0] = 'h';       // subscript notation
    *(name + 1) = 'E';   // pointer notation (equivalent)
    cout << "Modified name     : " << name << endl;  // hEllo

    // --- 6. Copy one string to another with strcpy ---
    char dest[20];              // destination buffer (large enough)
    strcpy(dest, "CopyMe");     // copies "CopyMe\0" into dest
    cout << "dest after strcpy : " << dest << endl;

    // --- 7. Compare two strings with strcmp ---
    // strcmp returns 0 if equal, negative if s1<s2, positive if s1>s2.
    int cmp = strcmp("apple", "banana");
    cout << "strcmp apple/banana: " << cmp << " (negative means apple < banana)" << endl;

    // --- 8. Pointer to the middle of a string ---
    const char* mid = greeting + 2;  // skip 'W' and 'o', point at 'r'
    cout << "From middle       : " << mid << endl;  // rld

    // --- 9. Print reverse of "Hello" ---
    cout << "Reverse of Hello  : ";
    printReverse("Hello");

    // --- 10. Array of char pointers (array of strings) ---
    const char* fruits[] = {"Apple", "Banana", "Cherry"};
    cout << "\nFruits:\n";
    for (int i = 0; i < 3; i++) {
        // fruits[i] is a char* pointing to each string literal
        cout << "  fruits[" << i << "] = " << fruits[i] << endl;
    }

    return 0;
}
