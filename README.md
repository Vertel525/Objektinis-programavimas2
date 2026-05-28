# Studentų Registras v1.0

Programa skirta studentų duomenų apdorojimui ir analizavimui. Vartotojas gali:
- įvesti studentų duomenis ranka;
- automatiškai sugeneruoti pažymius arba studentų įrašus;
- nuskaityti studentų duomenis iš failo;
- sugeneruoti testinius failus;
- atlikti skirtingų konteinerių ir studentų skirstymo strategijų veikimo spartos tyrimą.

Programoje realizuotos trys studentų skirstymo strategijos, kurių veikimo laikas lyginamas su skirtingo dydžio duomenų failais naudojant `vector`, `list` ir `deque` konteinerius.

---

## Versijų istorija

| Versija | Aprašymas |
|---------|-----------|
| v0.1 | Pradinis veikiantis variantas — rankinis įvedimas, skaičiavimas, išvedimas |
| v0.2 | Nuskaitymas iš failo, rūšiavimas, skirstymas į dvi grupes |
| v0.3 | Failų generavimas, testavimas su dideliais duomenų kiekiais |
| v0.4 | Optimizuotas skirstymas, patobulintas išvedimas į failą |
| v1.0 | Pridėtas `std::list` ir `std::deque` palaikymas, 3 skirstymo strategijos, greičio tyrimas |

---

## Įdiegimo instrukcija

### Reikalavimai
- C++17 palaikantis kompiliatorius (GCC 8+, MSVC 2019+, Clang 7+)
- CMake 3.16+

### Kompiliavimas su CMake

```bash
git clone https://github.com/Vertel525/Objektinis-programavimas
cd Objektinis-programavimas
mkdir build && cd build
cmake ..
cmake --build . --config Release
```

### Paleidimas

```bash
# Windows
main1.exe

# Linux / macOS
./main1
```

---

## Naudojimosi instrukcija

Paleidus programą pateikiamas meniu:

```
1 - ivedimas ranka
2 - generuojami pazymiai
3 - generuojami studentai ir pazymiai
4 - baigti darba
5 - nuskaityti faila (vector)
6 - failo generavimas ir benchmark
```

### Režimas 6 — Benchmark

```
1 - Generuoti failus      (sukuria 1000.txt ... 10000000.txt)
2 - Paleisti benchmark    (matuoja laiką visiems konteineriams ir strategijoms)
```

Įvedus `2`, programa paprašys failo pavadinimo ir išmatuos nuskaitymo, rūšiavimo ir visų 3 skirstymo strategijų laiką kiekvienam konteineriui.

---

## Testavimo sistemos parametrai

| Komponentas | Specifikacija |
|-------------|---------------|
| CPU | Intel Core i7-13650HX |
| GPU | NVIDIA RTX 5060 Mobile |
| RAM | 24 GB |
| Saugykla | SSD |
| OS | Windows |

---

## Tyrimo rezultatai

Visi matavimai atlikti su iš anksto sugeneruotais failais (1000, 10000, 100000, 1000000 įrašų).
Laikas nurodytas sekundėmis.

---

## Konteinerių greičio tyrimas

### Nuskaitymas (skaityti)

| Įrašų sk. | vector | list | deque |
|-----------|--------|------|-------|
| 1 000 | 0.0942052 s | 0.0493538 s | 0.0484189 s |
| 10 000 | 0.528222 s | 0.495995 s | 0.491544 s |
| 100 000 | 5.0388 s | 8.17166 s | 5.07298 s |
| 1 000 000 | 68.3341 s | 75.9146 s | 72.9164 s |

### Rūšiavimas (rikiuoti)

| Įrašų sk. | vector | list | deque |
|-----------|--------|------|-------|
| 1 000 | 0.0276871 s | 0.0005057 s | 0.032269 s |
| 10 000 | 0.241124 s | 0.0070069 s | 0.262496 s |
| 100 000 | 2.39571 s | 0.168299 s | 2.55142 s |
| 1 000 000 | 31.3452 s | 2.68962 s | 34.5294 s |

