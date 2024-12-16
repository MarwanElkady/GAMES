#ifndef _NUMERICAL_GAME_H
#define _NUMERICAL_GAME_H

#include "BoardGame_Classes.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <cstdlib>
using namespace std;

template <typename T>
class NumericalBoard : public Board<T> {
public:
    NumericalBoard();
    ~NumericalBoard();
    bool update_board(int x, int y, T symbol);
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();

    int get_rows() const { return this->rows; }
    int get_columns() const { return this->columns; }
    T get_board_cell(int x, int y) const { return this->board[x][y]; }

private:
    bool check_sum();
};

template <typename T>
class NumericalPlayer : public Player<T> {
public:
    NumericalPlayer(string name, vector<T> numbers);
    void getmove(int& x, int& y);
    vector<T> available_numbers();
private:
    vector<T> numbers;
};

template <typename T>
NumericalBoard<T>::NumericalBoard() {
    this->rows = this->columns = 3;
    this->board = new T*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new T[this->columns]();
    }
    this->n_moves = 0;
}

template <typename T>
NumericalBoard<T>::~NumericalBoard() {
    for (int i = 0; i < this->rows; i++) {
        delete[] this->board[i];
    }
    delete[] this->board;
}

template <typename T>
bool NumericalBoard<T>::update_board(int x, int y, T symbol) {
    if (x < 0 || x >= this->rows || y < 0 || y >= this->columns || this->board[x][y] != 0) {
        return false;
    }
    this->board[x][y] = symbol;
    this->n_moves++;
    return true;
}

template <typename T>
void NumericalBoard<T>::display_board() {
    for (int i = 0; i < this->rows; i++) {
        cout << "\n|";
        for (int j = 0; j < this->columns; j++) {
            if (this->board[i][j] == 0)
                cout << setw(3) << " " << " |";
            else
                cout << setw(3) << this->board[i][j] << " |";
        }
        cout << "\n------------------";
    }
    cout << endl;
}

template <typename T>
bool NumericalBoard<T>::check_sum() {
    for (int i = 0; i < 3; i++) {
        if (this->board[i][0] != 0 && this->board[i][1] != 0 && this->board[i][2] != 0 &&
            (this->board[i][0] + this->board[i][1] + this->board[i][2] == 15)) {
            return true;
        }
        if (this->board[0][i] != 0 && this->board[1][i] != 0 && this->board[2][i] != 0 &&
            (this->board[0][i] + this->board[1][i] + this->board[2][i] == 15)) {
            return true;
        }
    }

    if (this->board[0][0] != 0 && this->board[1][1] != 0 && this->board[2][2] != 0 &&
        (this->board[0][0] + this->board[1][1] + this->board[2][2] == 15)) {
        return true;
    }

    if (this->board[0][2] != 0 && this->board[1][1] != 0 && this->board[2][0] != 0 &&
        (this->board[0][2] + this->board[1][1] + this->board[2][0] == 15)) {
        return true;
    }

    return false;
}

template <typename T>
bool NumericalBoard<T>::is_win() {
    return check_sum();
}

template <typename T>
bool NumericalBoard<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

template <typename T>
bool NumericalBoard<T>::game_is_over() {
    return is_win() || is_draw();
}

template <typename T>
NumericalPlayer<T>::NumericalPlayer(string name, vector<T> numbers) : Player<T>(name, 0), numbers(numbers) {}

template <typename T>
vector<T> NumericalPlayer<T>::available_numbers() {
    return this->numbers;
}

template <typename T>
void NumericalPlayer<T>::getmove(int& x, int& y) {
    T symbol;
    cout << this->name << ", choose from your numbers: ";
    for (T num : numbers) {
        cout << num << " ";
    }
    cout << endl;
    cin >> symbol;

    while (find(numbers.begin(), numbers.end(), symbol) == numbers.end()) {
        cout << "Invalid number. Choose again: ";
        cin >> symbol;
    }

    numbers.erase(remove(numbers.begin(), numbers.end(), symbol), numbers.end());
    cout << "Enter your move (row col): ";
    cin >> x >> y;
    this->symbol = symbol;
}


template <typename T>
class NumericalRandomPlayer : public RandomPlayer<T> {
public:
    NumericalRandomPlayer(T symbol, vector<T> numbers);
    void getmove(int& x, int& y) override;

private:
    vector<T> numbers;
};

template <typename T>
NumericalRandomPlayer<T>::NumericalRandomPlayer(T symbol, vector<T> numbers)
    : RandomPlayer<T>(symbol), numbers(numbers) {}

template <typename T>
void NumericalRandomPlayer<T>::getmove(int& x, int& y) {
    if (numbers.empty()) {
        x = -1;
        y = -1;
        return;
    }

    T symbol = numbers[rand() % numbers.size()];
    numbers.erase(remove(numbers.begin(), numbers.end(), symbol), numbers.end());
    this->symbol = symbol;

    NumericalBoard<T>* numericalBoard = dynamic_cast<NumericalBoard<T>*>(this->boardPtr);
    if (!numericalBoard) {
        throw runtime_error("Board is not a NumericalBoard!");
    }

    int rows = numericalBoard->get_rows();
    int columns = numericalBoard->get_columns();

    do {
        x = rand() % rows;
        y = rand() % columns;
    } while (numericalBoard->get_board_cell(x, y) != 0);
}


#endif
