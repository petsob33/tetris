# Tetris (SDL2)

Jednoduchá implementace klasické hry Tetris v jazyce C s využitím knihovny SDL2 a SDL2_ttf. Projekt vznikl jako semestrální práce.

---

## Rychlý start / Quick start

Požadavky / Requirements:
- GCC nebo jiný C kompilátor
- CMake 
- SDL2 
- SDL2_ttf

Ubuntu / Debian:
```
sudo apt-get install build-essential cmake libsdl2-dev libsdl2-ttf-dev
```

Sestavení / Build:
```
mkdir build
cd build
cmake ..
make
```


Spuštění / Run:
```
./build/tetris
```

Poznámky:
- Ujistěte se, že v adresáři s hrou je font `font.ttf` (program jej otevírá v [`main`](main.c)).
- Highscore se načítají z `scores.txt` v běhovém adresáři a zapisují se tam po ukončení hry.

---

## Ovládání / Controls

- W / S — pohyb v menu
- Enter — potvrdit volbu
- Šipky vlevo / vpravo — posun tvaru
- Šipka dolů — urychlení pádu
- Space — otočení tvaru
- Esc / zavřít okno — ukončit hru

(V implementaci najdete logiku herních akcí v [`main.c`](main.c) a manipulaci s tvary v [`controller.c`](controller.c).)

---

## Struktura projektu / Project layout

- [CMakeLists.txt](CMakeLists.txt) — CMake konfigurace projektu  
- [main.c](main.c) — vstupní bod programu a smyčka hry (funkce [`main`](main.c))  
- [grafic.c](grafic.c) — vykreslování (funkce jako [`renderArr`](grafic.c), [`drawText`](grafic.c))  
- [grafic.h](grafic.h) — deklarace funkcií pro grafiku (např. `setColor`)  
- [controller.c](controller.c) — herní logika (např. [`rotateShape`](controller.c), [`moveDown`](controller.c), [`saveScore`](controller.c))  
- [controller.h](controller.h) — rozhraní herní logiky (např. `spawnShape`, `controlLine`)  
- build/ — výstupní složka vytvořená CMake (obsahuje sestavený binární soubor a soubory záloh jako [build/scores.txt](build/scores.txt))

---

## Ukládání skóre

Skóre jsou načítána a ukládána do souboru `scores.txt` v běhovém adresáři (viz [`saveScore`](controller.c) a načítání v [`main`](main.c)). Ve složce `build/` je příklad souboru [build/scores.txt](build/scores.txt).

---

## Úpravy a přispění

- Kód je jednoduchý C projekt — pro rychlé úpravy stačí změnit zdrojové soubory a znovu spustit `cmake --build build`.
- Pokud přidáte nový font, umístěte jej jako `font.ttf` do adresáře, odkud spouštíte spustitelný soubor.

---

