#include "funkcijos1.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cstdlib>
#include <fstream>

using std::string;
using std::vector;
using std::cout;
using std::cin;
using std::endl;
using std::sort;
using std::ofstream;
using std::left;
using std::right;
using std::setw;
using std::fixed;
using std::setprecision;

void inranka(vector<Studentas>& grupe) {
    while (true) {
        Studentas A;
        cout << "Iveskite studento varda ir pavarde (0 - baigti): ";
        cin >> A.vardas >> A.pavarde;
        if (A.vardas == "0" || A.pavarde == "0") break;

        cout << "Iveskite pazymius (0 - baigti): ";
        int temp;
        while (true) {
            if (cin >> temp) {
                if (temp == 0) break;
                if (temp >= 1 && temp <= 10) A.paz.push_back(temp);
                else cout << "Neteisingas pazymys (1-10 arba 0): ";
            }
            else {
                cout << "Iveskite skaiciu: ";
                cin.clear();
                cin.ignore(10000, '\n');
            }
        }

        cout << "Iveskite egzamino rezultata (1-10): ";
        while (true) {
            if (cin >> A.egz && A.egz >= 1 && A.egz <= 10) break;
            cout << "Neteisingas ivedimas (1-10): ";
            cin.clear();
            cin.ignore(10000, '\n');
        }

        A.skaiciuoti();
        grupe.push_back(std::move(A));
    }
}

void randpazymiai(vector<Studentas>& grupe) {
    while (true) {
        Studentas A;
        cout << "Iveskite studento varda ir pavarde (0 - baigti): ";
        cin >> A.vardas >> A.pavarde;
        if (A.vardas == "0" || A.pavarde == "0") break;

        int kiek;
        cout << "Kiek atsitiktiniu pazymiu? ";
        cin >> kiek;

        A.paz.reserve(kiek);
        for (int i = 0; i < kiek; i++)
            A.paz.push_back(rand() % 10 + 1);

        A.egz = rand() % 10 + 1;
        A.skaiciuoti();
        grupe.push_back(std::move(A));
    }
}

void randomvisk(vector<Studentas>& grupe) {
    int kiek1;
    cout << "Kiek studentu sugeneruoti? ";
    cin >> kiek1;

    vector<string> vardai = { "Kazys","Petriukas","Alfonsas","Jonas","Dziugas",
                                "Algis","Eugenija","Agne","Vitalija","Anastasija" };
    vector<string> pavardes = { "Ilgauskas","Javtokas","Katunskyte","Audrinis",
                                 "Milinskas","Aleksandravicius","Siskauskas",
                                 "Grybauskaite","Meilutyte","Cmilyte" };

    int kiek;
    cout << "Kiek atsitiktiniu pazymiu kiekvienam? ";
    cin >> kiek;

    grupe.reserve(grupe.size() + kiek1);
    for (int i = 0; i < kiek1; i++) {
        Studentas A;
        A.vardas = vardai[rand() % vardai.size()];
        A.pavarde = pavardes[rand() % pavardes.size()];

        A.paz.reserve(kiek);
        for (int j = 0; j < kiek; j++)
            A.paz.push_back(rand() % 10 + 1);

        A.egz = rand() % 10 + 1;
        A.skaiciuoti();
        grupe.push_back(std::move(A));
    }
}

void outputas(const vector<Studentas>& grupe, char& rez) {
    cout << "Rezultata isvesti su mediana (M/m) ar vidurkiu (V/v): ";
    while (true) {
        cin >> rez;
        if (rez == 'V' || rez == 'v' || rez == 'M' || rez == 'm') break;
        cout << "Iveskite v arba m: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }

    cout << "Kur isvesti rezultatus?\n 1 - i ekrana\n 2 - i CSV faila\n";
    int kur; cin >> kur;

    bool useVid = (rez == 'V' || rez == 'v');

    if (kur == 1) {
        cout << left << setw(12) << "Vardas"
            << setw(20) << "Pavarde"
            << (useVid ? "Vidurkis" : "Mediana") << '\n';

        for (const auto& A : grupe)
            cout << left << setw(12) << A.vardas
            << setw(20) << A.pavarde
            << fixed << setprecision(2)
            << (useVid ? A.vid : A.med) << '\n';
    }
    else if (kur == 2) {
        string outfailas;
        cout << "Iveskite CSV failo pavadinima: ";
        cin >> outfailas;

        std::ofstream out(outfailas);
        if (!out) { cout << "Nepavyko sukurti failo.\n"; return; }

        out << "Vardas,Pavarde," << (useVid ? "Vidurkis" : "Mediana") << '\n';
        for (const auto& A : grupe)
            out << A.vardas << ',' << A.pavarde << ','
            << fixed << setprecision(2)
            << (useVid ? A.vid : A.med) << '\n';

        cout << "Rezultatai issaugoti: " << outfailas << '\n';
    }
    else {
        cout << "Blogas pasirinkimas. Nieko neisvesta.\n";
    }
}