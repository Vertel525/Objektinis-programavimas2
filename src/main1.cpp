#include <iostream>
#include <chrono>
#include <vector>
#include <list>
#include <deque>
#include <string>
#include <cstdlib>
#include <ctime>
#include "funkcijos1.h"

using namespace std;

template <typename Container>
void testuoti(const string& failas) {
    Container studentai, vargsiukai, kietiakai;

    cout << "\n--- Failas: " << failas << " ---\n";

    auto t1 = chrono::high_resolution_clock::now();
    skaityti(studentai, failas);
    auto t2 = chrono::high_resolution_clock::now();
    cout << "  Skaitymas  : " << chrono::duration<double>(t2 - t1).count() << " s\n";

    auto t3 = chrono::high_resolution_clock::now();
    rikiuoti(studentai);
    auto t4 = chrono::high_resolution_clock::now();
    cout << "  Rikiavimas : " << chrono::duration<double>(t4 - t3).count() << " s\n";

    auto s1 = chrono::high_resolution_clock::now();
    skirstyti1(studentai, vargsiukai, kietiakai);
    auto e1 = chrono::high_resolution_clock::now();
    cout << "  Strategija1: " << chrono::duration<double>(e1 - s1).count() << " s\n";

    studentai.clear(); vargsiukai.clear();
    skaityti(studentai, failas);
    auto s2 = chrono::high_resolution_clock::now();
    skirstyti2(studentai, vargsiukai);
    auto e2 = chrono::high_resolution_clock::now();
    cout << "  Strategija2: " << chrono::duration<double>(e2 - s2).count() << " s\n";

    studentai.clear(); vargsiukai.clear();
    skaityti(studentai, failas);
    auto s3 = chrono::high_resolution_clock::now();
    skirstyti3(studentai, vargsiukai);
    auto e3 = chrono::high_resolution_clock::now();
    cout << "  Strategija3: " << chrono::duration<double>(e3 - s3).count() << " s\n";
}

int main() {
    srand((unsigned)time(0));

    cout << "Pasirinkite kaip bus vykdoma programa:\n";
    cout << " 1 - ivedimas ranka\n";
    cout << " 2 - generuojami pazymiai\n";
    cout << " 3 - generuojami studentai ir pazymiai\n";
    cout << " 4 - baigti darba\n";
    cout << " 5 - nuskaityti faila (vector)\n";
    cout << " 6 - failo generavimas ir benchmark\n";

    int pasirinkimas;
    cin >> pasirinkimas;

    if (pasirinkimas == 1 || pasirinkimas == 2 ||
        pasirinkimas == 3 || pasirinkimas == 5) {

        vector<Studentas> grupe;
        char rez;

        if (pasirinkimas == 1) {
            inranka(grupe);
        }
        else if (pasirinkimas == 2) {
            randpazymiai(grupe);
        }
        else if (pasirinkimas == 3) {
            randomvisk(grupe);
        }
        else if (pasirinkimas == 5) {
            string failas;
            cout << "Iveskite failo pavadinima: ";
            cin >> failas;

            auto start = chrono::high_resolution_clock::now();
            skaityti(grupe, failas);
            auto end = chrono::high_resolution_clock::now();
            cout << "Failo nuskaitymas uztruko: "
                << chrono::duration<double>(end - start).count() << " s\n";
        }

        rikiuoti(grupe);
        outputas(grupe, rez);
    }
    else if (pasirinkimas == 4) {
        return 0;
    }
    else if (pasirinkimas == 6) {
        cout << "\n1 - Generuoti failus\n2 - Paleisti benchmark\n";
        int sub; cin >> sub;

        if (sub == 1) {
            auto startGen = chrono::high_resolution_clock::now();
            generuotifaila(1000, "1000.txt");
            generuotifaila(10000, "10000.txt");
            generuotifaila(100000, "100000.txt");
            generuotifaila(1000000, "1000000.txt");
            generuotifaila(10000000, "10000000.txt");
            auto endGen = chrono::high_resolution_clock::now();
            cout << "Failu kurimas: "
                << chrono::duration<double>(endGen - startGen).count() << " s\n";
        }
        else if (sub == 2) {
            string failas;
            cout << "Iveskite faila: ";
            cin >> failas;

            auto totalStart = chrono::high_resolution_clock::now();

            cout << "\n===== VECTOR =====";
            testuoti<vector<Studentas>>(failas);

            cout << "\n===== LIST =====";
            testuoti<list<Studentas>>(failas);

            cout << "\n===== DEQUE =====";
            testuoti<deque<Studentas>>(failas);

            auto totalEnd = chrono::high_resolution_clock::now();
            cout << "\nVISAS LAIKAS: "
                << chrono::duration<double>(totalEnd - totalStart).count() << " s\n";

            {
                vector<Studentas> grupe, vargsiukai, kietiakai;
                skaityti(grupe, failas);
                skirstyti1(grupe, vargsiukai, kietiakai);

                auto t7 = chrono::high_resolution_clock::now();
                isvestifaila(vargsiukai, "vargsiukai.txt");
                auto t8 = chrono::high_resolution_clock::now();
                cout << "Vargsiuku irasymas: "
                    << chrono::duration<double>(t8 - t7).count() << " s\n";

                auto t9 = chrono::high_resolution_clock::now();
                isvestifaila(kietiakai, "kietiakai.txt");
                auto t10 = chrono::high_resolution_clock::now();
                cout << "Kietiaku irasymas: "
                    << chrono::duration<double>(t10 - t9).count() << " s\n";
            }
        }
    }

    return 0;
}