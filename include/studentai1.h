#ifndef STUDENT_H
#define STUDENT_H

#include "zmogus.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <sstream>

class Studentas : public Zmogus {
private:
    std::vector<int> paz_;
    int egz_ = 0;
    double vid_ = 0.0;
    double med_ = 0.0;

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
    Studentas() : Zmogus(), egz_(0), vid_(0.0), med_(0.0) {}

    Studentas(const std::string& vardas, const std::string& pavarde,
        const std::vector<int>& paz, int egz)
        : Zmogus(vardas, pavarde), paz_(paz), egz_(egz)
    {
        skaiciuoti();
    }

    Studentas(const Studentas& other)
        : Zmogus(other),
        paz_(other.paz_), egz_(other.egz_),
        vid_(other.vid_), med_(other.med_) {}

    Studentas(Studentas&& other) noexcept
        : Zmogus(std::move(other)),
        paz_(std::move(other.paz_)),
        egz_(other.egz_), vid_(other.vid_), med_(other.med_) {}

    Studentas& operator=(const Studentas& other) {
        if (this != &other) {
            Zmogus::operator=(other);
            paz_ = other.paz_;
            egz_ = other.egz_;
            vid_ = other.vid_;
            med_ = other.med_;
        }
        return *this;
    }

    Studentas& operator=(Studentas&& other) noexcept {
        if (this != &other) {
            Zmogus::operator=(std::move(other));
            paz_ = std::move(other.paz_);
            egz_ = other.egz_;
            vid_ = other.vid_;
            med_ = other.med_;
        }
        return *this;
    }

    ~Studentas() override {}

    inline double vid() const override { return vid_; }
    inline double med() const override { return med_; }
    inline const std::vector<int>& paz() const { return paz_; }
    inline int egz() const { return egz_; }

    void setEgz(int e) { egz_ = e; }
    void setPaz(std::vector<int>&& p) { paz_ = std::move(p); }
    void addPaz(int p) { paz_.push_back(p); }
    void finalize() override { skaiciuoti(); }

    void print(std::ostream& os) const override {
        os << vardas_ << " " << pavarde_;
        for (int p : paz_) os << " " << p;
        os << " " << egz_;
        os << " (vid: " << vid_ << ", med: " << med_ << ")";
    }

    friend std::istream& operator>>(std::istream& is, Studentas& s) {
        s.paz_.clear();
        s.egz_ = 0;
        s.vid_ = 0.0;
        s.med_ = 0.0;

        if (!(is >> s.vardas_ >> s.pavarde_)) return is;

        std::vector<int> visi;
        int x;
        while (is >> x) visi.push_back(x);

        if (visi.size() >= 2) {
            s.egz_ = visi.back();
            visi.pop_back();
            s.paz_ = std::move(visi);
            s.skaiciuoti();
        }
        return is;
    }
};

inline bool compareVid(const Studentas& a, const Studentas& b) {
    return a.vid() < b.vid();
}
inline bool comparePavarde(const Studentas& a, const Studentas& b) {
    return a.pavarde() < b.pavarde();
}

#endif