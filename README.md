# Simulator saobraćaja
Ovaj program implementira simulaciju saobraćaja korištenjem usmjerenog grafa kojim se modeluje saobraćajna mreža sastavljena od lokacija, puteva i raskrsnica.
Napisan je u C++ programskom jeziku, uz pravilnu modularizaciju i poštovanje principa objektno-orijentisanog programiranja.

Simulacija omogućava kretanje više vozila kroz mrežu, uzimajući u obzir dužine puteva, ograničenja brzine, broj vozila na putevima i raskrsnicama, te dinamičko računanje optimalne putanje.

## Funkcionalnosti
* Usmjereni graf saobraćajne mreže
  * Tri tipa čvorova:
    1. Lokacija - grad, parking i dr. (polazne/odredišne tačke)
    2. Put - segment između 2 čvora (vodi u jednom smjeru)
    3. Raskrsnica - povezuje više puteva, ima definisane ulazne i izlazne veze
  * Svaki čvor puta karakteriše:
    * dužina puta
    * maksimalna brzina
    * maksimalan broj vozila
  * Za raskrnice je moguće definisati prelazne puteve, njihovu dužinu, prosječnu brzinu i maksimalan broj vozila.
  * Omogućena je serijalizacija i deserijalizacija grafa.
 
* Model vozila
  * Svako vozilo ima definisanu prosječnu i trenutnu brzinu.
  * Kreće se od nasumične polazne tačke do nasumičnog odredišta.
  * Brzina kretanja je ograničena maksimalnom brzinom puta na kom se trenutno nalazi.
  * Izračunava se najbolja putanja (po distanci ili po vremenu).
 
* Simulacija saobraćaja
  * Odvija se u **diskretnim** vremenskim koracima.
  * U svakom koraku:
    * svako vozilo se pomjera na osnovu svoje brzine i slobodnog prostora
    * ako je naredni čvor popunjen, vozilo ostaje na trenutnoj poziciji
  * Javne metode omogućavaju:
    * izvršavanje jednog koraka simulacije (_doOneStepOfSimulation()_)
    * provjeru završetka simulacije (_isSimulationOver()_)
    * pregled trenutne pozicije vozila (_currentPositionOfVehicles(std::ostream&)_)
    * izračunavanje prosječnog vremena putovanja između lokacija (_averageTime(Graph&, Vehicle&)_).

