#include <gtest/gtest.h>
#include <sstream>
#include <fstream>
#include <vector>
#include "studentai1.h"

using namespace std;


TEST(ZmogusTest, CannotInstantiateDirectly) {

    EXPECT_TRUE(std::is_abstract<Zmogus>::value);
}

TEST(ZmogusTest, PointerToStudentas) {
    Studentas s("Jonas", "Jonaitis", {6, 7, 8}, 9);
    Zmogus* ptr = &s;
    EXPECT_EQ(ptr->vardas(), "Jonas");
    EXPECT_EQ(ptr->pavarde(), "Jonaitis");
    EXPECT_GT(ptr->vid(), 0.0);
    EXPECT_GT(ptr->med(), 0.0);
}

TEST(StudentasTest, DefaultConstructor) {
    Studentas s;
    EXPECT_EQ(s.vardas(),  "");
    EXPECT_EQ(s.pavarde(), "");
    EXPECT_EQ(s.egz(),     0);
    EXPECT_DOUBLE_EQ(s.vid(), 0.0);
    EXPECT_DOUBLE_EQ(s.med(), 0.0);
    EXPECT_TRUE(s.paz().empty());
}

TEST(StudentasTest, ParametrizedConstructor) {
    Studentas s("Jonas", "Jonaitis", {6, 7, 8}, 9);
    EXPECT_EQ(s.vardas(),     "Jonas");
    EXPECT_EQ(s.pavarde(),    "Jonaitis");
    EXPECT_EQ(s.egz(),        9);
    EXPECT_EQ(s.paz().size(), 3u);
    EXPECT_GT(s.vid(), 0.0);
    EXPECT_GT(s.med(), 0.0);
}

TEST(StudentasTest, CopyConstructor) {
    Studentas original("Petras", "Petraitis", {5, 6, 7}, 8);
    Studentas copy(original);
    EXPECT_EQ(copy.vardas(),     original.vardas());
    EXPECT_EQ(copy.pavarde(),    original.pavarde());
    EXPECT_EQ(copy.egz(),        original.egz());
    EXPECT_DOUBLE_EQ(copy.vid(), original.vid());
    EXPECT_DOUBLE_EQ(copy.med(), original.med());
    EXPECT_EQ(copy.paz().size(), original.paz().size());
}

TEST(StudentasTest, CopyConstructorDeep) {
    Studentas original("Petras", "Petraitis", {5, 6, 7}, 8);
    Studentas copy(original);
    copy.setVardas("Kitas");
    EXPECT_EQ(original.vardas(), "Petras");
}

TEST(StudentasTest, MoveConstructor) {
    Studentas temp("Antanas", "Antanaitis", {4, 5, 6}, 7);
    double vidBefore = temp.vid();
    Studentas moved(std::move(temp));
    EXPECT_EQ(moved.vardas(),        "Antanas");
    EXPECT_EQ(moved.pavarde(),       "Antanaitis");
    EXPECT_DOUBLE_EQ(moved.vid(),    vidBefore);
    EXPECT_EQ(temp.vardas(),         "");
}

TEST(StudentasTest, CopyAssignment) {
    Studentas a("Algis", "Algauskas", {7, 8, 9}, 10);
    Studentas b;
    b = a;
    EXPECT_EQ(b.vardas(),        a.vardas());
    EXPECT_EQ(b.pavarde(),       a.pavarde());
    EXPECT_EQ(b.egz(),           a.egz());
    EXPECT_DOUBLE_EQ(b.vid(),    a.vid());
}

TEST(StudentasTest, CopyAssignmentSelf) {
    Studentas a("Algis", "Algauskas", {7, 8, 9}, 10);
    a = a;
    EXPECT_EQ(a.vardas(), "Algis");
}

TEST(StudentasTest, MoveAssignment) {
    Studentas a("Zigmas", "Zigmauskas", {3, 4, 5}, 6);
    double vidBefore = a.vid();
    Studentas b;
    b = std::move(a);
    EXPECT_EQ(b.vardas(),        "Zigmas");
    EXPECT_EQ(b.pavarde(),       "Zigmauskas");
    EXPECT_DOUBLE_EQ(b.vid(),    vidBefore);
    EXPECT_EQ(a.vardas(),        "");
}

TEST(StudentasTest, Destructor) {
    EXPECT_NO_THROW({
        Studentas s("Temp", "Tempauskas", {1, 2, 3}, 5);
    });
}

TEST(StudentasTest, Setters) {
    Studentas s;
    s.setVardas("Matas");
    s.setPavarde("Matauskas");
    s.addPaz(6);
    s.addPaz(7);
    s.addPaz(8);
    s.setEgz(9);
    s.finalize();
    EXPECT_EQ(s.vardas(),     "Matas");
    EXPECT_EQ(s.pavarde(),    "Matauskas");
    EXPECT_EQ(s.egz(),        9);
    EXPECT_EQ(s.paz().size(), 3u);
    EXPECT_GT(s.vid(),        0.0);
    EXPECT_GT(s.med(),        0.0);
}

TEST(StudentasTest, SetPaz) {
    Studentas s;
    vector<int> p = {1, 2};
    s.setPaz(std::move(p));
    s.setEgz(5);
    s.finalize();
    EXPECT_EQ(s.paz().size(), 2u);
}

TEST(StudentasTest, OutputOperator) {
    Studentas s("Jonas", "Jonaitis", {6, 7}, 8);
    ostringstream oss;
    oss << s;
    string result = oss.str();
    EXPECT_NE(result.find("Jonas"),    string::npos);
    EXPECT_NE(result.find("Jonaitis"), string::npos);
    EXPECT_NE(result.find("vid:"),     string::npos);
    EXPECT_NE(result.find("med:"),     string::npos);
}

TEST(StudentasTest, OutputOperatorViaBasePointer) {
    Studentas s("Jonas", "Jonaitis", {6, 7}, 8);
    Zmogus* ptr = &s;
    ostringstream oss;
    oss << *ptr;
    EXPECT_NE(oss.str().find("Jonas"), string::npos);
}
TEST(StudentasTest, InputOperatorFromString) {
    istringstream iss("Petras Petraitis 5 6 7 8 9");
    Studentas s;
    iss >> s;
    EXPECT_EQ(s.vardas(),     "Petras");
    EXPECT_EQ(s.pavarde(),    "Petraitis");
    EXPECT_EQ(s.egz(),        9);
    EXPECT_EQ(s.paz().size(), 4u);
    EXPECT_GT(s.vid(),        0.0);
    EXPECT_GT(s.med(),        0.0);
}

TEST(StudentasTest, InputOperatorFromFile) {
    {
        ofstream out("test_temp.txt");
        out << "Vardas Pavarde 5 6 7 8 9\n";
    }
    ifstream in("test_temp.txt");
    Studentas s;
    in >> s;
    EXPECT_EQ(s.vardas(),  "Vardas");
    EXPECT_EQ(s.pavarde(), "Pavarde");
    EXPECT_EQ(s.egz(),     9);
    EXPECT_GT(s.vid(),     0.0);
    remove("test_temp.txt");
}

TEST(StudentasTest, OutputOperatorToFile) {
    Studentas s("Ona", "Onaite", {5, 6}, 7);
    {
        ofstream out("test_out.txt");
        out << s;
    }
    ifstream in("test_out.txt");
    string line;
    getline(in, line);
    EXPECT_NE(line.find("Ona"),    string::npos);
    EXPECT_NE(line.find("Onaite"), string::npos);
    remove("test_out.txt");
}
