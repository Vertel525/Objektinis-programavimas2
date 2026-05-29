# Studentų Pažymių Skaičiuoklė

C++ programa skirta studentų pažymių valdymui. Programa leidžia įvesti studentus rankiniu būdu, generuoti atsitiktinius duomenis arba nuskaityti iš failo, tada rikiuoti ir skirstyti studentus pagal vidurkį.

---

## Versijų istorija

| Versija | Aprašas |
|---------|---------|
| v1.0 | Pradinė realizacija su `struct Studentas`, vector/list/deque konteineriai, 3 skirstymo strategijos |
| v1.1 | `struct` pakeista į `class`, pridėti konstruktoriai, destruktorius, getter/setter metodai |
| v1.2 | Pridėti `operator<<` ir `operator>>`, pilnas Rule of Five, testų failas |
| v1.5 | Sukurta abstrakti bazinė klasė `Zmogus`, `Studentas` išvesta iš jos |
| v2.0 | Doxygen dokumentacija, Google Test unit testai, CMake build sistema |

---

## Failų struktūra

```
├── zmogus.h               # Abstrakti bazinė klasė
├── studentai1.h           # Studentas klasė (išvesta iš Zmogus)
├── funkcijos1.h           # Funkcijų deklaracijos
├── funkcijos1.tpp         # Template funkcijų realizacijos
├── funckijos1.cpp         # Įvesties/išvesties funkcijų realizacijos
├── main1.cpp              # Pagrindinis failas
├── Testas.cpp             # Rankinis testų failas
├── testas_gtest.cpp       # Google Test unit testai
├── CMakeLists.txt         # CMake build konfigūracija
├── Doxyfile               # Doxygen konfigūracija
└── docs/                  # Sugeneruota dokumentacija (HTML + PDF)
    ├── html/              # HTML dokumentacija
    └── latex/             # LaTeX failai + refman.pdf
```

---

## Reikalavimai

- C++17 ar naujesnė versija
- CMake 3.14+ (unit testams su Google Test)
- Doxygen (dokumentacijos generavimui)
- Interneto ryšys pirmojo CMake paleidimo metu (Google Test atsisiunčiamas automatiškai)

---

## Kompiliavimas

### Visual Studio
1. Atidaryti `main1.vcxproj`
2. Build → Build Solution (**Ctrl+Shift+B**)
3. Paleisti (**Ctrl+F5**)

### Komandinė eilutė (g++)
```bash
g++ -std=c++17 -O2 -o programa main1.cpp funckijos1.cpp
./programa
```

---

## Įdiegimas ir paleidimas su CMake

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

Programa paleidžiama:
```bash
./programa        # Linux/Mac
programa.exe      # Windows
```

---

## Unit testai

### Rankinis testų failas (Testas.cpp)
Veikia tiesiogiai Visual Studio — atskiras projektas toje pačioje solution.

Paleidžiamas su **Ctrl+F5** kai `Testas` projektas nustatytas kaip startup.

Išvestis:
```
========== Studentas / Zmogus klases testai (v1.5) ==========

--- Zmogus abstraktumas ---
  [PASS] Zmogus negali buti sukurtas tiesiogiai
  [PASS] Zmogus* rodo i Studentas objekta
  ...

========== Rezultatai ==========
Praejo  : 63
Nepraejo: 0
Visi testai sekmingai praejo!
```

---

### Google Test (testas_gtest.cpp)

#### Nustatymas Visual Studio

