#pragma once
#include <vector>
#include <iostream>
#include "Header.h"

struct Coordinate {
    int x, y;
};

class Ship {
public:
    std::vector<Coordinate> parts;
    bool isSunk(const std::vector<std::vector<char>>& b);
};

class Board {
public:
    std::vector<std::vector<char>> grid;
    std::vector<Ship> ships;

    Board();
    void clearAll();
    void display(bool hide = false, bool showMines = false);
    bool validPlace(int x, int y, int len, bool horiz);
    void placeShip(int x, int y, int len, bool horiz);
    void placeMines(int count);
    void randomShipsAndMines();
    bool receiveShot(int x, int y, Board& shooterBoard);
    void airStrike(int x, int y);
    bool allSunk();
};

