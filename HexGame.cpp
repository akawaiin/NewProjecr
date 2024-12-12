#include "HexGame.h"

HexGame::HexGame()
        : board(BOARD_SIZE, vector<Player>(BOARD_SIZE, NONE)),
          currentPlayer(BLUE),
          firstMoveDone(false),
          isBoardFlipped(false) {}

void HexGame::displayBoard() {
    cout << "   ";
    for (int i = 0; i < BOARD_SIZE; ++i) {
        cout << i << " ";
    }
    cout << endl;

    // Отображение каждой строки игрового поля
    for (int i = 0; i < BOARD_SIZE; ++i) {
        cout << string(i, ' ') << i << " "; // Отступ для формы доски
        for (int j = 0; j < BOARD_SIZE; ++j) {
            Player player = isBoardFlipped ? getFlippedPlayer(board[j][i]) : board[i][j];
            if (player == RED) cout << "R ";
            else if (player == BLUE) cout << "B ";
            else cout << ". ";
        }
        cout << endl;
    }
}

void HexGame::makeMove(int row, int col) {
    // Проверка валидности координат и того, что клетка пустая
    if (row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE && board[row][col] == NONE) {
        board[row][col] = currentPlayer; // Применение хода текущего игрока

        // Если это первый ход в игре
        if (!firstMoveDone) {
            firstMoveDone = true; // Установить флаг первой игры
            char choice;
            cout << "Player " << (currentPlayer == RED ? "RED" : "BLUE") << " made the first move. Do you want to flip the board? (y/n): ";
            cin >> choice;
            if (choice == 'y' || choice == 'Y') {
                isBoardFlipped = true; // Перевернуть доску
                currentPlayer = (currentPlayer == BLUE) ? RED : BLUE; // Сменить цвет игрока
            }
            cout << endl << endl; // Два перехода на новую строку
        }

        currentPlayer = (currentPlayer == BLUE) ? RED : BLUE; // Переключение текущего игрока
    } else {
        cout << "Incorrect move. Try again." << endl;
    }
}

Player HexGame::getCurrentPlayer() const {
    return currentPlayer; // Возвращает текущего игрока
}

bool HexGame::checkWin() {
    return checkWinForPlayer(RED) || checkWinForPlayer(BLUE); // Проверка победы для обоих игроков
}

Player HexGame::winner() {
    if (checkWinForPlayer(RED)) return RED;
    if (checkWinForPlayer(BLUE)) return BLUE;
    return NONE;
}

Player HexGame::getFlippedPlayer(Player player) const {
    if (isBoardFlipped) {
        return (player == RED) ? BLUE : (player == BLUE) ? RED : NONE; // Меняет RED и BLUE, если доска перевернута
    }
    return player;
}

bool HexGame::checkWinForPlayer(Player player) {
    vector<vector<bool>> visited(BOARD_SIZE, vector<bool>(BOARD_SIZE, false)); // Массив для отслеживания посещенных клеток
    queue<pair<int, int>> q; // Очередь для реализации BFS

    // Заполнение очереди для начальной позиции
    if (player == RED) {
        for (int i = 0; i < BOARD_SIZE; ++i) {
            if (board[0][i] == RED) {
                q.push({0, i}); // Добавить в очередь
                visited[0][i] = true; // Отметить как посещенное
            }
        }
    } else { // BLUE
        for (int i = 0; i < BOARD_SIZE; ++i) {
            if (board[i][0] == BLUE) {
                q.push({i, 0}); // Добавить в очередь
                visited[i][0] = true; // Отметить как посещенное
            }
        }
    }

    // Направления для проверки соседей на доске
    vector<pair<int, int>> directions = { {0, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, 0}, {-1, 1} };

    // BFS для проверки выигрышного пути
    while (!q.empty()) {
        pair<int, int> p = q.front(); // Получение координат из очереди
        q.pop();
        int x = p.first;
        int y = p.second;

        if ((player == RED && x == BOARD_SIZE - 1) || (player == BLUE && y == BOARD_SIZE - 1)) {
            return true;
        }

        // Проверка всех соседей
        for (const auto& dir : directions) {
            int nx = x + dir.first; // Новая координата x
            int ny = y + dir.second; // Новая координата y

            // Проверка границ и наличия игрока
            if (nx >= 0 && nx < BOARD_SIZE && ny >= 0 && ny < BOARD_SIZE
                && !visited[nx][ny] && board[nx][ny] == player) {
                visited[nx][ny] = true;
                q.push({nx, ny}); // Добавить в очередь
            }
        }
    }
    return false;
}