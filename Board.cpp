#include "Board.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

Board::Board() : grid(SIZE, vector<char>(SIZE, EMPTY)) {}

bool Ship::isSunk(const vector<vector<char>>& b) {
    for (auto& p : parts) if (b[p.x][p.y] != HIT) return false;
    return true;
}

void Board::clearAll() {
    ships.clear();
    for (auto& row : grid)
        fill(row.begin(), row.end(), EMPTY);
}

void Board::display(bool hide, bool) {
    cout << "  ";
    for (int j = 0; j < SIZE; j++) cout << j << " ";
    cout << endl;
    for (int i = 0; i < SIZE; i++) {
        cout << i << " ";
        for (int j = 0; j < SIZE; j++) {
            char c = grid[i][j];
            if (hide) {
                if (c == SHIP || c == MINE) {
                    cout << EMPTY << " ";
                }
                else {
                    cout << c << " ";
                }
            }
            else {
                cout << c << " ";
            }
        }
        cout << endl;
    }
}

bool Board::validPlace(int x, int y, int len, bool horiz) {
    int dx = horiz ? 0 : 1, dy = horiz ? 1 : 0;
    for (int i = -1; i <= len; i++) {
        for (int j = -1; j <= 1; j++) {
            int xi = x + dx * i + dy * j;
            int yj = y + dy * i + dx * j;
            if (xi >= 0 && xi < SIZE && yj >= 0 && yj < SIZE && grid[xi][yj] == SHIP)
                return false;
        }
    }
    for (int i = 0; i < len; i++) {
        int xi = x + dx * i, yj = y + dy * i;
        if (xi < 0 || xi >= SIZE || yj < 0 || yj >= SIZE || grid[xi][yj] != EMPTY)
            return false;
    }
    return true;
}

void Board::placeShip(int x, int y, int len, bool horiz) {
    Ship s;
    for (int i = 0; i < len; i++) {
        int xi = x + (horiz ? 0 : i);
        int yj = y + (horiz ? i : 0);
        grid[xi][yj] = SHIP;
        s.parts.push_back({ xi, yj });
    }
    ships.push_back(s);
}

void Board::placeMines(int count) {
    int placed = 0;
    while (placed < count) {
        int x = rand() % SIZE;
        int y = rand() % SIZE;
        if (grid[x][y] == EMPTY) {
            grid[x][y] = MINE;
            placed++;
        }
    }
}

void Board::randomShipsAndMines() {
    clearAll();
    vector<int> sizes = { 4, 3, 3, 2, 2, 2, 1, 1, 1, 1 };
    for (int len : sizes) {
        bool placed = false;
        while (!placed) {
            int x = rand() % SIZE, y = rand() % SIZE;
            bool horiz = rand() % 2;
            if (validPlace(x, y, len, horiz)) {
                placeShip(x, y, len, horiz);
                placed = true;
            }
        }
    }
    placeMines(5);
}

bool Board::receiveShot(int x, int y, Board& shooterBoard) {
    char& cell = grid[x][y];
    if (cell == SHIP) {
        cell = HIT;
        cout << "Попадание!\n";
        return true;
    }
    else if (cell == EMPTY) {
        cell = MISS;
        cout << "Мимо.\n";
        return false;
    }
    else if (cell == MINE) {
        cout << "Мина активирована!\n";
        cell = MINE_HIT;
        char& shooterCell = shooterBoard.grid[x][y];
        if (shooterCell == SHIP) {
            shooterCell = HIT;
            cout << "Урон по своему кораблю!\n";
        }
        else if (shooterCell == EMPTY) {
            shooterCell = MISS;
            cout << "Обратный урон по пустой клетке.\n";
        }
        return false;
    }
    else if (cell == HIT || cell == MISS || cell == MINE_HIT) {
        cout << "Сюда уже стреляли.\n";
        return false;
    }
    return false;
}

void Board::airStrike(int x, int y) {
    static const vector<Coordinate> pattern = {
        {0,0},{1,0},{-1,0},{0,1},{0,-1}
    };
    cout << "Атака самолёта!\n";
    for (auto& d : pattern) {
        int xi = x + d.x, yj = y + d.y;
        if (xi >= 0 && xi < SIZE && yj >= 0 && yj < SIZE) {
            char& cell = grid[xi][yj];
            if (cell == SHIP) {
                cell = HIT;
                cout << "Попадание!\n";
            }
            else if (cell == EMPTY) {
                cell = MISS;
            }
        }
    }
}

bool Board::allSunk() {
    for (auto& s : ships) if (!s.isSunk(grid)) return false;
    return true;
}
