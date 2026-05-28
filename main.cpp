#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>

using std::string;
using std::cin;
using std::vector;
using std::cout;
using std::left;
using std::right;
using std::setw;
using std::endl;
using std::fixed;
using std::setprecision;
using std::sort;


struct Studentas {
    string vardas, pavarde;
    vector <int> paz;
    int egz;
    double vid;
    double med;
};
void inputas(vector <Studentas>& grupe, char& c);
void mediana(vector <Studentas>& grupe);
void outputas(const vector <Studentas>& grupe, char c);
int main() {
    vector<Studentas> grupe;
    char c;
    inputas(grupe, c);
    mediana(grupe);
    outputas(grupe, c);
}

void inputas(vector <Studentas>& grupe, char& c) {

    for (int ii = 0; ii < 2; ii++) {
        Studentas A;
        cout << "Iveskite studento vardo ir pavarde ";
        cin >> A.vardas >> A.pavarde;
        cout << "Iveskite semestro ivercius. Kiek ju bus? ";
        int n, sum = 0;
        while(true){
            if (cin >> n && n >= 0) {
                break;
            }
            else {
                cout << "Neteisingas ivedimas, iveskite teigiama skaiciu: ";
                cin.clear();
                cin.ignore(10000, '\n');
            }
        }
        for (int i = 0; i < n; i++) {
            int temp;
            cout << "Iveskite " << i + 1 << " pazymi is " << n << ": ";
            while (true) {
                if (cin >> temp && temp >= 1 && temp <= 10) {
                    break;
                }
                else {
                    cout << "Neteisingas ivedimas, iveskite skaiciu nuo 1 iki 10: ";
                    cin.clear();
                    cin.ignore(10000, '\n');
                }
            }
            A.paz.push_back(temp); sum += temp;
        }
        cout << "Iveskite egzamina: ";
        while (true) {
            if (cin >> A.egz && A.egz >= 1 && A.egz <= 10) {
                break;
            }
            else {
                cout << "Neteisingas ivedimas, iveskite skaiciu nuo 1 iki 10: ";
                cin.clear();
                cin.ignore(10000, '\n');
            }
        }
        A.vid = sum * 1.0 / (n * 1.0) * 0.4 + A.egz * 0.6;
        grupe.push_back(A);
        A.paz.clear();
    }
    cout << "Rezultata isvesti su mediana(irasyti M arba m) ar vidurkiu(irasyti V arba v)";
    while (true) {
        if (cin >> c && c == 'V' || c == 'v' || c == 'M' || c == 'm') {
            break;
        }
        else {
            cout << "Neteisingas ivedimas, iveskite v arba m: ";
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }

}

void mediana(vector<Studentas>& grupe)
{
    for (auto& A : grupe) {
        int n = A.paz.size();
       sort(A.paz.begin(), A.paz.end());

       if (n % 2 != 0) {
           A.med = A.paz[n / 2];
       }
       else A.med = (A.paz[n / 2 - 1] + A.paz[n / 2]) / 2.0;
    }


}
void outputas(const vector<Studentas>& grupe, char c) {;
    if (c == 'V' || c == 'v') {
        cout << left << setw(10) << "Vardas" << left << setw(20) << "Pavarde" << left << setw(10) << "vidurkis" << endl;
        for (auto A : grupe) {

            cout << left << setw(10) << A.vardas << left << setw(20) << A.pavarde;
            cout << left << setw(10) << fixed << setprecision(2) << A.vid << endl;
        }
    }
    if (c == 'M' || c == 'm') {
        cout << left << setw(10) << "Vardas" << left << setw(20) << "Pavarde" << left << setw(10) << "mediana" << endl;

        for (auto A : grupe) {

            cout << left << setw(10) << A.vardas << left << setw(20) << A.pavarde;
            cout << setw(10) << fixed << setprecision(2) << A.med<<endl;
        }
    }
}
