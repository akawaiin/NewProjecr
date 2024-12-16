#include <iostream>
#include "HexGame.h"

using namespace std;

void play(HexGame& game) {
    int row, column;

    while (true) {
        game.displayBoard();
        cout << "Current Player: " << (game.getCurrentPlayer() == BLUE ? "Blue" : "Red") << endl;

        cout << "Enter your move (row and column): ";
        cin >> row >> column;

        game.makeMove(row, column);

        if (game.checkWin()) {
            game.displayBoard();
            cout << "Congratulations! " << (game.winner() == RED ? "Red" : "Blue") << " Wins!" << endl;
            break;
        }
    }
}

int main() {
    HexGame game;
    cout << "Welcome to Hex Game!" << endl;
    play(game);
    return 0;
}
//Доп: сделать чтоб открывалось в консоли, а не в файле. Выводит ошибку если координаты не те