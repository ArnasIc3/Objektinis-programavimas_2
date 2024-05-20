#include "menu.h"
#include "student.h"

void testConstructors() {
    mVector<int> grades = {5, 6, 7, 8, 9};

    // parameterized constructor
    Studentas s1("John", "Doe", 8, grades);
    cout << s1.getVardas() << " " << s1.getPavarde() << endl; // Should print "John Doe"

    // copy constructor
    Studentas s2(s1);
    cout << s2.getVardas() << " " << s2.getPavarde() << endl; // Should print "John Doe"

    // move constructor
    Studentas s3(std::move(s2));
    cout << s3.getVardas() << " " << s3.getPavarde() << endl; // Should print "John Doe"

    // default constructor
    Studentas s4;
    cout << s4.getVardas() << " " << s4.getPavarde() << endl; // Should print " "
}

int main() {
    bool runTests = false;
    if (runTests) {
        testConstructors();
    }
    srand(time(nullptr));
    Menu_execute();
    return 0;
}