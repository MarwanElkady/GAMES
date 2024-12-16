#ifndef PYRAMID_TICTACTOE_H
#define PYRAMID_TICTACTOE_H

#include "BoardGame_Classes.h"
#include <iostream>
#include <iomanip>
#include <limits>
#include <cstdlib>
#include <ctime>

using namespace std;

template <typename T>
class PyramidBoard : public Board<T> {
public:
    PyramidBoard();
    bool update_board(int x, int y, T symbol) override;
    void display_board() override;
    bool is_win() override;
    bool is_draw() override;
    bool game_is_over() override;

private:
    bool check_line(T a, T b, T c);  
};

template <typename T>
class PyramidPlayer : public Player<T> {
public:
    PyramidPlayer(string name, T symbol);
    void getmove(int& x, int& y) override;
};

template <typename T>
class PyramidRandomPlayer : public RandomPlayer<T> {
public:
    PyramidRandomPlayer(T symbol);
    void getmove(int& x, int& y) override;
};

//--------------------------------------- IMPLEMENTATION


template <typename T>
PyramidBoard<T>::PyramidBoard() {
    this->rows = 3;  
    this->board = new T*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new T[2 * i + 1];
        for (int j = 0; j < (2 * i + 1); j++) {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
}


template <typename T>
bool PyramidBoard<T>::update_board(int x, int y, T symbol) {
    if (x >= 0 && x < this->rows && y >= 0 && y < (2 * x + 1) && this->board[x][y] == 0) {
        this->board[x][y] = symbol;
        this->n_moves++;
        return true;
    }
    return false;
}


template <typename T>
void PyramidBoard<T>::display_board() {
    for (int i = 0; i < this->rows; i++) {
        cout << setw(3 * (this->rows - i)) << "";  
        for (int j = 0; j < (2 * i + 1); j++) {
            cout << (this->board[i][j] == 0 ? "." : string(1, this->board[i][j])) << " ";
        }
        cout << endl;
    }
    cout << endl;
}

template <typename T>
bool PyramidBoard<T>::is_win() {

    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < (2 * i - 1); j++) {
            if (check_line(this->board[i][j], this->board[i][j + 1], this->board[i][j + 2])) {
                return true;
            }
        }
    }


    for (int i = 0; i < this->rows - 1; i++) {
        for (int j = 0; j < (2 * i + 1); j++) {
            if (j < (2 * i - 1)) {  
                if (check_line(this->board[i][j], this->board[i + 1][j], this->board[i + 1][j + 1])) {
                    return true;
                }
            }
            if (j > 0) {  
                if (check_line(this->board[i][j], this->board[i + 1][j], this->board[i + 1][j - 1])) {
                    return true;
                }
            }
            if (j < (2 * i + 1)) {
                if (check_line(this->board[i][j], this->board[i + 1][j], this->board[i + 2][j])) {
                    return true;
                }
            }
        }
    }
    return false;
}

// PyramidBoard is_draw
template <typename T>
bool PyramidBoard<T>::is_draw() {
    return (this->n_moves == 9) && !is_win(); 
}

// PyramidBoard game_is_over
template <typename T>
bool PyramidBoard<T>::game_is_over() {
    return is_win() || is_draw();
}


template <typename T>
bool PyramidBoard<T>::check_line(T a, T b, T c) {
    return a != 0 && a == b && b == c;
}


template <typename T>
PyramidPlayer<T>::PyramidPlayer(string name, T symbol) : Player<T>(name, symbol) {}


template <typename T>
void PyramidPlayer<T>::getmove(int& x, int& y) {
    cout << this->getname() << ", enter your move (row column): ";
    cin >> x >> y;
    while (cin.fail() || x < 0 || y < 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Enter your move (row column): ";
        cin >> x >> y;
    }
}


template <typename T>
PyramidRandomPlayer<T>::PyramidRandomPlayer(T symbol) : RandomPlayer<T>(symbol) {
    srand(static_cast<unsigned int>(time(0)));  // Seed RNG
}


template <typename T>
void PyramidRandomPlayer<T>::getmove(int& x, int& y) {
    do {
        x = rand() % 3;             
        y = rand() % (2 * x + 1); 
    } while (this->boardPtr && !this->boardPtr->update_board(x, y, 0));  
}

#endif  // PYRAMID_TICTACTOE_H
