#ifndef ULTIMATE_TIC_TAC_TOE_H
#define ULTIMATE_TIC_TAC_TOE_H

#include "boardgame_classes.h"
#include <iostream>
#include <iomanip>
using namespace std;

// Ultimate Tic Tac Toe Board Class
class UltimateBoard : public Board<char> {
private:
    // 3x3 grids, each grid is a mini tic-tac-toe
    char subBoards[3][3][3][3];
    bool subBoardWon[3][3] = {{false}}; // Tracks won grids
    char subBoardWinner[3][3] = {{' '}}; // Winner of each grid
    int currentRow, currentCol; // Active grid coordinates

public:
    UltimateBoard();
    bool update_board(int x, int y, char symbol) override;
    void display_board() override;
    bool is_win() override;
    bool is_draw() override;
    bool game_is_over() override;
    bool isSubBoardWin(int gridX, int gridY, char symbol);
    void displaySubBoard(int gridX, int gridY);
};

UltimateBoard::UltimateBoard() {
    rows = columns = 9;
    currentRow = currentCol = -1;
    // Initialize the board to empty
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            for (int x = 0; x < 3; x++) {
                for (int y = 0; y < 3; y++) {
                    subBoards[i][j][x][y] = ' ';
                }
            }
        }
    }
}

bool UltimateBoard::update_board(int x, int y, char symbol) {
    // Ensure the move is within bounds
    if (x < 0 || x >= 9 || y < 0 || y >= 9) return false;

    int gridX = x / 3, gridY = y / 3;
    int cellX = x % 3, cellY = y % 3;

    // Check if move is in active grid or first move
    if (currentRow != -1 && currentCol != -1 && (gridX != currentRow || gridY != currentCol)) {
        cout << "Invalid move. Play in the active grid: (" << currentRow << ", " << currentCol << ").\n";
        return false;
    }

    // Check if the cell is empty
    if (subBoards[gridX][gridY][cellX][cellY] != ' ') return false;

    subBoards[gridX][gridY][cellX][cellY] = symbol; // Make the move
    n_moves++;

    // Check for a win in the sub-board
    if (isSubBoardWin(gridX, gridY, symbol)) {
        subBoardWon[gridX][gridY] = true;
        subBoardWinner[gridX][gridY] = symbol;
        cout << "Sub-board (" << gridX << ", " << gridY << ") won by " << symbol << "!\n";
    }

    // Update active grid
    currentRow = cellX;
    currentCol = cellY;

    // If the next grid is already won, allow any move
    if (subBoardWon[currentRow][currentCol]) {
        currentRow = -1;
        currentCol = -1;
    }
    return true;
}

bool UltimateBoard::isSubBoardWin(int gridX, int gridY, char symbol) {
    // Check rows, columns, and diagonals in a 3x3 grid
    for (int i = 0; i < 3; i++) {
        if (subBoards[gridX][gridY][i][0] == symbol && subBoards[gridX][gridY][i][1] == symbol && subBoards[gridX][gridY][i][2] == symbol)
            return true;
        if (subBoards[gridX][gridY][0][i] == symbol && subBoards[gridX][gridY][1][i] == symbol && subBoards[gridX][gridY][2][i] == symbol)
            return true;
    }
    if (subBoards[gridX][gridY][0][0] == symbol && subBoards[gridX][gridY][1][1] == symbol && subBoards[gridX][gridY][2][2] == symbol)
        return true;
    if (subBoards[gridX][gridY][0][2] == symbol && subBoards[gridX][gridY][1][1] == symbol && subBoards[gridX][gridY][2][0] == symbol)
        return true;

    return false;
}

void UltimateBoard::display_board() {
    cout << "\nUltimate Tic Tac Toe Board:\n";
    for (int gridX = 0; gridX < 3; gridX++) {
        for (int row = 0; row < 3; row++) {
            for (int gridY = 0; gridY < 3; gridY++) {
                for (int col = 0; col < 3; col++) {
                    cout << subBoards[gridX][gridY][row][col];
                    if (col < 2) cout << " | ";
                }
                cout << "   ";
            }
            cout << "\n";
        }
        if (gridX < 2) cout << string(45, '-') << "\n";
    }
}

bool UltimateBoard::is_win() {
    // Check if any player has won the overall 3x3 grid
    for (int i = 0; i < 3; i++) {
        if (subBoardWinner[i][0] != ' ' && subBoardWinner[i][0] == subBoardWinner[i][1] && subBoardWinner[i][1] == subBoardWinner[i][2])
            return true;
        if (subBoardWinner[0][i] != ' ' && subBoardWinner[0][i] == subBoardWinner[1][i] && subBoardWinner[1][i] == subBoardWinner[2][i])
            return true;
    }
    if (subBoardWinner[0][0] != ' ' && subBoardWinner[0][0] == subBoardWinner[1][1] && subBoardWinner[1][1] == subBoardWinner[2][2])
        return true;
    if (subBoardWinner[0][2] != ' ' && subBoardWinner[0][2] == subBoardWinner[1][1] && subBoardWinner[1][1] == subBoardWinner[2][0])
        return true;

    return false;
}

bool UltimateBoard::is_draw() {
    return n_moves == 81 && !is_win();
}

bool UltimateBoard::game_is_over() {
    return is_win() || is_draw();
}

#endif // ULTIMATE_TIC_TAC_TOE_H
