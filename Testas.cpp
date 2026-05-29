#include <iostream>
#include <cassert>
#include <vector>
#include "studentai1.h"
using namespace std;

int passed = 0, failed = 0;

void check(bool condition, const string& name) {
    if (condition) { cout << "  [PASS] " << name << "\n"; passed++; }
    else { cout << "  [FAIL] " << name << "\n"; failed++; }
}

void testDefaultConstructor() {
    cout << "\n--- Default Constructor ---\n";
    Studentas s;
    check(s.vardas() == "", "vardas is empty");
    check(s.pavarde() == "", "pavarde is empty");
    check(s.egz() == 0, "egz is 0");
    check(s.vid() == 0.0, "vid is 0.0");
    check(s.paz().empty(), "paz is empty");
}

void testParametrizedConstructor() {
    cout << "\n--- Parametrized Constructor ---\n";
    Studentas s("Jonas", "Jonaitis", { 6, 7, 8 }, 9);
    check(s.vardas() == "Jonas", "vardas correct");
    check(s.pavarde() == "Jonaitis", "pavarde correct");
    check(s.egz() == 9, "egz correct");
    check(s.paz().size() == 3, "paz size correct");
    check(s.vid() > 0.0, "vid calculated");
}

void testCopyConstructor() {
    cout << "\n--- Copy Constructor ---\n";
    Studentas original("Petras", "Petraitis", { 5, 6, 7 }, 8);
    Studentas copy(original);
    check(copy.vardas() == original.vardas(), "vardas copied");
    check(copy.pavarde() == original.pavarde(), "pavarde copied");
    check(copy.vid() == original.vid(), "vid copied");
    Studentas copy2(original);
    copy2.setVardas("Kitas");
    check(original.vardas() == "Petras", "original not affected");
}

void testMoveConstructor() {
    cout << "\n--- Move Constructor ---\n";
    Studentas temp("Antanas", "Antanaitis", { 4, 5, 6 }, 7);
    double vidBefore = temp.vid();
    Studentas moved(std::move(temp));
    check(moved.vardas() == "Antanas", "vardas moved");
    check(moved.vid() == vidBefore, "vid preserved");
    check(temp.vardas() == "", "source emptied");
}

void testCopyAssignment() {
    cout << "\n--- Copy Assignment ---\n";
    Studentas a("Algis", "Algauskas", { 7, 8, 9 }, 10);
    Studentas b;
    b = a;
    check(b.vardas() == a.vardas(), "vardas assigned");
    check(b.vid() == a.vid(), "vid assigned");
    b = b;
    check(b.vardas() == "Algis", "self-assignment safe");
}

void testMoveAssignment() {
    cout << "\n--- Move Assignment ---\n";
    Studentas a("Zigmas", "Zigmauskas", { 3, 4, 5 }, 6);
    double vidBefore = a.vid();
    Studentas b;
    b = std::move(a);
    check(b.vardas() == "Zigmas", "vardas move-assigned");
    check(b.vid() == vidBefore, "vid preserved");
    check(a.vardas() == "", "source emptied");
}

int main() {
    testDefaultConstructor();
    testParametrizedConstructor();
    testCopyAssignment();
    testCopyConstructor();
    testMoveAssignment();
    testMoveAssignment();
    cout << "\nPraejo: " << passed << " | Nepraejo: " << failed << "\n";
    return failed == 0 ? 0 : 1;
}
