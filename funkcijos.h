#ifndef FUNKCIJOS_H
#define FUNKCIJOS_H

#include "studentai.h"
#include <vector>
#include <string>

using std::vector;
using std::string;

void inranka(vector<Studentas>& grupe);
void randpazymiai(vector<Studentas>& grupe);
void random(vector<Studentas>& grupe);
void outputas(const vector<Studentas>& grupe, char& rez);
void skaityti(vector<Studentas>& grupe, string& failas);
void rikiuoti(vector<Studentas>& grupe);

#endif