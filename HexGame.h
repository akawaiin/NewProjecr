#ifndef HEXGAME_H
#define HEXGAME_H

#include <vector>
#include <queue>
#include <iostream>

using namespace std;

// Размер игрового поля
const int BOARD_SIZE = 11;

// Перечисление для обозначения игроков
enum Player { NONE, RED, BLUE };

class HexGame {
public:
    HexGame();

    // Метод для отображения игрового поля
    void displayBoard();

    // Метод для выполнения ходов игроков
    void makeMove(int row, int col);

    Player getCurrentPlayer() const;

    bool checkWin();

    Player winner();

private:
    vector<vector<Player>> board; // Игровое поле, текущее состояние
    Player currentPlayer;
    bool firstMoveDone;
    bool isBoardFlipped;

    Player getFlippedPlayer(Player player) const;

    // Метод для проверки победы для конкретного игрока
    bool checkWinForPlayer(Player player);
};

#endif // HEXGAME_H