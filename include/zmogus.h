#ifndef ZMOGUS_H
#define ZMOGUS_H

#include <string>
#include <iostream>

class Zmogus {
protected:
    std::string vardas_;
    std::string pavarde_;

public:
    Zmogus() {}

    Zmogus(const std::string& vardas, const std::string& pavarde)
        : vardas_(vardas), pavarde_(pavarde) {}

    Zmogus(const Zmogus& other)
        : vardas_(other.vardas_), pavarde_(other.pavarde_) {}

    Zmogus(Zmogus&& other) noexcept
        : vardas_(std::move(other.vardas_)),
        pavarde_(std::move(other.pavarde_)) {}

    Zmogus& operator=(const Zmogus& other) {
        if (this != &other) {
            vardas_ = other.vardas_;
            pavarde_ = other.pavarde_;
        }
        return *this;
    }

    Zmogus& operator=(Zmogus&& other) noexcept {
        if (this != &other) {
            vardas_ = std::move(other.vardas_);
            pavarde_ = std::move(other.pavarde_);
        }
        return *this;
    }

    virtual ~Zmogus() {}

    inline const std::string& vardas()  const { return vardas_; }
    inline const std::string& pavarde() const { return pavarde_; }

    void setVardas(const std::string& v) { vardas_ = v; }
    void setPavarde(const std::string& p) { pavarde_ = p; }

    virtual double vid() const = 0;
    virtual double med() const = 0;
    virtual void finalize() = 0;
    virtual void print(std::ostream& os) const = 0;

    friend std::ostream& operator<<(std::ostream& os, const Zmogus& z) {
        z.print(os);
        return os;
    }
};

#endif