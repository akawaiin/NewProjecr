#include <iostream>
#include "HexGame.h"

using namespace std;

int main() {
    HexGame game; // Создание экземпляра игры
    int row, col;

    cout << "Welcome to Hex Game!" << endl;

    while (true) {
        game.displayBoard();
        cout << "Current Player: " << (game.getCurrentPlayer() == BLUE ? "Blue" : "Red") << endl;

        cout << "Enter your move (row and column): ";
        cin >> row >> col;

        game.makeMove(row, col);

        if (game.checkWin()) {
            game.displayBoard();
            cout << "Congratulations! " << (game.winner() == RED ? "Red" : "Blue") << " Wins!" << endl;
            break;
        }
    }

    return 0;
}
//Доп: сделать чтоб открывалось в консоли, а не в файле. Выводит ошибку если координаты не те