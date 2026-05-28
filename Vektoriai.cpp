#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>

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

vector<string> vardai = { "Kazys", "Petriukas", "Alfonsas", "Jonas", "Dziugas", "Algis", "Eugenija", "Agne", "Vitalija","Anastasija" };
vector<string> pavardes = { "Ilgauskas", "Javtokas", "Katunskyte", "Audrinis", "Milinskas", "Aleksandravicius", "Siskauskas", "Grybauskaite", "Meilutyte", "Cmilyte" };

void inranka(vector <Studentas>& grupe);
void randpazymiai(vector <Studentas>& grupe);
void random(vector <Studentas>& grupe);
void outputas(const vector <Studentas>& grupe, char& rez);

int main() {
    srand(time(0));
    vector<Studentas> grupe;
    char rez;

    int pasirinkimas;
    cout << "Pasirinkite kaip bus vykdoma programa: " << endl;
    cout << " 1 - ivedimas ranka" << endl;
    cout << " 2 - generuojami pazymiai" << endl;
    cout << " 3 - generuojami studentai ir pazymiai" << endl;
    cout << " 4 - baigti darba ";

        cin >> pasirinkimas;
        if (pasirinkimas == 1) {
            inranka(grupe);
        }
        if (pasirinkimas == 2) {
            randpazymiai(grupe);
        }
        if (pasirinkimas == 3) {
            random(grupe);
        }
        if (pasirinkimas == 4) {
            return 0;
        }

    
    outputas(grupe, rez);
}

void inranka(vector <Studentas>& grupe) {

    while (true) {
        Studentas A;
        int sum = 0;
        cout << "Iveskite studento vardo ir pavarde. Norint baigti studentu ivedima, iveskite 0: " << endl;
        cin >> A.vardas >> A.pavarde;

        if (A.vardas == "0" || A.pavarde == "0") {
            break;
        }
        int temp;
        cout << "Iveskite pazymius nuo 1 iki 10. Norint baigti pazymiu ivedima, iveskite 0: " << endl;

        while (true) {
            if (cin >> temp) {
                if (temp == 0) {
                    break;
                }
                if (temp >= 1 && temp <= 10) {
                    A.paz.push_back(temp);
                    sum += temp;
                }
                else {
                    cout << "Neteisingas pazymys, iveskite 1-10 arba 0: " << endl;
                }
            }
            else {
                cout << "Neteisingas ivedimas, iveskite skaiciu: " << endl;
                cin.clear();
                cin.ignore(10000, '\n');
            }
        }

        cout << "Iveskite egzamino rezultata: " << endl;
        while (true) {
            if (cin >> A.egz && A.egz >= 1 && A.egz <= 10) {
                break;
            }
            else {
                cout << "Neteisingas ivedimas, iveskite skaiciu nuo 1 iki 10: " << endl;
                cin.clear();
                cin.ignore(10000, '\n');
            }
        }
        int n = A.paz.size();
        if (n > 0) {
            A.vid = sum * 1.0 / (n * 1.0) * 0.4 + A.egz * 0.6;
        }

        sort(A.paz.begin(), A.paz.end());
        if (n % 2 != 0) {
            A.med = A.paz[n / 2];
            A.med = A.med * 0.4 + A.egz * 0.6;
        }
        else if (n > 0) {
            A.med = (A.paz[n / 2 - 1] + A.paz[n / 2]) / 2.0;
            A.med = A.med * 0.4 + A.egz * 0.6;

        }

    grupe.push_back(A);
    } 
    
}

void randpazymiai(vector <Studentas>& grupe) {

    while (true) {
        Studentas A;
        int sum = 0;
        cout << "Iveskite studento vardo ir pavarde. Norint baigti studentu ivedima, iveskite 0: " << endl;
        cin >> A.vardas >> A.pavarde;

        if (A.vardas == "0" || A.pavarde == "0") {
            break;
        }
        int kiek;
        cout << "Iveskite kiek norite atsitiktinai sugeneruotu pazymiu: " << endl;
        cin >> kiek;

        for (int i = 0; i < kiek; i++) {
            int rng = rand() % 10 + 1;
            A.paz.push_back(rng);
            sum += rng;
        }

        A.egz = rand() % 10 + 1;

        int n = A.paz.size();
        if (n > 0) {
            A.vid = sum * 1.0 / (n * 1.0) * 0.4 + A.egz * 0.6;
        }

        sort(A.paz.begin(), A.paz.end());
        if (n % 2 != 0) {
            A.med = A.paz[n / 2];
            A.med = A.med * 0.4 + A.egz * 0.6;
        }
        else if (n > 0) {
            A.med = (A.paz[n / 2 - 1] + A.paz[n / 2]) / 2.0;
            A.med = A.med * 0.4 + A.egz * 0.6;

        }
    grupe.push_back(A);
    }
}


void random(vector <Studentas>& grupe) {

        int kiek1;
        cout << "Kiek studentu sugeneruoti? " << endl;
        cin >> kiek1;

        for (int i = 0; i < kiek1; i++) {
            Studentas A;
            int sum = 0;
            A.vardas = vardai[rand() % vardai.size()];
            A.pavarde = pavardes[rand() % pavardes.size()];

            int kiek;
            cout << "Iveskite kiek norite atsitiktinai sugeneruotu pazymiu: " << endl;
            cin >> kiek;

            for (int j = 0; j < kiek; j++) {
                int rng = rand() % 10 + 1;
                A.paz.push_back(rng);
                sum += rng;
            }

            A.egz = rand() % 10 + 1;

            int n = A.paz.size();
            if (n > 0) {
                A.vid = sum * 1.0 / (n * 1.0) * 0.4 + A.egz * 0.6;
            }

            sort(A.paz.begin(), A.paz.end());
            if (n % 2 != 0) {
                A.med = A.paz[n / 2];
                A.med = A.med * 0.4 + A.egz * 0.6;
            }
            else if (n > 0) {
                A.med = (A.paz[n / 2 - 1] + A.paz[n / 2]) / 2.0;
                A.med = A.med * 0.4 + A.egz * 0.6;

            }
            grupe.push_back(A);
        }
}

void outputas(const vector<Studentas>& grupe, char &rez) {
    cout << "Rezultata isvesti su mediana(irasyti M arba m) ar vidurkiu(irasyti V arba v): " << endl;
    cin >> rez;
    while (true) {
        if (rez == 'V' || rez == 'v' || rez == 'M' || rez == 'm') {
            break;
        }
        else {
            cout << "Neteisingas ivedimas, iveskite v arba m: " << endl;
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }
    if (rez == 'V' || rez == 'v') {
        cout << left << setw(10) << "Vardas" << left << setw(20) << "Pavarde" << left << setw(10) << "vidurkis" << endl;
        for (auto A : grupe) {

            cout << left << setw(10) << A.vardas << left << setw(20) << A.pavarde;
            cout << left << setw(10) << fixed << setprecision(2) << A.vid << endl;
        }
    }
    if (rez == 'M' || rez == 'm') {
        cout << left << setw(10) << "Vardas" << left << setw(20) << "Pavarde" << left << setw(10) << "mediana" << endl;
        for (auto A : grupe) {

            cout << left << setw(10) << A.vardas << left << setw(20) << A.pavarde;
            cout << setw(10) << fixed << setprecision(2) << A.med << endl;
        }
    }
}
