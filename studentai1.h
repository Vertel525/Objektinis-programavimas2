#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <vector>
#include <algorithm>

struct Studentas {
    std::string vardas, pavarde;
    std::vector<int> paz;
    int egz = 0;
    double vid = 0.0;
    double med = 0.0;

    void skaiciuoti() {
        int n = (int)paz.size();
        if (n == 0) return;

        int sum = 0;
        for (int x : paz) sum += x;
        vid = sum * 1.0 / n * 0.4 + egz * 0.6;

        std::vector<int> sorted = paz;
        std::sort(sorted.begin(), sorted.end());

        if (n % 2 != 0)
            med = sorted[n / 2];
        else
            med = (sorted[n / 2 - 1] + sorted[n / 2]) / 2.0;

        med = med * 0.4 + egz * 0.6;
    }
};

#endif