## Primjer izvršavanja
```
 ________________________________________________________________________________
|                                                                                |
|                             Izaberite jednu opciju:                            |
|________________________________________________________________________________|
|       [1] Izvrsenje simulacije        |     [2] Pregled saobracajne mreze      |
|                                       |      u kojoj se odvija simulacija      |
|_______________________________________|________________________________________|
|          [3] Prikaz putanje           |              [4] Izlaz                 |
|                vozila                 |                                        |
|_______________________________________|________________________________________|

1

 ___________________________________________________________________
|                  Simulaciju odraditi tako da se...                |
|___________________________________________________________________|
|     [1] Minimizuje distanca     |     [2] Minimizuje vrijeme      |
|_________________________________|_________________________________|

1

 ________________________________________________________________________________
|                                                                                |
|                             Izaberite jednu opciju:                            |
|________________________________________________________________________________|
|          [1] Izvrsenje jednog         |          [2] Prikaz trenutnog          |
|           koraka simulacije           |               stanja vozila            |
|_______________________________________|________________________________________|
|        [3] Prikaz prosjecnog          |               [4] Izlaz                |
|           vremena putovanja           |                                        |
|_______________________________________|________________________________________|

2
Trenutne pozicije vozila:
Vozilo: auto1, trenutna pozicija: A
Vozilo: auto2, trenutna pozicija: D
Vozilo: auto3, trenutna pozicija: C

 ________________________________________________________________________________
|                                                                                |
|                             Izaberite jednu opciju:                            |
|________________________________________________________________________________|
|          [1] Izvrsenje jednog         |          [2] Prikaz trenutnog          |
|           koraka simulacije           |               stanja vozila            |
|_______________________________________|________________________________________|
|        [3] Prikaz prosjecnog          |               [4] Izlaz                |
|           vremena putovanja           |                                        |
|_______________________________________|________________________________________|

1

 ________________________________________________________________________________
|                                                                                |
|                             Izaberite jednu opciju:                            |
|________________________________________________________________________________|
|          [1] Izvrsenje jednog         |          [2] Prikaz trenutnog          |
|           koraka simulacije           |               stanja vozila            |
|_______________________________________|________________________________________|
|        [3] Prikaz prosjecnog          |               [4] Izlaz                |
|           vremena putovanja           |                                        |
|_______________________________________|________________________________________|

2
Trenutne pozicije vozila:
Vozilo: auto1, trenutna pozicija: Put od lokacije A
Vozilo: auto2, trenutna pozicija: Put od lokacije D
Vozilo: auto3, trenutna pozicija: Put od lokacije C

 ________________________________________________________________________________
|                                                                                |
|                             Izaberite jednu opciju:                            |
|________________________________________________________________________________|
|          [1] Izvrsenje jednog         |          [2] Prikaz trenutnog          |
|           koraka simulacije           |               stanja vozila            |
|_______________________________________|________________________________________|
|        [3] Prikaz prosjecnog          |               [4] Izlaz                |
|           vremena putovanja           |                                        |
|_______________________________________|________________________________________|

1

 ________________________________________________________________________________
|                                                                                |
|                             Izaberite jednu opciju:                            |
|________________________________________________________________________________|
|          [1] Izvrsenje jednog         |          [2] Prikaz trenutnog          |
|           koraka simulacije           |               stanja vozila            |
|_______________________________________|________________________________________|
|        [3] Prikaz prosjecnog          |               [4] Izlaz                |
|           vremena putovanja           |                                        |
|_______________________________________|________________________________________|

2
Trenutne pozicije vozila:
Vozilo: auto1, trenutna pozicija: I13
Vozilo: auto2, trenutna pozicija: I14
Vozilo: auto3, trenutna pozicija: I13

 ________________________________________________________________________________
|                                                                                |
|                             Izaberite jednu opciju:                            |
|________________________________________________________________________________|
|          [1] Izvrsenje jednog         |          [2] Prikaz trenutnog          |
|           koraka simulacije           |               stanja vozila            |
|_______________________________________|________________________________________|
|        [3] Prikaz prosjecnog          |               [4] Izlaz                |
|           vremena putovanja           |                                        |
|_______________________________________|________________________________________|

1

 ________________________________________________________________________________
|                                                                                |
|                             Izaberite jednu opciju:                            |
|________________________________________________________________________________|
|          [1] Izvrsenje jednog         |          [2] Prikaz trenutnog          |
|           koraka simulacije           |               stanja vozila            |
|_______________________________________|________________________________________|
|        [3] Prikaz prosjecnog          |               [4] Izlaz                |
|           vremena putovanja           |                                        |
|_______________________________________|________________________________________|

2
Trenutne pozicije vozila:
Vozilo: auto1, trenutna pozicija: I13
Vozilo: auto2, trenutna pozicija: I14
Vozilo: auto3, trenutna pozicija: I13

 ________________________________________________________________________________
|                                                                                |
|                             Izaberite jednu opciju:                            |
|________________________________________________________________________________|
|          [1] Izvrsenje jednog         |          [2] Prikaz trenutnog          |
|           koraka simulacije           |               stanja vozila            |
|_______________________________________|________________________________________|
|        [3] Prikaz prosjecnog          |               [4] Izlaz                |
|           vremena putovanja           |                                        |
|_______________________________________|________________________________________|

1

 ________________________________________________________________________________
|                                                                                |
|                             Izaberite jednu opciju:                            |
|________________________________________________________________________________|
|          [1] Izvrsenje jednog         |          [2] Prikaz trenutnog          |
|           koraka simulacije           |               stanja vozila            |
|_______________________________________|________________________________________|
|        [3] Prikaz prosjecnog          |               [4] Izlaz                |
|           vremena putovanja           |                                        |
|_______________________________________|________________________________________|

2
Trenutne pozicije vozila:
Vozilo: auto1, trenutna pozicija: Put ka lokaciji C
Vozilo: auto2, trenutna pozicija: Put izmedju raskrsnica
Vozilo: auto3, trenutna pozicija: Put ka lokaciji B

 ________________________________________________________________________________
|                                                                                |
|                             Izaberite jednu opciju:                            |
|________________________________________________________________________________|
|          [1] Izvrsenje jednog         |          [2] Prikaz trenutnog          |
|           koraka simulacije           |               stanja vozila            |
|_______________________________________|________________________________________|
|        [3] Prikaz prosjecnog          |               [4] Izlaz                |
|           vremena putovanja           |                                        |
|_______________________________________|________________________________________|

1

 ________________________________________________________________________________
|                                                                                |
|                             Izaberite jednu opciju:                            |
|________________________________________________________________________________|
|          [1] Izvrsenje jednog         |          [2] Prikaz trenutnog          |
|           koraka simulacije           |               stanja vozila            |
|_______________________________________|________________________________________|
|        [3] Prikaz prosjecnog          |               [4] Izlaz                |
|           vremena putovanja           |                                        |
|_______________________________________|________________________________________|

2
Trenutne pozicije vozila:
Vozilo: auto1, trenutna pozicija: C
Vozilo: auto2, trenutna pozicija: I13
Vozilo: auto3, trenutna pozicija: B

 ________________________________________________________________________________
|                                                                                |
|                             Izaberite jednu opciju:                            |
|________________________________________________________________________________|
|          [1] Izvrsenje jednog         |          [2] Prikaz trenutnog          |
|           koraka simulacije           |               stanja vozila            |
|_______________________________________|________________________________________|
|        [3] Prikaz prosjecnog          |               [4] Izlaz                |
|           vremena putovanja           |                                        |
|_______________________________________|________________________________________|

1

 ________________________________________________________________________________
|                                                                                |
|                             Izaberite jednu opciju:                            |
|________________________________________________________________________________|
|          [1] Izvrsenje jednog         |          [2] Prikaz trenutnog          |
|           koraka simulacije           |               stanja vozila            |
|_______________________________________|________________________________________|
|        [3] Prikaz prosjecnog          |               [4] Izlaz                |
|           vremena putovanja           |                                        |
|_______________________________________|________________________________________|

2
Trenutne pozicije vozila:
Vozilo: auto1, trenutna pozicija: C [Simulacija zavrsena za vozilo auto1]
Vozilo: auto2, trenutna pozicija: Put ka lokaciji C
Vozilo: auto3, trenutna pozicija: B [Simulacija zavrsena za vozilo auto3]

 ________________________________________________________________________________
|                                                                                |
|                             Izaberite jednu opciju:                            |
|________________________________________________________________________________|
|          [1] Izvrsenje jednog         |          [2] Prikaz trenutnog          |
|           koraka simulacije           |               stanja vozila            |
|_______________________________________|________________________________________|
|        [3] Prikaz prosjecnog          |               [4] Izlaz                |
|           vremena putovanja           |                                        |
|_______________________________________|________________________________________|

1

 ________________________________________________________________________________
|                                                                                |
|                             Izaberite jednu opciju:                            |
|________________________________________________________________________________|
|          [1] Izvrsenje jednog         |          [2] Prikaz trenutnog          |
|           koraka simulacije           |               stanja vozila            |
|_______________________________________|________________________________________|
|        [3] Prikaz prosjecnog          |               [4] Izlaz                |
|           vremena putovanja           |                                        |
|_______________________________________|________________________________________|

2
Trenutne pozicije vozila:
Vozilo: auto1, trenutna pozicija: C [Simulacija zavrsena za vozilo auto1]
Vozilo: auto2, trenutna pozicija: C
Vozilo: auto3, trenutna pozicija: B [Simulacija zavrsena za vozilo auto3]

 ________________________________________________________________________________
|                                                                                |
|                             Izaberite jednu opciju:                            |
|________________________________________________________________________________|
|          [1] Izvrsenje jednog         |          [2] Prikaz trenutnog          |
|           koraka simulacije           |               stanja vozila            |
|_______________________________________|________________________________________|
|        [3] Prikaz prosjecnog          |               [4] Izlaz                |
|           vremena putovanja           |                                        |
|_______________________________________|________________________________________|

1

 ________________________________________________________________________________
|                                                                                |
|                             Izaberite jednu opciju:                            |
|________________________________________________________________________________|
|          [1] Izvrsenje jednog         |          [2] Prikaz trenutnog          |
|           koraka simulacije           |               stanja vozila            |
|_______________________________________|________________________________________|
|        [3] Prikaz prosjecnog          |               [4] Izlaz                |
|           vremena putovanja           |                                        |
|_______________________________________|________________________________________|

2
Trenutne pozicije vozila:
Vozilo: auto1, trenutna pozicija: C [Simulacija zavrsena za vozilo auto1]
Vozilo: auto2, trenutna pozicija: C [Simulacija zavrsena za vozilo auto2]
Vozilo: auto3, trenutna pozicija: B [Simulacija zavrsena za vozilo auto3]

 ________________________________________________________________________________
|                                                                                |
|                             Izaberite jednu opciju:                            |
|________________________________________________________________________________|
|          [1] Izvrsenje jednog         |          [2] Prikaz trenutnog          |
|           koraka simulacije           |               stanja vozila            |
|_______________________________________|________________________________________|
|        [3] Prikaz prosjecnog          |               [4] Izlaz                |
|           vremena putovanja           |                                        |
|_______________________________________|________________________________________|

3
Prosjecno vrijeme putovanja od A do C iznosi: 22.4
Prosjecno vrijeme putovanja od D do C iznosi: 30.2683
Prosjecno vrijeme putovanja od C do B iznosi: 21.9879

 ________________________________________________________________________________
|                                                                                |
|                             Izaberite jednu opciju:                            |
|________________________________________________________________________________|
|          [1] Izvrsenje jednog         |          [2] Prikaz trenutnog          |
|           koraka simulacije           |               stanja vozila            |
|_______________________________________|________________________________________|
|        [3] Prikaz prosjecnog          |               [4] Izlaz                |
|           vremena putovanja           |                                        |
|_______________________________________|________________________________________|

4

 ________________________________________________________________________________
|                                                                                |
|                             Izaberite jednu opciju:                            |
|________________________________________________________________________________|
|       [1] Izvrsenje simulacije        |     [2] Pregled saobracajne mreze      |
|                                       |      u kojoj se odvija simulacija      |
|_______________________________________|________________________________________|
|          [3] Prikaz putanje           |              [4] Izlaz                 |
|                vozila                 |                                        |
|_______________________________________|________________________________________|

2

_____________________________________________________
inf      inf      inf      inf      320.00   inf
inf      inf      inf      inf      inf      220.00
inf      inf      inf      inf      400.00   inf
inf      inf      inf      inf      inf      620.00
340.00   575.00   456.00   430.00   inf      inf
inf      inf      inf      inf      150.00   inf
_____________________________________________________
_____________________________________________________
inf      2.00     2.00     2.00
2.00     2.00     2.00     2.00
2.00     2.00     2.00     2.00
_____________________________________________________
3.00
3.00
_____________________________________________________

 ________________________________________________________________________________
|                                                                                |
|                             Izaberite jednu opciju:                            |
|________________________________________________________________________________|
|       [1] Izvrsenje simulacije        |     [2] Pregled saobracajne mreze      |
|                                       |      u kojoj se odvija simulacija      |
|_______________________________________|________________________________________|
|          [3] Prikaz putanje           |              [4] Izlaz                 |
|                vozila                 |                                        |
|_______________________________________|________________________________________|

3

__________________________________________________________________________________________________________________________________________________________________________________
Vozilo auto1:
[po distanci]:
A (0.00,0.00) -> Put od lokacije A (0.00,0.00) -> I13 (320.00,6.40) -> Put ka lokaciji C (322.00,6.44) -> C (778.00,15.56)
[po vremenu]:
A (0.00,0.00) -> Put od lokacije A (0.00,0.00) -> I13 (320.00,6.40) -> Put ka lokaciji C (322.00,6.44) -> C (778.00,15.56)
__________________________________________________________________________________________________________________________________________________________________________________
Vozilo auto2:
[po distanci]:
D (0.00,0.00) -> Put od lokacije D (0.00,0.00) -> I14 (620.00,10.33) -> Put izmedju raskrsnica (623.00,10.39) -> I13 (773.00,13.39) -> Put ka lokaciji C (775.00,13.43) -> C (1231.00,22.55)       
[po vremenu]:
D (0.00,0.00) -> Put od lokacije D (0.00,0.00) -> I14 (620.00,10.33) -> Put izmedju raskrsnica (623.00,10.39) -> I13 (773.00,13.39) -> Put ka lokaciji C (775.00,13.43) -> C (1231.00,22.55)       
__________________________________________________________________________________________________________________________________________________________________________________
Vozilo auto3:
[po distanci]:
C (0.00,0.00) -> Put od lokacije C (0.00,0.00) -> I13 (400.00,8.00) -> Put ka lokaciji B (402.00,8.04) -> B (977.00,15.23)
[po vremenu]:
C (0.00,0.00) -> Put od lokacije C (0.00,0.00) -> I13 (400.00,8.00) -> Put ka lokaciji B (402.00,8.04) -> B (977.00,15.23)
__________________________________________________________________________________________________________________________________________________________________________________

 ________________________________________________________________________________
|                                                                                |
|                             Izaberite jednu opciju:                            |
|________________________________________________________________________________|
|       [1] Izvrsenje simulacije        |     [2] Pregled saobracajne mreze      |
|                                       |      u kojoj se odvija simulacija      |
|_______________________________________|________________________________________|
|          [3] Prikaz putanje           |              [4] Izlaz                 |
|                vozila                 |                                        |
|_______________________________________|________________________________________|

4
```

# Autorska prava
© 2025 Aleksandra Vučićević
