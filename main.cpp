#include <iostream>
#include <chrono>
#include <vector>      
#include <string>      
#include <cstdlib>     
#include <ctime>       
#include "funkcijos.h"

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
    cout << " 5 - nuskaityti failus";

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

    rikiuoti(grupe);
    outputas(grupe, rez);
}
