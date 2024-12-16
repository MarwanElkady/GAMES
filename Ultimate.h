#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include "boardgame_classes.h"

using namespace std;


class TicTacToeBoard : public Board<char> {
public:
    TicTacToeBoard() {
        rows = 3;
        columns = 3;
        board = new char*[rows];
        for (int i = 0; i < rows; i++) {
            board[i] = new char[columns];
            for (int j = 0; j < columns; j++) {
                board[i][j] = ' ';
            }
        }
    }

    ~TicTacToeBoard() {
        for (int i = 0; i < rows; i++) {
            delete[] board[i];
        }
        delete[] board;
    }

    bool update_board(int x, int y, char symbol) override {
        if (x >= 0 && x < rows && y >= 0 && y < columns && board[x][y] == ' ') {
            board[x][y] = symbol;
            n_moves++;
            return true;
        }
        return false;
    }

    void display_board() override {
        cout << "   0   1   2\n";
        for (int i = 0; i < rows; i++) {
            cout << i << " ";
            for (int j = 0; j < columns; j++) {
                cout << board[i][j];
                if (j < columns - 1) cout << " | ";
            }
            cout << endl;
            if (i < rows - 1) cout << "  ---+---+---\n";
        }
        cout << endl;
    }

    bool is_win() override {
        for (int i = 0; i < rows; i++) {
            if (board[i][0] != ' ' && board[i][0] == board[i][1] && board[i][1] == board[i][2])
                return true;
        }
        for (int j = 0; j < columns; j++) {
            if (board[0][j] != ' ' && board[0][j] == board[1][j] && board[1][j] == board[2][j])
                return true;
        }
        if (board[0][0] != ' ' && board[0][0] == board[1][1] && board[1][1] == board[2][2])
            return true;
        if (board[0][2] != ' ' && board[0][2] == board[1][1] && board[1][1] == board[2][0])
            return true;
        return false;
    }

    bool is_draw() override {
        return n_moves == rows * columns && !is_win();
    }

    bool game_is_over() override {
        return is_win() || is_draw();
    }

    char get_cell(int x, int y) {
        return board[x][y];
    }
};


class UltimateTicTacToeBoard : public Board<char> {
private:
    TicTacToeBoard* boards[3][3];
    char mainBoard[3][3];
public:
    UltimateTicTacToeBoard() {
        rows = 3;
        columns = 3;
        n_moves = 0;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                boards[i][j] = new TicTacToeBoard();
                mainBoard[i][j] = ' ';
            }
        }
    }

    ~UltimateTicTacToeBoard() {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                delete boards[i][j];
            }
        }
    }

    bool update_board(int x, int y, char symbol) override {
        int bigX = x / 3, bigY = y / 3;
        int smallX = x % 3, smallY = y % 3;

        if (mainBoard[bigX][bigY] == ' ' && boards[bigX][bigY]->update_board(smallX, smallY, symbol)) {
            if (boards[bigX][bigY]->is_win()) {
                mainBoard[bigX][bigY] = symbol;
            }
            n_moves++;
            return true;
        }
        return false;

        if (boards[bigX][bigY]->is_win()) {
            mainBoard[bigX][bigY] = symbol;
        } else if (boards[bigX][bigY]->is_draw()) {
            mainBoard[bigX][bigY] = '-';
        }
    }

void display_board() override {
    cout << "Ultimate Tic Tac Toe Board:\n";

    for (int bigRow = 0; bigRow < 3; bigRow++) {
        for (int smallRow = 0; smallRow < 3; smallRow++) {
            cout << "\n|";
            for (int bigCol = 0; bigCol < 3; bigCol++) {
                for (int smallCol = 0; smallCol < 3; smallCol++) {

                    cout << "(" << bigRow * 3 + smallRow << "," << bigCol * 3 + smallCol << ")";
                    cout << setw(2) << boards[bigRow][bigCol]->get_cell(smallRow, smallCol) << " |";
                }
                if (bigCol < 2) cout << "|| "; 
            }
        }
        if (bigRow < 2) {
            cout << endl;
            cout << "\n=========================================================================================\n"; 
        }
    }
cout << endl; 
cout << "\nMain Board Status:\n";
    cout << "   0   1   2\n";
    for (int i = 0; i < 3; i++) {
        cout << i << " ";
        for (int j = 0; j < 3; j++) {
            char status = mainBoard[i][j];
            if (status == ' ') {
                cout << (boards[i][j]->game_is_over() ? '-' : ' '); 
            } else {
                cout << status;
            }
            if (j < 2) cout << " | ";
        }
        cout << endl;
        if (i < 2) cout << "  ---+---+---\n";
    }
    cout << endl;
}





    bool is_win() override {
        for (int i = 0; i < 3; i++) {
            if (mainBoard[i][0] != ' ' && mainBoard[i][0] == mainBoard[i][1] && mainBoard[i][1] == mainBoard[i][2])
                return true;
            if (mainBoard[0][i] != ' ' && mainBoard[0][i] == mainBoard[1][i] && mainBoard[1][i] == mainBoard[2][i])
                return true;
        }
        if (mainBoard[0][0] != ' ' && mainBoard[0][0] == mainBoard[1][1] && mainBoard[1][1] == mainBoard[2][2])
            return true;
        if (mainBoard[0][2] != ' ' && mainBoard[0][2] == mainBoard[1][1] && mainBoard[1][1] == mainBoard[2][0])
            return true;
        return false;
    }

    bool is_draw() override {
        return n_moves == 81 && !is_win();
    }

    bool game_is_over() override {
        return is_win() || is_draw();
    }
};

template <typename T>
class UltHumanPlayer : public Player<T> {
public:
    UltHumanPlayer(string name, T symbol) : Player<T>(name, symbol) {}

    void getmove(int& x, int& y) override {
        cout << Player<T>::name << " (" << Player<T>::symbol << "), enter your move (row and column): ";
        cin >> x >> y;
    }
};


template <typename T>
class UltimateTicTacToeRandomPlayer : public RandomPlayer<T> {
public:
    UltimateTicTacToeRandomPlayer(T symbol) : RandomPlayer<T>(symbol) {}

    void getmove(int& x, int& y) override {
        x = rand() % 9; 
        y = rand() % 9; 
    }
};

