#ifndef _CONNECT_FOUR_H
#define _CONNECT_FOUR_H

#include "BoardGame_Classes.h"
#include <iostream>
#include <iomanip>
#include <limits>
using namespace std;

template <typename T>
class ConnectFourBoard : public Board<T> {
public:
    ConnectFourBoard();
    bool update_board(int x, int y, T symbol);
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();
};

template <typename T>
class ConnectFourPlayer : public Player<T> {
public:
    ConnectFourPlayer(string name, T symbol);
    void getmove(int& x, int& y);
};

template <typename T>
ConnectFourBoard<T>::ConnectFourBoard() {
    this->rows = 6;
    this->columns = 7;
    this->board = new T*[this->rows];
    for (int i = 0; i < this->rows; ++i) {
        this->board[i] = new T[this->columns];
        for (int j = 0; j < this->columns; ++j) {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
}

template <typename T>
bool ConnectFourBoard<T>::update_board(int x, int y, T symbol) {
    y -= 1;
    if (y < 0 || y >= this->columns || this->board[0][y] != 0) {
        return false;
    }
    for (int i = this->rows - 1; i >= 0; --i) {
        if (this->board[i][y] == 0) {
            this->board[i][y] = symbol;
            ++this->n_moves;
            return true;
        }
    }
    return false;
}

template <typename T>
void ConnectFourBoard<T>::display_board() {
    cout << endl;
    for (int i = 0; i < this->rows; ++i) {
        cout << "| ";
        for (int j = 0; j < this->columns; ++j) {
            cout << (this->board[i][j] ? this->board[i][j] : '.') << " ";
        }
        cout << "|\n";
    }
    cout << "  1 2 3 4 5 6 7 \n";
}

template <typename T>
bool ConnectFourBoard<T>::is_win() {
    for (int i = 0; i < this->rows; ++i) {
        for (int j = 0; j < this->columns; ++j) {
            T curr = this->board[i][j];
            if (curr == 0) continue;

            if (j + 3 < this->columns &&
                curr == this->board[i][j + 1] && curr == this->board[i][j + 2] && curr == this->board[i][j + 3]) {
                return true;
            }

            if (i + 3 < this->rows &&
                curr == this->board[i + 1][j] && curr == this->board[i + 2][j] && curr == this->board[i + 3][j]) {
                return true;
            }

            if (i + 3 < this->rows && j + 3 < this->columns &&
                curr == this->board[i + 1][j + 1] && curr == this->board[i + 2][j + 2] && curr == this->board[i + 3][j + 3]) {
                return true;
            }

            if (i + 3 < this->rows && j - 3 >= 0 &&
                curr == this->board[i + 1][j - 1] && curr == this->board[i + 2][j - 2] && curr == this->board[i + 3][j - 3]) {
                return true;
            }
        }
    }
    return false;
}

template <typename T>
bool ConnectFourBoard<T>::is_draw() {
    return this->n_moves == this->rows * this->columns && !is_win();
}

template <typename T>
bool ConnectFourBoard<T>::game_is_over() {
    return is_win() || is_draw();
}

template <typename T>
ConnectFourPlayer<T>::ConnectFourPlayer(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void ConnectFourPlayer<T>::getmove(int& x, int& y) {
    while (true) {
        cout << "\n" << this->getname() << ", enter the column (1 - 7): ";
        cin >> y;

        if (cin.fail() || y < 1 || y > 7) {
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            cout << "Invalid move. Please enter a valid column (1 - 7)." << endl;
        } else {
            break;
        }
    }
    x = 0;
}


template <typename T>
class ConnectFourRandomPlayer : public RandomPlayer<T> {
public:
    ConnectFourRandomPlayer(T symbol) : RandomPlayer<T>(symbol) {}

    void getmove(int& x, int& y) override {
        x = 0;
        y = rand() % 8;
    }
};

#endif
