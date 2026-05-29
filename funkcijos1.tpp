#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <type_traits>
#include <vector>
#include <list>
#include "studentai1.h"

template <typename Container>
void skaityti(Container& grupe, const std::string& failas) {
    grupe.clear();

    if constexpr (std::is_same<Container, std::vector<Studentas>>::value)
        grupe.reserve(10000000);

    std::ifstream in(failas);
    in.sync_with_stdio(false);

    if (!in.is_open()) {
        std::cout << "Nepavyko atidaryti failo: " << failas << "\n";
        return;
    }

    std::string line;
    std::getline(in, line);

    while (std::getline(in, line)) {
        if (line.empty()) continue;

        std::istringstream iss(line);
        Studentas A;
        std::string v, p;
        iss >> v >> p;
        if (v.empty() || p.empty()) continue;
        A.setVardas(v);
        A.setPavarde(p);

        if (A.vardas.empty() || A.pavarde.empty()) continue;

        std::vector<int> visi;
        visi.reserve(6);
        int x;
        while (iss >> x) visi.push_back(x);

        if (visi.size() < 2) continue;

       int egz = visi.back();
       visi.pop_back();
       A.setEgz(egz);
       A.setPaz(std::move(visi));
       A.finalize()

        grupe.push_back(std::move(A));
    }

}

template <typename Container>
void rikiuoti(Container& grupe) {
    auto cmp = [](const Studentas& a, const Studentas& b) {
        return a.vid < b.vid;
    };

    if constexpr (std::is_same<Container, std::list<Studentas>>::value)
        grupe.sort(cmp);
    else
        std::sort(grupe.begin(), grupe.end(), cmp);
}

template <typename Container>
void skirstyti1(const Container& grupe, Container& vargsiukai, Container& kietiakai) {
    std::partition_copy(
        grupe.begin(), grupe.end(),
        std::back_inserter(kietiakai),
        std::back_inserter(vargsiukai),
        [](const Studentas& s) { return s.vid >= 5.0; }
    );
}

template <typename Container>
void skirstyti2(Container& studentai, Container& vargsiukai) {
    std::copy_if(
        studentai.begin(), studentai.end(),
        std::back_inserter(vargsiukai),
        [](const Studentas& s) { return s.vid < 5.0; }
    );

    auto it = std::remove_if(
        studentai.begin(), studentai.end(),
        [](const Studentas& s) { return s.vid < 5.0; }
    );
    studentai.erase(it, studentai.end());
}

template <typename Container>
void skirstyti3(Container& studentai, Container& vargsiukai) {
    if constexpr (std::is_same<Container, std::list<Studentas>>::value) {
        for (auto it = studentai.begin(); it != studentai.end();) {
            if (it->vid < 5.0)
                vargsiukai.splice(vargsiukai.end(), studentai, it++);
            else
                ++it;
        }
    }
    else {
        auto it = std::partition(
            studentai.begin(), studentai.end(),
            [](const Studentas& s) { return s.vid >= 5.0; }
        );
        std::copy(it, studentai.end(), std::back_inserter(vargsiukai));
        studentai.erase(it, studentai.end());
    }
}

template <typename Container>
void isvestifaila(const Container& grupe, const std::string& failas) {
    std::ofstream out(failas);
    out.sync_with_stdio(false);

    for (const auto& s : grupe)
        out << s.vardas << ' ' << s.pavarde << ' ' << s.vid << '\n';
}

inline void generuotifaila(int kiek, const std::string& failas) {
    std::ofstream out(failas);
    out.sync_with_stdio(false);

    out << "Vardas Pavarde ND1 ND2 ND3 ND4 ND5 Egz\n";

    for (int i = 1; i <= kiek; i++) {
        out << "Vardas" << i << " Pavarde" << i << ' ';
        for (int j = 0; j < 5; j++)
            out << rand() % 10 + 1 << ' ';
        out << rand() % 10 + 1 << '\n';

        if (i % 100000 == 0)
            std::cout << "Sugeneruota: " << i << '\n';
    }
}
