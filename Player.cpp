#include "Player.h"
#include "Header.h"
#include <iostream>
#include <limits>
using namespace std;

Player::Player(string n, bool ai) : name(n), isAI(ai), usedAir(false) {}

void Player::setupShips() {
    string ans;
    do {
        clearScreen();
        board.randomShipsAndMines();
        cout << name << ", расположение кораблей и мин:\n";
        board.display(false, true);
        cout << name << ", устраивает расположение? (y/n): ";
        if (isAI) {
            cout << "y (авто)\n";
            ans = "y";
        }
        else {
            cin >> ans;
        }
    } while (ans != "y" && ans != "Y");
}

bool Player::takeTurn(Player& opponent) {
    if (isAI) {
        int x, y;
        do {
            x = rand() % SIZE;
            y = rand() % SIZE;
        } while (opponent.board.grid[x][y] == HIT || opponent.board.grid[x][y] == MISS);
        cout << name << " стреляет в: " << x << " " << y << endl;
        return opponent.board.receiveShot(x, y, board);
    }

    string input;
    cout << name << ", введите X Y или 'F' для самолёта: ";
    cin >> input;

    if (input == "F" || input == "f") {
        if (usedAir) {
            cout << "Самолёт уже использован.\n";
            return takeTurn(opponent);
        }
        int x, y;
        cout << "Введите координаты центра удара (X Y): ";
        while (!(cin >> x >> y) || x < 0 || x >= SIZE || y < 0 || y >= SIZE) {
            cout << "Ошибка! Введите корректные координаты: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        usedAir = true;
        opponent.board.airStrike(x, y);
        return false;
    }

    int x, y;
    try {
        x = stoi(input);
    }
    catch (...) {
        cout << "Ошибка! Нужно вводить числа.\n";
        return takeTurn(opponent);
    }

    if (!(cin >> y)) {
        cout << "Ошибка! Нужно ввести вторую координату.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return takeTurn(opponent);
    }

    if (x < 0 || x >= SIZE || y < 0 || y >= SIZE) {
        cout << "Ошибка! Координаты должны быть от 0 до " << SIZE - 1 << ".\n";
        return takeTurn(opponent);
    }

    return opponent.board.receiveShot(x, y, board);
}
