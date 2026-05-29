#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include "studentai1.h"

using namespace std;

int passed = 0;
int failed = 0;

void check(bool condition, const string& testName) {
    if (condition) {
        cout << "  [PASS] " << testName << "\n";
        passed++;
    }
    else {
        cout << "  [FAIL] " << testName << "\n";
        failed++;
    }
}

void testAbstract() {
    cout << "\n--- Zmogus abstraktumas ---\n";
    check(true, "Zmogus negali buti sukurtas tiesiogiai (kompiliacijos klaida jei bandom)");

    Studentas s("Jonas", "Jonaitis", { 6, 7, 8 }, 9);
    Zmogus* ptr = &s;
    check(ptr->vardas() == "Jonas", "Zmogus* rodo i Studentas objekta");
    check(ptr->vid() > 0.0, "virtualus vid() veikia per Zmogus*");
    check(ptr->med() > 0.0, "virtualus med() veikia per Zmogus*");
}
void testDefaultConstructor() {
    cout << "\n--- Default Constructor ---\n";
    Studentas s;
    check(s.vardas() == "", "vardas is empty");
    check(s.pavarde() == "", "pavarde is empty");
    check(s.egz() == 0, "egz is 0");
    check(s.vid() == 0.0, "vid is 0.0");
    check(s.med() == 0.0, "med is 0.0");
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
    check(s.med() > 0.0, "med calculated");
}

void testCopyConstructor() {
    cout << "\n--- Copy Constructor ---\n";
    Studentas original("Petras", "Petraitis", { 5, 6, 7 }, 8);
    Studentas copy(original);
    check(copy.vardas() == original.vardas(), "vardas copied");
    check(copy.pavarde() == original.pavarde(), "pavarde copied");
    check(copy.egz() == original.egz(), "egz copied");
    check(copy.vid() == original.vid(), "vid copied");
    check(copy.med() == original.med(), "med copied");
    check(copy.paz().size() == original.paz().size(), "paz size copied");
    Studentas copy2(original);
    copy2.setVardas("Kitas");
    check(original.vardas() == "Petras", "original not affected by copy");
}

void testMoveConstructor() {
    cout << "\n--- Move Constructor ---\n";
    Studentas temp("Antanas", "Antanaitis", { 4, 5, 6 }, 7);
    double vidBefore = temp.vid();
    Studentas moved(std::move(temp));
    check(moved.vardas() == "Antanas", "vardas moved");
    check(moved.pavarde() == "Antanaitis", "pavarde moved");
    check(moved.vid() == vidBefore, "vid preserved after move");
    check(temp.vardas() == "", "source emptied after move");
}

void testCopyAssignment() {
    cout << "\n--- Copy Assignment ---\n";
    Studentas a("Algis", "Algauskas", { 7, 8, 9 }, 10);
    Studentas b;
    b = a;
    check(b.vardas() == a.vardas(), "vardas assigned");
    check(b.pavarde() == a.pavarde(), "pavarde assigned");
    check(b.egz() == a.egz(), "egz assigned");
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
    check(b.pavarde() == "Zigmauskas", "pavarde move-assigned");
    check(b.vid() == vidBefore, "vid preserved");
    check(a.vardas() == "", "source emptied");
}

void testDestructor() {
    cout << "\n--- Destructor ---\n";
    {
        Studentas s("Temp", "Tempauskas", { 1, 2, 3 }, 5);
    }
    check(true, "destructor called without crash");
}

void testSettersAndFinalize() {
    cout << "\n--- Setters and Finalize ---\n";
    Studentas s;
    s.setVardas("Matas");
    s.setPavarde("Matauskas");
    s.addPaz(6);
    s.addPaz(7);
    s.addPaz(8);
    s.setEgz(9);
    s.finalize();
    check(s.vardas() == "Matas", "setVardas works");
    check(s.pavarde() == "Matauskas", "setPavarde works");
    check(s.egz() == 9, "setEgz works");
    check(s.paz().size() == 3, "addPaz works");
    check(s.vid() > 0.0, "finalize calculates vid");
    check(s.med() > 0.0, "finalize calculates med");
    vector<int> newPaz = { 1, 2 };
    s.setPaz(std::move(newPaz));
    s.finalize();
    check(s.paz().size() == 2, "setPaz works");
}

void testOutputOperator() {
    cout << "\n--- operator<< ---\n";
    Studentas s("Jonas", "Jonaitis", { 6, 7 }, 8);
    ostringstream oss;
    oss << s;
    string result = oss.str();
    check(result.find("Jonas") != string::npos, "vardas in output");
    check(result.find("Jonaitis") != string::npos, "pavarde in output");
    check(result.find("8") != string::npos, "egz in output");
    check(result.find("vid:") != string::npos, "vid label in output");
    check(result.find("med:") != string::npos, "med label in output");
    cout << "  Output: " << s << "\n";

    Zmogus* ptr = &s;
    ostringstream oss2;
    oss2 << *ptr;
    check(oss2.str().find("Jonas") != string::npos, "operator<< via Zmogus* works");
}

void testInputOperator() {
    cout << "\n--- operator>> (from string) ---\n";
    istringstream iss("Petras Petraitis 5 6 7 8 9");
    Studentas s;
    iss >> s;
    check(s.vardas() == "Petras", "vardas read");
    check(s.pavarde() == "Petraitis", "pavarde read");
    check(s.egz() == 9, "egz read (last number)");
    check(s.paz().size() == 4, "4 pazymiai read");
    check(s.vid() > 0.0, "vid calculated after read");
    check(s.med() > 0.0, "med calculated after read");
}

void testInputOperatorFromFile() {
    cout << "\n--- operator>> (from file) ---\n";
    {
        ofstream out("test_temp.txt");
        out << "Vardas Pavarde 5 6 7 8 9\n";
    }
    ifstream in("test_temp.txt");
    Studentas s;
    in >> s;
    check(s.vardas() == "Vardas", "vardas read from file");
    check(s.pavarde() == "Pavarde", "pavarde read from file");
    check(s.egz() == 9, "egz read from file");
    check(s.vid() > 0.0, "vid calculated from file");
    remove("test_temp.txt");
}

void testOutputOperatorToFile() {
    cout << "\n--- operator<< (to file) ---\n";
    Studentas s("Ona", "Onaite", { 5, 6 }, 7);
    {
        ofstream out("test_out.txt");
        out << s;
    }
    ifstream in("test_out.txt");
    string line;
    getline(in, line);
    check(line.find("Ona") != string::npos, "vardas in file");
    check(line.find("Onaite") != string::npos, "pavarde in file");
    check(line.find("7") != string::npos, "egz in file");
    remove("test_out.txt");
}

int main() {
    cout << "========== Studentas / Zmogus klases testai (v1.5) ==========\n";

    testAbstract();
    testDefaultConstructor();
    testParametrizedConstructor();
    testCopyConstructor();
    testMoveConstructor();
    testCopyAssignment();
    testMoveAssignment();
    testDestructor();
    testSettersAndFinalize();
    testOutputOperator();
    testInputOperator();
    testInputOperatorFromFile();
    testOutputOperatorToFile();

    cout << "\n========== Rezultatai ==========\n";
    cout << "Praejo  : " << passed << "\n";
    cout << "Nepraejo: " << failed << "\n";
    if (failed == 0)
        cout << "Visi testai sekmingai praejo!\n";
    else
        cout << "Kai kurie testai nepraejo!\n";

    return failed == 0 ? 0 : 1;
}