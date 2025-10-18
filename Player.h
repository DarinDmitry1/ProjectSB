#pragma once
#include <string>
#include "Board.h"

class Player {
public:
    std::string name;
    Board board;
    bool usedAir;
    bool isAI;

    Player(std::string n, bool ai = false);
    void setupShips();
    bool takeTurn(Player& opponent);
};
