#include <iostream>
#include <chrono>
#include <vector>      
#include <string>      
#include <cstdlib>     
#include <ctime>       
#include "funkcijos1.h"

using namespace std;

int main() {
    srand(time(0));

    vector<Studentas> grupe;
    char rez;
    string failas;

    int pasirinkimas;
    cout << "Pasirinkite kaip bus vykdoma programa: " << endl;
    cout << " 1 - ivedimas ranka" << endl;
    cout << " 2 - generuojami pazymiai" << endl;
    cout << " 3 - generuojami studentai ir pazymiai" << endl;
    cout << " 4 - baigti darba " << endl;
    cout << " 5 - nuskaityti failus" << endl;
    cout << " 6 - failo generavimas";

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
    if (pasirinkimas == 5) {

        auto start = std::chrono::high_resolution_clock::now();

        skaityti(grupe, failas);

        auto end = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double> diff = end - start;

        cout << "Failo nuskaitymas uztruko: " << diff.count() << " s" << endl;
    }

    if (pasirinkimas >= 1 && pasirinkimas <= 5) {
        rikiuoti(grupe);
        outputas(grupe, rez);
    }
    if (pasirinkimas == 6) {

        // 1 TYRIMAS (failo kūrimas)

        auto startGen = chrono::high_resolution_clock::now();
        generuotifaila(1000, "1000.txt");
        generuotifaila(10000, "10000.txt");
        generuotifaila(100000, "100000.txt");
        generuotifaila(1000000, "1000000.txt");
        generuotifaila(10000000, "10000000.txt");
        auto endGen = chrono::high_resolution_clock::now();

        cout << "Failo kurimas: " << chrono::duration<double>(endGen - startGen).count() << " s" << endl;
    


    // 2 TYRIMAS (duomenų apdorojimas)

        vector<Studentas> grupe;
        vector<Studentas> vargsiukai;
        vector<Studentas> kietiakai;

        string failas;
        cout << "Iveskite faila: ";
        cin >> failas;

        auto totalStart = chrono::high_resolution_clock::now();

        auto t1 = chrono::high_resolution_clock::now();
        skaityti(grupe, failas);
        auto t2 = chrono::high_resolution_clock::now();

        cout << grupe.size() << " irasu nuskaitymo laikas: " << chrono::duration<double>(t2 - t1).count() << endl;

        auto t3 = chrono::high_resolution_clock::now();
        rikiuoti(grupe);
        auto t4 = chrono::high_resolution_clock::now();

        cout << grupe.size() << " irasu rusiavimo laikas: " << chrono::duration<double>(t4 - t3).count() << endl;

        auto t5 = chrono::high_resolution_clock::now();
        skirstyti(grupe, vargsiukai, kietiakai);
        auto t6 = chrono::high_resolution_clock::now();

        cout << grupe.size() << " irasu dalijimo laikas: " << chrono::duration<double>(t6 - t5).count() << endl;


        auto t7 = chrono::high_resolution_clock::now();
        isvestifaila(vargsiukai, "vargsiukai.txt");
        auto t8 = chrono::high_resolution_clock::now();

        cout << "Vargsiuku irasymas: " << chrono::duration<double>(t8 - t7).count() << endl;

        auto t9 = chrono::high_resolution_clock::now();
        isvestifaila(kietiakai, "kietiakai.txt");
        auto t10 = chrono::high_resolution_clock::now();

        cout << "Kietiaku irasymas: "<< chrono::duration<double>(t10 - t9).count() << endl;

        auto totalEnd = chrono::high_resolution_clock::now();

        cout << "VISAS LAIKAS: "<< chrono::duration<double>(totalEnd - totalStart).count() << " s" <<endl;
    }
}
