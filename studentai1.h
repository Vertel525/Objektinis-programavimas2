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

    Studentas(const Studentas& other)
        : vardas_(other.vardas_), pavarde_(other.pavarde_),
        paz_(other.paz_), egz_(other.egz_),
        vid_(other.vid_), med_(other.med_) {}

    Studentas(Studentas&& other) noexcept
        : vardas_(std::move(other.vardas_)),
        pavarde_(std::move(other.pavarde_)),
        paz_(std::move(other.paz_)),
        egz_(other.egz_), vid_(other.vid_), med_(other.med_) {}

    Studentas& operator=(const Studentas& other) {
        if (this != &other) {
            vardas_ = other.vardas_;
            pavarde_ = other.pavarde_;
            paz_ = other.paz_;
            egz_ = other.egz_;
            vid_ = other.vid_;
            med_ = other.med_;
        }
        return *this;
    }

    Studentas& operator=(Studentas&& other) noexcept {
        if (this != &other) {
            vardas_ = std::move(other.vardas_);
            pavarde_ = std::move(other.pavarde_);
            paz_ = std::move(other.paz_);
            egz_ = other.egz_;
            vid_ = other.vid_;
            med_ = other.med_;
        }
        return *this;
    }

    ~Studentas() {}

    inline const std::string& vardas()  const { return vardas_; }
    inline const std::string& pavarde() const { return pavarde_; }
    inline const std::vector<int>& paz() const { return paz_; }
    inline int    egz() const { return egz_; }
    inline double vid() const { return vid_; }
    inline double med() const { return med_; }

    void setVardas(const std::string& v) { vardas_ = v; }
    void setPavarde(const std::string& p) { pavarde_ = p; }
    void setEgz(int e) { egz_ = e; }
    void setPaz(std::vector<int>&& p) { paz_ = std::move(p); }
    void addPaz(int p) { paz_.push_back(p); }
    void finalize() { skaiciuoti(); }

#endif
