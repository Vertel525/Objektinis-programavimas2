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

## v1.1 rezultatai

Šioje versijoje (v1.1) programa perrašyta naudojant `class` vietoje `struct`. 
Atliktas tyrimas siekiant palyginti šių dviejų realizacijų efektyvumą apdorojant studentų duomenis.

Testavimas atliktas:
- naudojant **vector konteinerį**
- taikant **3 skirstymo strategiją (partition)**
- su skirtingais kompiliatoriaus optimizavimo lygiais: **-O1, -O2, -O3**

# Tyrimo rezultatai

100000 studentų

| Optimizacija | Laikas (class) | Laikas (struct) | Failo dydis (class) | Failo dydis (struct) |
|--------------|----------------|-----------------|---------------------|----------------------|
| -O1          |  0.259675 s    | 0.246076 s      | 326 KB              |     339 KB           |
| -O2          |  0.249686 s    | 0.244191 s      | 309 KB              |     322 KB           |
| -O3          |  0.249245 s    | 0.247485 s      | 341 KB              |     323 KB           |
------------------------------------------------------------------------------------------------

1000000 studentų

| Optimizacija | Laikas (class) | Laikas (struct) | Failo dydis (class) | Failo dydis (struct) |
|--------------|----------------|-----------------|---------------------|----------------------|
| -O1          | 1.30572 s      | 1.23554 s       | 326 KB              |  339 KB              |
| -O2          | 1.25852 s      | 1.20096 s       | 309 KB              |  322 KB              |
| -O3          | 1.25299 s      | 1.20199 s       | 341 KB              |  323 KB              |
------------------------------------------------------------------------------------------------