1. Atsisiųsti Google Test iš [github.com/google/googletest/releases](https://github.com/google/googletest/releases)
2. Išskleisti į projekto aplanką: `googletest-1.17.0/`
3. Sukurti naują **Console App** projektą solution'e, pavadinti `Gtest`
4. Pridėti šiuos failus prie `Gtest` projekto (**Add → Existing Item**):
   - `testas_gtest.cpp`
   - `googletest-1.17.0\googletest-1.17.0\googletest\src\gtest-all.cc`
   - `googletest-1.17.0\googletest-1.17.0\googletest\src\gtest_main.cc`
5. **Properties → C/C++ → General → Additional Include Directories** pridėti:
   ```
   C:\<path_to_project>
   C:\<path_to_project>\googletest-1.17.0\googletest-1.17.0\googletest\include
   C:\<path_to_project>\googletest-1.17.0\googletest-1.17.0\googletest
   ```
6. **Properties → C/C++ → Language → C++ Language Standard** nustatyti į `ISO C++17`
7. Build ir paleisti

#### Nustatymas su CMake (automatinis)

```bash
mkdir build
cd build
cmake ..
cmake --build .
./testai        # Linux/Mac
testai.exe      # Windows
```

CMake automatiškai atsisiunčia Google Test — nereikia nieko papildomai diegti.

#### Testų rezultatai

| Testų grupė | Testų skaičius | Aprašas |
|-------------|---------------|---------|
| `ZmogusTest` | 2 | Abstraktumas, polimorfizmas |
| `StudentasTest` | 16 | Visi konstruktoriai, operatoriai, setteriai |

```
[==========] 18 tests from 2 test suites ran.
[  PASSED  ] 18 tests.
```

---

## Dokumentacija

### Peržiūrėti HTML dokumentaciją
Atidaryti `docs/html/index.html` naršyklėje.

### Generuoti dokumentaciją iš naujo
```bash
doxygen Doxyfile
```

### PDF dokumentacija
`docs/latex/refman.pdf` — taip pat pridėta prie v2.0 release GitHub'e.

---

## Klasių struktūra

```
Zmogus  (abstrakti)
│   vardas_, pavarde_
│   virtual vid(), med(), finalize(), print()
│
└── Studentas
        paz_, egz_, vid_, med_
        operator<<, operator>>
        Rule of Five (5 metodai)
```

---

## Studentas klasė — Rule of Five

| Metodas | Aprašas |
|---------|---------|
| Default konstruktorius | Sukuria tuščią studentą |
| Parametrizuotas konstruktorius | `Studentas(vardas, pavarde, paz, egz)` |
| Kopijavimo konstruktorius | Gili kopija — originalas nepasikeičia |
| Perkėlimo konstruktorius | Perima duomenis, šaltinis ištuštinamas |
| Kopijavimo priskyrimo operatorius | Saugus savęs priskyrimo atveju |
| Perkėlimo priskyrimo operatorius | Perima duomenis, šaltinis ištuštinamas |
| Destruktorius | Automatinis, virtualus |

---

## Perdengtų operatorių aprašas

### `operator<<` — išvestis

Veikia per `Zmogus::print()` virtualų metodą. Leidžia išvesti į bet kokį srautą.

```cpp
Studentas s("Jonas", "Jonaitis", {6, 7, 8}, 9);

// Į ekraną:
cout << s;
// Jonas Jonaitis 6 7 8 9 (vid: 7.40, med: 7.40)

// Į failą:
ofstream out("rezultatai.txt");
out << s;

// Per bazinės klasės rodyklę (polimorfizmas):
Zmogus* ptr = &s;
cout << *ptr;
```

### `operator>>` — įvestis

Formatas: `Vardas Pavardė paz1 paz2 ... pazN egz`  
Paskutinis skaičius visada egzaminas.

```cpp
// Iš klaviatūros:
Studentas s;
cin >> s;

// Iš eilutės:
istringstream iss("Petras Petraitis 5 6 7 8 9");
iss >> s;

// Iš failo:
ifstream in("studentai.txt");
in >> s;
```

---

## Duomenų įvestis ir išvestis

### Įvestis rankiniu būdu (pasirinkimas 1)
Vartotojas įveda vardą, pavardę, pažymius ir egzaminą per konsolę.

### Įvestis automatiškai (pasirinkimai 2 ir 3)
Programa sugeneruoja atsitiktinius pažymius arba studentus su pažymiais.

### Įvestis iš failo (pasirinkimai 5 ir 6)
Failo formatas:
```
Vardas Pavarde ND1 ND2 ND3 ND4 ND5 Egz
Jonas Jonaitis 4 6 7 8 9 10
Petras Petraitis 3 5 6 7 8 7
```

### Išvestis į ekraną
Vardas, pavardė ir galutinis balas (vidurkiu arba mediana) lentelės formatu.

### Išvestis į CSV failą
Suderinamas su Excel programa.

### Išvestis į tekstinį failą
Skirstymo rezultatai išsaugomi `vargsiukai.txt` ir `kietiakai.txt`.

---

## Skirstymo strategijos

| Strategija | Metodas | Aprašas |
|------------|---------|---------|
| 1 | `partition_copy` | Kopijuoja į du atskirus konteinerius |
| 2 | `copy_if` + `remove_if` | Kopijuoja vargšiukus, šalina iš originalo |
| 3 | `partition` / `splice` | Skirstoma vietoje — greičiausia |

---

## Benchmark rezultatai — optimizavimo flag'ai (vector, strategija 3, 1 000 000 įrašų)

| Flag | Vykdymo laikas | Exe dydis |
|------|---------------|-----------|
| `-O0` / `/Od` | ~4.2 s | ~350 KB |
| `-O1` / `/O1` | ~1.9 s | ~310 KB |
| `-O2` / `/O2` | ~1.7 s | ~315 KB |
| `-O3` | ~1.6 s | ~320 KB |

---

## Programos meniu

```
1 - ivedimas ranka
2 - generuojami pazymiai
3 - generuojami studentai ir pazymiai
4 - baigti darba
5 - nuskaityti faila (vector)
6 - failo generavimas ir benchmark
```
