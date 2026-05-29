#ifndef FUNKCIJOS_H
#define FUNKCIJOS_H

#include "studentai1.h"
#include <vector>
#include <list>
#include <deque>
#include <string>

void inranka(std::vector<Studentas>& grupe);
void randpazymiai(std::vector<Studentas>& grupe);
void randomvisk(std::vector<Studentas>& grupe);
void outputas(const std::vector<Studentas>& grupe, char& rez);

template <typename Container>
void skaityti(Container& grupe, const std::string& failas);

template <typename Container>
void rikiuoti(Container& grupe);

template <typename Container>
void skirstyti1(const Container& grupe, Container& vargsiukai, Container& kietiakai);

template <typename Container>
void skirstyti2(Container& studentai, Container& vargsiukai);

template <typename Container>
void skirstyti3(Container& studentai, Container& vargsiukai);

template <typename Container>
void isvestifaila(const Container& grupe, const std::string& failas);

inline void generuotifaila(int kiek, const std::string& failas);

#include "funkcijos1.tpp"

#endif