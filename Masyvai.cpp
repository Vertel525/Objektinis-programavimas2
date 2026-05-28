#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using std::string;
using std::cin;
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
    int *paz;
    int pazkiek;
    int egz;
    double vid;
    double med;
};

const string vardai[10] = { "Kazys", "Petriukas", "Alfonsas", "Jonas", "Dziugas", "Algis", "Eugenija", "Agne", "Vitalija","Anastasija" };
const string pavardes[10] = { "Ilgauskas", "Javtokas", "Katunskyte", "Audrinis", "Milinskas", "Aleksandravicius", "Siskauskas", "Grybauskaite", "Meilutyte", "Cmilyte" };

void inranka(Studentas *&grupe, int &kiek);
void randpazymiai(Studentas *&grupe, int &kiek);
void random(Studentas *&grupe, int &kiek);
void outputas(Studentas *grupe, char& rez, int kiek);

int main() {
    srand(time(0));
    Studentas* grupe = nullptr;
    int kiek = 0;
    char rez;

    int pasirinkimas;
    cout << "Pasirinkite kaip bus vykdoma programa: " << endl;
    cout << " 1 - ivedimas ranka" << endl;
    cout << " 2 - generuojami pazymiai" << endl;
    cout << " 3 - generuojami studentai ir pazymiai" << endl;
    cout << " 4 - baigti darba ";

    cin >> pasirinkimas;
    if (pasirinkimas == 1) {
        inranka(grupe, kiek);
    }
    if (pasirinkimas == 2) {
        randpazymiai(grupe, kiek);
    }
    if (pasirinkimas == 3) {
        random(grupe, kiek);
    }
    if (pasirinkimas == 4) {
        return 0;
    }

    outputas(grupe, rez, kiek);

    for (int i = 0; i < kiek; i++) {
        delete[] grupe[i].paz;
    }
    delete[] grupe;

    return 0;
}
void pushback(Studentas *&grupe, int &kiek, Studentas &A){
    Studentas* naujas = new Studentas[kiek + 1];
    for (int i = 0; i < kiek; i++) {
        naujas[i] = grupe[i];
    }
    naujas[kiek] = A;
    delete[] grupe;
    grupe = naujas;
    kiek++;
}

void inranka(Studentas *&grupe, int &kiek) {

    while (true) {
        Studentas A;
        int sum = 0;
        A.paz = nullptr;
        A.pazkiek = 0;
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
                    int* naujas = new int[A.pazkiek + 1];
                    for (int i = 0; i < A.pazkiek; i++) {
                        naujas[i] = A.paz[i];
                    }
                    naujas[A.pazkiek] = temp;
                    delete[] A.paz;
                    A.paz = naujas;
                    A.pazkiek++;
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
        int n = A.pazkiek;
        if (n > 0) {
            A.vid = sum * 1.0 / (n * 1.0) * 0.4 + A.egz * 0.6;
        }

        sort(A.paz, A.paz + n);
        if (n % 2 != 0) {
            A.med = A.paz[n / 2] * 0.4 + A.egz * 0.6;
        }
        else if (n > 0) {
            A.med = (A.paz[n / 2 - 1] + A.paz[n / 2]) / 2.0;
            A.med = A.med * 0.4 + A.egz * 0.6;

        }

        pushback(grupe, kiek, A);
    }

}

void randpazymiai(Studentas *&grupe, int &kiek) {

    while (true) {
        Studentas A;
        int sum = 0;
        A.paz = nullptr;
        A.pazkiek = 0;
        cout << "Iveskite studento vardo ir pavarde. Norint baigti studentu ivedima, iveskite 0: " << endl;
        cin >> A.vardas >> A.pavarde;

        if (A.vardas == "0" || A.pavarde == "0") {
            break;
        }
        int pazkiek;
        cout << "Iveskite kiek norite atsitiktinai sugeneruotu pazymiu: " << endl;
        cin >> pazkiek;

        A.paz = new int[pazkiek];
        A.pazkiek = pazkiek;

        for (int i = 0; i < pazkiek; i++) {
            A.paz[i]= rand() % 10 + 1;
            sum += A.paz[i];
        }

        A.egz = rand() % 10 + 1;

        int n = A.pazkiek;
        if (n > 0) {
            A.vid = sum * 1.0 / (n * 1.0) * 0.4 + A.egz * 0.6;
        }

        sort(A.paz, A.paz + n);
        if (n % 2 != 0) {
            A.med = A.paz[n / 2] * 0.4 + A.egz * 0.6;
        }
        else if (n > 0) {
            A.med = (A.paz[n / 2 - 1] + A.paz[n / 2]) / 2.0;
            A.med = A.med * 0.4 + A.egz * 0.6;

        }
        pushback(grupe, kiek, A);
    }
}

void random(Studentas *&grupe, int &kiek) {

    Studentas A;
    int kiek1, sum = 0;
    cout << "Kiek studentu sugeneruoti? " << endl;
    cin >> kiek1;

    for (int i = 0; i < kiek1; i++) {
        int sum = 0;
        A.paz = nullptr;
        A.pazkiek = 0;
        A.vardas = vardai[rand() % 10];
        A.pavarde = pavardes[rand() % 10];

        int pazkiek;
        cout << "Iveskite kiek norite atsitiktinai sugeneruotu pazymiu: " << endl;
        cin >> pazkiek;

        A.paz = new int[pazkiek];
        A.pazkiek = pazkiek;

        for (int j = 0; j < pazkiek; j++) {
            A.paz[j] = rand() % 10 + 1;
            sum += A.paz[j];
        }

        A.egz = rand() % 10 + 1;

        int n = A.pazkiek;
        if (n > 0) {
            A.vid = sum * 1.0 / (n * 1.0) * 0.4 + A.egz * 0.6;
        }

        sort(A.paz, A.paz + n);
        if (n % 2 != 0) {
            A.med = A.paz[n / 2];
            A.med = A.med * 0.4 + A.egz * 0.6;
        }
        else if (n > 0) {
            A.med = (A.paz[n / 2 - 1] + A.paz[n / 2]) / 2.0;
            A.med = A.med * 0.4 + A.egz * 0.6;

        }
        pushback(grupe, kiek, A);
    }
}

void outputas(Studentas *grupe, char& rez, int kiek) {
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
        for (int i = 0; i < kiek; i++) {

            cout << left << setw(10) << grupe[i].vardas << left << setw(20) << grupe[i].pavarde;
            cout << left << setw(10) << fixed << setprecision(2) << grupe[i].vid << endl;
        }
    }
    if (rez == 'M' || rez == 'm') {
        cout << left << setw(10) << "Vardas" << left << setw(20) << "Pavarde" << left << setw(10) << "mediana" << endl;
        for (int i = 0; i < kiek; i++) {

            cout << left << setw(10) << grupe[i].vardas << left << setw(20) << grupe[i].pavarde;
            cout << left << setw(10) << fixed << setprecision(2) << grupe[i].med << endl;
        }
    }
}
