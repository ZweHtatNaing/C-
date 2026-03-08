// 08_vector_of_objects.cpp
// Topic: Vectors of Structs and Objects
//        Storing, sorting, searching, and managing user-defined types

#include <iostream>
#include <vector>
#include <algorithm>   // sort, find_if, remove_if
#include <string>
using namespace std;

// =====================================================================
// SAMPLE STRUCT
// =====================================================================
struct Student {
    string name;
    int    age;
    double gpa;

    // Constructor for convenient creation
    Student(string n, int a, double g) : name(n), age(a), gpa(g) {}

    // Overload << for easy printing
    friend ostream& operator<<(ostream& os, const Student& s) {
        os << "[" << s.name << " | age=" << s.age << " | gpa=" << s.gpa << "]";
        return os;
    }
};

void printStudents(const string& label, const vector<Student>& v) {
    cout << label << ":\n";
    for (const auto& s : v) cout << "  " << s << "\n";
}

int main() {
    // =====================================================================
    // CREATING A VECTOR OF OBJECTS
    // =====================================================================

    // --- 1. push_back with constructor calls ---
    vector<Student> students;
    students.push_back(Student("Alice",  20, 3.9));
    students.push_back(Student("Bob",    22, 3.2));
    students.push_back(Student("Carol",  21, 3.7));
    students.push_back(Student("Dave",   20, 2.8));
    students.push_back(Student("Eve",    23, 3.5));
    printStudents("Initial list", students);

    // --- 2. emplace_back — construct in-place, no temporary object ---
    // Arguments are forwarded directly to the Student constructor.
    students.emplace_back("Frank", 19, 3.1);
    cout << "\nAfter emplace_back Frank:\n  " << students.back() << "\n";

    // --- 3. Initialiser list construction ---
    vector<Student> team = {
        {"Ana",  24, 3.8},
        {"Ben",  25, 3.6},
        {"Cara", 22, 3.3}
    };
    printStudents("\nTeam (brace-init)", team);

    // =====================================================================
    // ACCESSING AND MODIFYING
    // =====================================================================

    // --- 4. Access by index ---
    cout << "\nstudents[0] : " << students[0] << endl;
    cout << "students.at(2) : " << students.at(2) << endl;

    // --- 5. Modify a field through a reference ---
    students[1].gpa = 3.8;   // Bob gets a higher GPA
    cout << "Bob after update: " << students[1] << endl;

    // --- 6. Range-for with const ref (read-only, efficient) ---
    cout << "\nAll students (const ref):\n";
    for (const Student& s : students) {
        cout << "  " << s << "\n";
    }

    // =====================================================================
    // SORTING
    // =====================================================================

    // --- 7. Sort by GPA descending ---
    sort(students.begin(), students.end(), [](const Student& a, const Student& b){
        return a.gpa > b.gpa;   // descending
    });
    printStudents("\nSorted by GPA (desc)", students);

    // --- 8. Sort by name alphabetically ---
    sort(students.begin(), students.end(), [](const Student& a, const Student& b){
        return a.name < b.name;
    });
    printStudents("Sorted by name (asc)", students);

    // --- 9. Sort by age, then by name for ties ---
    sort(students.begin(), students.end(), [](const Student& a, const Student& b){
        if (a.age != b.age) return a.age < b.age;
        return a.name < b.name;
    });
    printStudents("Sorted by age then name", students);

    // =====================================================================
    // SEARCHING
    // =====================================================================

    // --- 10. find_if — find first match by predicate ---
    auto it = find_if(students.begin(), students.end(), [](const Student& s){
        return s.name == "Carol";
    });
    if (it != students.end())
        cout << "\nFound: " << *it << endl;
    else
        cout << "\nCarol not found." << endl;

    // --- 11. Find all students with GPA >= 3.5 ---
    cout << "\nHonour roll (GPA >= 3.5):\n";
    for (const Student& s : students) {
        if (s.gpa >= 3.5) cout << "  " << s << "\n";
    }

    // =====================================================================
    // REMOVING
    // =====================================================================

    // --- 12. Erase-remove idiom with a predicate ---
    // Remove all students younger than 21.
    students.erase(
        remove_if(students.begin(), students.end(), [](const Student& s){
            return s.age < 21;
        }),
        students.end()
    );
    printStudents("\nAfter removing age < 21", students);

    // =====================================================================
    // VECTORS OF POINTERS TO OBJECTS
    // =====================================================================

    // --- 13. Raw pointer vector (manual memory management) ---
    vector<Student*> ptrVec;
    ptrVec.push_back(new Student("X", 20, 3.0));
    ptrVec.push_back(new Student("Y", 21, 3.5));

    cout << "\nPointer vector:\n";
    for (Student* sp : ptrVec) cout << "  " << *sp << "\n";

    // MUST delete manually:
    for (Student* sp : ptrVec) delete sp;
    ptrVec.clear();

    // =====================================================================
    // COMMON UTILITY PATTERNS
    // =====================================================================

    // --- 14. Collect matching elements into a new vector ---
    vector<Student> roster = {
        {"Tom",  20, 3.9}, {"Sam", 22, 3.1}, {"Lily", 21, 3.6}, {"Max", 23, 2.9}
    };

    vector<Student> topStudents;
    for (const Student& s : roster) {
        if (s.gpa >= 3.5) topStudents.push_back(s);
    }
    printStudents("\nTop students (gpa >= 3.5)", topStudents);

    // --- 15. Transform: extract one field into a separate vector ---
    vector<string> names;
    for (const Student& s : roster) names.push_back(s.name);
    cout << "\nAll names: ";
    for (const string& n : names) cout << n << " ";
    cout << endl;

    // --- 16. Compute average GPA ---
    double total = 0.0;
    for (const Student& s : roster) total += s.gpa;
    cout << "Average GPA: " << total / roster.size() << endl;

    return 0;
}
