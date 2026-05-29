#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <vector>
#include <algorithm>

class Studentas {
private:
    std::string vardas_;
    std::string pavarde_;
    std::vector<int> paz_;
    int egz_ = 0;
    double vid_ = 0.0;
    double med_ = 0.0;
public:
    Studentas() : egz_(0), vid_(0.0), med_(0.0) {}


void skaiciuoti() {
    int n = (int)paz_.size();

    if (n == 0) return;
    int sum = 0;

    for (int x : paz_) sum += x;
    vid_ = sum * 1.0 / n * 0.4 + egz_ * 0.6;

    std::vector<int> sorted = paz_;
    std::sort(sorted.begin(), sorted.end());

    if (n % 2 != 0)
        med_ = sorted[n / 2];
    else
        med_ = (sorted[n / 2 - 1] + sorted[n / 2]) / 2.0;
    med_ = med_ * 0.4 + egz_ * 0.6;
}

public: 
    Studentas(const std::string& vardas, const std::string& pavarde,
        const std::vector<int>& paz, int egz)
        : vardas_(vardas), pavarde_(pavarde), paz_(paz), egz_(egz)
    {
        skaiciuoti();
    }


#endif
