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

int main() {
    testDefaultConstructor();
    testParametrizedConstructor();
    cout << "\nPraejo: " << passed << " | Nepraejo: " << failed << "\n";
    return failed == 0 ? 0 : 1;
}
