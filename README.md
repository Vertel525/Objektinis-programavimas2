# Studentų Pažymių Skaičiuoklė

C++ programa skirta studentų pažymių valdymui. Programa leidžia įvesti studentus rankiniu būdu, generuoti atsitiktinius duomenis arba nuskaityti iš failo, tada rikiuoti ir skirstyti studentus pagal vidurkį.

---

## Versijų istorija

| Versija | Aprašas |
|---------|---------|
| v1.0 | Pradinė realizacija su `struct Studentas`, vector/list/deque konteineriai, 3 skirstymo strategijos |
| v1.1 | `struct` pakeista į `class`, pridėti konstruktoriai, destruktorius, getter/setter metodai |
| v1.2 | Pridėti `operator<<` ir `operator>>`, pilnas Rule of Five, testų failas |
| v1.3 | Sukurti abstrakčią klasę, kurioje negalima kurti žmogaus tipo objektų, derived klasė, testai|

---

## Failų struktūra

```
├── studentai1.h       # Studentas klasė
├── funkcijos1.h       # Funkcijų deklaracijos
├── funkcijos1.tpp     # Template funkcijų realizacijos
├── funkcijos1.cpp     # Įvesties/išvesties funkcijų realizacijos
├── main1.cpp          # Pagrindinis failas
├── testas.cpp         # Vienetų testai
└── zmogus.h           # Zmogus klasė
```

---

## Studentas klasė

### Privačios duomenų narės

| Narė | Tipas | Aprašas |
|------|-------|---------|
| `vardas_` | `string` | Studento vardas |
| `pavarde_` | `string` | Studento pavardė |
| `paz_` | `vector<int>` | Namų darbų pažymiai |
| `egz_` | `int` | Egzamino pažymys |
| `vid_` | `double` | Galutinis balas (vidurkis) |
| `med_` | `double` | Galutinis balas (mediana) |

---

## Rule of Five

Visi penki metodai yra pilnai realizuoti `studentai1.h` faile:

| Metodas | Aprašas |
|---------|---------|
| Kopijuojantis konstruktorius | Gili kopija — originalas nepasikeičia |
| Perkeliantis konstruktorius | Perima duomenis iš laikino objekto, šaltinis ištuštinamas |
| Kopijuojantis priskyrimo operatorius | Kopijuoja duomenis, saugus savęs priskyrimo atveju |
| Perkeliantis priskyrimo operatorius | Perima duomenis, šaltinis ištuštinamas |
| Destruktorius | Atlaisvina atmintį, kviečiamas automatiškai |

---

## Perdengtų operatorių aprašas

### `operator<<` — išvestis

Leidžia išvesti studento duomenis į bet kokį išvesties srautą: `cout`, failą, `ostringstream`.

### `operator>>` — įvestis

Leidžia nuskaityti studento duomenis iš bet kokio įvesties srauto: `cin`, failo, `istringstream`.

---

## Duomenų įvestis ir išvestis

### Įvestis rankiniu būdu (pasirinkimas 1)
Vartotojas įveda vardą, pavardę, pažymius ir egzaminą per konsolę.

### Įvestis automatiškai (pasirinkimai 2 ir 3)
Programa pati sugeneruoja atsitiktinius pažymius arba atsitiktinius studentus su pažymiais.

### Įvestis iš failo (pasirinkimas 5 ir 6)
Nuskaitoma iš `.txt` failo. Failo formatas:
```
Vardas Pavarde ND1 ND2 ND3 ND4 ND5 Egz
Vardas1 Pavarde1 4 6 7 8 9 10
Vardas2 Pavarde2 3 5 6 7 8 7
```

### Išvestis į ekraną
Rodo vardą, pavardę ir galutinį balą (vidurkį arba medianą) lentelės formatu.

### Išvestis į CSV failą
Išsaugo rezultatus CSV formatu, kurį galima atidaryti Excel programoje.

### Išvestis į tekstinį failą
Skirstymo rezultatai (vargšiukai / kietiakai) išsaugomi atskiruose failuose `vargsiukai.txt` ir `kietiakai.txt`.

---

## Skirstymo strategijos

| Strategija | Aprašas |
|------------|---------|
| `skirstyti1` | `partition_copy` — kopijuoja į du atskirus konteinerius |
| `skirstyti2` | `copy_if` + `remove_if` — kopijuoja vargšiukus, šalina iš originalo |
| `skirstyti3` | `partition` arba `splice` (list) — skirstoma vietoje |

---

## Kompiliavimas

```bash
# Pagrindinis programas
g++ -std=c++17 -O2 -o programa main2.cpp funkcijos2.cpp

# Testai
g++ -std=c++17 -o testas testas.cpp
./testas
```

---

## Testų rezultatai

<img width="1639" height="1420" alt="Screenshot 2026-05-29 050106" src="https://github.com/user-attachments/assets/1fe3a59d-ca5d-4ae6-9fa8-2510b3f99c3e" />
<img width="1554" height="1405" alt="Screenshot 2026-05-29 050135" src="https://github.com/user-attachments/assets/d98cebc0-835d-4aa1-a1c4-e0c6a823cca0" />
<img width="1741" height="1431" alt="Screenshot 2026-05-29 050123" src="https://github.com/user-attachments/assets/975cceda-861a-40ad-9df1-302afd73e9cd" />

