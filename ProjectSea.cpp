#include <iostream>
#include <ctime>
#include <limits>
#include "Player.h"
#include "Header.h"
using namespace std;

int main() {
    setlocale(LC_ALL, "ru");
    srand(static_cast<unsigned>(time(0)));

    int mode;
    while (true) {
        cout << "Выбор режима:\n1) Играть против ИИ\n2) Игра вдвоем\nВыберите (1 или 2): ";
        if (cin >> mode && (mode == 1 || mode == 2)) break;
        cout << "Ошибка! Введите 1 или 2.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    Player A("Команда A");
    Player B(mode == 1 ? "ИИ" : "Команда B", mode == 1);

    A.setupShips();
    B.setupShips();

    bool aTurn = true;
    while (true) {
        clearScreen();

        cout << "------ Поля ------\n";
        cout << "Поле A:\n";
        A.board.display(true);
        cout << "\nПоле B:\n";
        B.board.display(true);

        bool again = aTurn ? A.takeTurn(B) : B.takeTurn(A);

        if (!again) aTurn = !aTurn;

        if (B.board.allSunk()) { cout << "\nКоманда A победила!\n"; break; }
        if (A.board.allSunk()) { cout << "\n" << B.name << " победил!\n"; break; }

        cout << "\nНажмите Enter для продолжения...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
    }

    return 0;
}