---

## Skirstymo strategijų tyrimas

### 1 strategija — du nauji konteineriai (partition_copy)

Studentas lieka bendrame konteineryje **ir** patenka į vieną iš dviejų naujų (`vargšiukai` ir `kietiakai`).
Neefektyvu atminties atžvilgiu — duomenys dubliuojami, tačiau operacija greita.

| Įrašų sk. | vector | list | deque |
|-----------|--------|------|-------|
| 1 000 | 0.0135152 s | 0.0038836 s | 0.0045774 s |
| 10 000 | 0.141924 s | 0.0406719 s | 0.0408574 s |
| 100 000 | 1.77447 s | 0.555841 s | 0.410997 s |
| 1 000 000 | 17.2134 s | 5.53756 s | 5.86204 s |

### 2 strategija — vienas naujas konteineris (copy_if + remove_if)

Vargšiukai perkeliami į naują konteinerį ir **ištrinami** iš bendro.
Efektyviau atminties atžvilgiu, tačiau dažni trynimai stipriai lėtina `list`.

| Įrašų sk. | vector | list | deque |
|-----------|--------|------|-------|
| 1 000 | 0.0028835 s | 0.003627 s | 0.0037777 s |
| 10 000 | 0.0296754 s | 0.0363959 s | 0.038055 s |
| 100 000 | 0.461055 s | 0.592309 s | 0.372462 s |
| 1 000 000 | 3.97545 s | 5.09716 s | 5.8258 s |

### 3 strategija — optimizuota (partition / splice)

- `vector` / `deque`: `std::partition` — vienas praėjimas, jokio papildomo kopijavimo
- `list`: `splice` — nulinės kopijos, tik rodyklių perstatymas

| Įrašų sk. | vector | list | deque |
|-----------|--------|------|-------|
| 1 000 | 0.0038043 s | 0.0011601 s | 0.0042473 s |
| 10 000 | 0.0375445 s | 0.0119693 s | 0.0446 s |
| 100 000 | 0.534876 s | 0.117763 s | 0.431631 s |
| 1 000 000 | 3.71992 s | 1.1785 s | 5.81549 s |

---

## Išvados

### Konteineriai

- **`std::vector`** — greičiausias nuskaitymui dėl gretimos atminties ir `reserve()`. Rūšiavimas su `std::sort` labai greitas. Skirstymas su `std::partition` efektyvus, tačiau 1 strategija lėta dėl didelio kopijavimo kiekio.
- **`std::list`** — lėčiausias nuskaitymui (nėra `reserve()`, daug atminties alokacijų). Rūšiavimas su `list::sort` paradoksaliai greičiausias iš visų — nes naudoja `merge sort` be elementų kopijavimo. Skirstymas su `splice` (3 strategija) — absoliučiai greičiausias iš visų konteinerių.
- **`std::deque`** — tarpinis variantas. Nuskaitymas panašus į `vector`, rūšiavimas šiek tiek lėtesnis. Skirstymas 2 strategijoje lėčiausias dėl neefektyvių vidinių blokų.

### Strategijos

- **1 strategija** — lėčiausia dėl atminties dubliavimo (studentas egzistuoja dviejuose konteineriuose vienu metu).
- **2 strategija** — vidutinė. `vector` atveju greičiau nei 1 strategija, tačiau `list` atveju labai lėta dėl dažnų trynimų.
- **3 strategija** — greičiausia visais atvejais. `std::partition` `vector`/`deque` atveju ir `splice` `list` atveju leidžia išvengti nereikalingo kopijavimo.

---

## Failo struktūra

```
.
├── main1.cpp          # Pagrindinė programa
├── funkcijos1.h       # Funkcijų deklaracijos
├── funkcijos1.cpp     # Interaktyvios funkcijos (inranka, outputas ir kt.)
├── funkcijos1.tpp     # Šabloninės funkcijos (skaityti, rikiuoti, skirstyti...)
├── studentai1.h       # Studentas struktūra
├── CMake.txt          # Build failas
└── README.md
```
