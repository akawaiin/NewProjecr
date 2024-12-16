#include "HexGame.h"

HexGame::HexGame()
        : board(BOARD_SIZE, vector<Player>(BOARD_SIZE, NONE)),
          currentPlayer(BLUE),
          firstMoveDone(false),
          isBoardFlipped(false) {}

void HexGame::displayBoard() {
    cout << "   ";
    for (int index = 0; index < BOARD_SIZE; ++index) {
        cout << index << " ";
    }
    cout << endl;

    for (int rowIndex = 0; rowIndex < BOARD_SIZE; ++rowIndex) {
        cout << string(rowIndex, ' ') << rowIndex << " ";
        for (int columnIndex = 0; columnIndex < BOARD_SIZE; ++columnIndex) {
            Player player = isBoardFlipped ? getFlippedPlayer(board[columnIndex][rowIndex]) : board[rowIndex][columnIndex];
            if (player == RED) cout << "R ";
            else if (player == BLUE) cout << "B ";
            else cout << ". ";
        }
        cout << endl;
    }
}

void HexGame::makeMove(int row, int column) {
    if (row >= 0 && row < BOARD_SIZE && column >= 0 && column < BOARD_SIZE && board[row][column] == NONE) {
        board[row][column] = currentPlayer;

        if (!firstMoveDone) {
            firstMoveDone = true;
            char choice;
            cout << "Player " << (currentPlayer == RED ? "RED" : "BLUE") << " made the first move. Do you want to flip the board? (y/n): ";
            cin >> choice;
            if (choice == 'y' || choice == 'Y') {
                isBoardFlipped = true;
                currentPlayer = (currentPlayer == BLUE) ? RED : BLUE;
            }
            cout << endl << endl;
        }

        currentPlayer = (currentPlayer == BLUE) ? RED : BLUE;
    } else {
        cout << "Incorrect move. Try again." << endl;
    }
}

Player HexGame::getCurrentPlayer() const {
    return currentPlayer;
}

bool HexGame::checkWin() {
    return checkWinForPlayer(RED) || checkWinForPlayer(BLUE);
}

Player HexGame::winner() {
    if (checkWinForPlayer(RED)) return RED;
    if (checkWinForPlayer(BLUE)) return BLUE;
    return NONE;
}

Player HexGame::getFlippedPlayer(Player player) const {
    if (isBoardFlipped) {
        return (player == RED) ? BLUE : (player == BLUE) ? RED : NONE;
    }
    return player;
}

bool HexGame::checkWinForPlayer(Player player) {
    vector<vector<bool>> visited(BOARD_SIZE, vector<bool>(BOARD_SIZE, false));
    queue<pair<int, int>> positionQueue;

    if (player == RED) {
        for (int index = 0; index < BOARD_SIZE; ++index) {
            if (board[0][index] == RED) {
                positionQueue.push({0, index});
                visited[0][index] = true;
            }
        }
    } else {
        for (int index = 0; index < BOARD_SIZE; ++index) {
            if (board[index][0] == BLUE) {
                positionQueue.push({index, 0});
                visited[index][0] = true;
            }
        }
    }

    vector<pair<int, int>> directions = { {0, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, 0}, {-1, 1} };

    while (!positionQueue.empty()) {
        pair<int, int> currentPosition = positionQueue.front();
        positionQueue.pop();
        int xCoordinate = currentPosition.first;
        int yCoordinate = currentPosition.second;

        if ((player == RED && xCoordinate == BOARD_SIZE - 1) || (player == BLUE && yCoordinate == BOARD_SIZE - 1)) {
            return true;
        }

        for (const auto& direction : directions) {
            int newX = xCoordinate + direction.first;
            int newY = yCoordinate + direction.second;

            if (newX >= 0 && newX < BOARD_SIZE && newY >= 0 && newY < BOARD_SIZE
                && !visited[newX][newY] && board[newX][newY] == player) {
                visited[newX][newY] = true;
                positionQueue.push({newX, newY});
            }
        }
    }
    return false;
}
