#include "funkcijos1.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <fstream>

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
using std::ifstream;
using std::ofstream;

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
        vector<string> vardai = { "Kazys", "Petriukas", "Alfonsas", "Jonas", "Dziugas", "Algis", "Eugenija", "Agne", "Vitalija","Anastasija" };
        vector<string> pavardes = { "Ilgauskas", "Javtokas", "Katunskyte", "Audrinis", "Milinskas", "Aleksandravicius", "Siskauskas", "Grybauskaite", "Meilutyte", "Cmilyte" };

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
void outputas(const vector<Studentas>& grupe, char& rez) {
    cout << "Rezultata isvesti su mediana (M/m) ar vidurkiu (V/v): " << endl;
    while (true) {
        cin >> rez;
        if (rez == 'V' || rez == 'v' || rez == 'M' || rez == 'm') break;
        else {
            cout << "Neteisingas ivedimas, iveskite v arba m: " << endl;
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }

    cout << "Kur isvesti rezultatus?" << endl;
    cout << " 1 - i ekrana" << endl;
    cout << " 2 - i CSV faila" << endl;

    int kur;
    cin >> kur;

    if (kur == 1) {
        if (rez == 'V' || rez == 'v') {
            cout << left << setw(10) << "Vardas" << left << setw(20) << "Pavarde" << left << setw(10) << "Vidurkis" << endl;

            for (auto A : grupe) {
                cout << left << setw(10) << A.vardas << left << setw(20) << A.pavarde << left << setw(10) << fixed << setprecision(2) << A.vid << endl;
            }
        }
        else {
            cout << left << setw(10) << "Vardas" << left << setw(20) << "Pavarde" << left << setw(10) << "Mediana" << endl;

            for (auto A : grupe) {
                cout << left << setw(10) << A.vardas << left << setw(20) << A.pavarde << left << setw(10) << fixed << setprecision(2) << A.med << endl;
            }
        }
    }
    else if (kur == 2) {
        string outfailas;
        cout << "Iveskite CSV failo pavadinima (pvz: rezultatai.csv): ";
        cin >> outfailas;

        ofstream out(outfailas);
        if (!out) {
            cout << "Nepavyko sukurti CSV failo." << endl;
            return;
        }

        if (rez == 'V' || rez == 'v') {
            out << "Vardas,Pavarde,Vidurkis" << endl;
            for (auto A : grupe) {
                out << A.vardas << "," << A.pavarde << "," << fixed << setprecision(2) << A.vid << endl;
            }
        }
        else {
            out << "Vardas,Pavarde,Mediana" << endl;
            for (auto A : grupe) {
                out << A.vardas << "," << A.pavarde << "," << fixed << setprecision(2) << A.med << endl;
            }
        }

        out.close();
        cout << "Rezultatai issaugoti faile: " << outfailas << endl;
    }
    else {
        cout << "Blogas pasirinkimas. Nieko neisvesta.\n";
    }
}


void skaityti(vector<Studentas>& grupe, string& failas)
{
    cout << "Iveskite failo pavadinima: ";
    cin >> failas;

    grupe.clear();

    std::ifstream in(failas);
    if (!in) {
        cout << "Nepavyko atidaryti failo: " << failas << endl;
        return;
    }

    string line;
    getline(in, line);

    while (getline(in, line)) {
        if (line.empty()) continue;

        std::istringstream iss(line);
        Studentas A;
        int sum = 0;

        iss >> A.vardas >> A.pavarde;

        A.paz.clear();
        int x;
        vector<int> visi;

        while (iss >> x) {
            visi.push_back(x);
        }

        if (visi.empty()) continue;

        A.egz = visi.back();
        visi.pop_back();
        A.paz = visi;

        int n = A.paz.size();
        for (int k : A.paz) sum += k;

        if (n > 0) {
            A.vid = (sum * 1.0) / n * 0.4 + A.egz * 0.6;
        }

        sort(A.paz.begin(), A.paz.end());
        if (n % 2 != 0) {
            A.med = A.paz[n / 2];
        }
        else if (n > 0) {
            A.med = (A.paz[n / 2 - 1] + A.paz[n / 2]) / 2.0;
        }
        A.med = A.med * 0.4 + A.egz * 0.6;

        grupe.push_back(A);
    }

    cout << "Nuskaityta studentu: " << grupe.size() << endl;
}
void rikiuoti(vector<Studentas>& grupe) {
    cout << "Rikiuoti pagal: " << endl;
    cout << " 1 - varda" << endl;
    cout << " 2 - pavarde" << endl;
    cout << " 3 - galutini (vidurkis)" << endl;
    cout << " 4 - galutini (mediana)" << endl;

    while (true) {
        int r;
        cin >> r;

        if (r == 1) {
            sort(grupe.begin(), grupe.end(), [](const Studentas& a, const Studentas& b) {
                return a.vardas < b.vardas;
                });
            break;
        }
        else if (r == 2) {
            sort(grupe.begin(), grupe.end(), [](const Studentas& a, const Studentas& b) {
                return a.pavarde < b.pavarde;
                });
            break;
        }
        else if (r == 3) {
            sort(grupe.begin(), grupe.end(), [](const Studentas& a, const Studentas& b) {
                return a.vid < b.vid;
                });
            break;
        }
        else if (r == 4) {
            sort(grupe.begin(), grupe.end(), [](const Studentas& a, const Studentas& b) {
                return a.med < b.med;
                });
            break;
        }
        else {
            cout << "Neteisinga ivestis, iveskite skaicius 1-4" << endl;
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }
}

void generuotifaila(int kiek, string failovardas) {

    ofstream out(failovardas);

    if (!out) {
        cout << "Nepavyko sukurti failo\n";
        return;
    }
    out << "Vardas Pavarde ND1 ND2 ND3 ND4 ND5 Egz" << endl;
    for (int i = 1; i <= kiek; i++) {
        out << "Vardas" << i << " Pavarde" << i << " ";
        for (int j = 0; j < 5; j++) {
            out << rand() % 10 + 1 << " ";
        }
        out << rand() % 10 + 1 << "\n";
        if (i % 100000 == 0) {
            cout << "Sugeneruota: " << i << endl;
        }
    }
    out.close();
}
void skirstyti(const vector<Studentas>& grupe, vector<Studentas>& vargsiukai, vector<Studentas>& kietiakai) {

    for (auto s : grupe) {
        if (s.vid < 5.0)
            vargsiukai.push_back(s);
        else
            kietiakai.push_back(s);
    }
}
void isvestifaila(const vector<Studentas>& grupe, string failas) {
    ofstream out(failas);

    if (!out) {
        cout << "Nepavyko sukurti failo\n";
        return;
    }

    for (auto s : grupe) {
        out << s.vardas << " " << s.pavarde << " " << s.vid << endl;
    }
    out.close();
}
