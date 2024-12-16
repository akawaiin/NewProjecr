#ifndef HEXGAME_H
#define HEXGAME_H

#include <vector>
#include <queue>
#include <iostream>

using namespace std;

const int BOARD_SIZE = 11;

enum Player { NONE, RED, BLUE };

class HexGame {
public:
    HexGame();
    void displayBoard();
    void makeMove(int row, int column);
    Player getCurrentPlayer() const;
    bool checkWin();
    Player winner();

private:
    vector<vector<Player>> board;
    Player currentPlayer;
    bool firstMoveDone;
    bool isBoardFlipped;

    Player getFlippedPlayer(Player player) const;
    bool checkWinForPlayer(Player player);
};

#endif // HEXGAME_H