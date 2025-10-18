#pragma once
#include <cstdlib>

const int SIZE = 10;
const char EMPTY = '.';
const char SHIP = 'S';
const char HIT = 'X';
const char MISS = 'o';
const char MINE = 'M';
const char MINE_HIT = 'B';

inline void clearScreen() {
    system("cls");
}

