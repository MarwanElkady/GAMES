#ifndef REVERSETICTACTOEBOARD_H
#define REVERSETICTACTOEBOARD_H

#include "BoardGame_Classes.h"
#include <iostream>
using namespace std;

class TicTacToeInverse : public Board<char>
{
private:
    bool skipWin = true;
    bool continue_game = true;

    bool check_win()
    {
        for (int i = 0; i < this->rows; i++)
        {
            if ((this->board[i][0] == this->board[i][1] && this->board[i][1] == this->board[i][2] &&
                 this->board[i][0] != '_') ||
                (this->board[0][i] == this->board[1][i] && this->board[1][i] == this->board[2][i] &&
                 this->board[0][i] != '_'))
            {
                return true;
            }
        }

        if ((this->board[0][0] == this->board[1][1] && this->board[1][1] == this->board[2][2] &&
             this->board[0][0] != '_') ||
            (this->board[0][2] == this->board[1][1] && this->board[1][1] == this->board[2][0] &&
             this->board[0][2] != '_'))
        {
            return true;
        }

        return false;
    }

public:
    TicTacToeInverse()
    {
        rows = 3;
        columns = 3;
        n_moves = 0;
        board = new char *[rows];
        for (int i = 0; i < rows; ++i)
        {
            board[i] = new char[columns]();
            for (int j = 0; j < columns; ++j)
            {
                board[i][j] = '_';
            }
        }
    }

    bool game_is_over() override
    {
        if (this->is_win() || this->is_draw())
        {
            if (continue_game)
            {
                continue_game = false;
                return false;
            }
            else
            {
                return true;
            }
        }
        return false;
    }

    bool is_win() override
    {
        if (check_win())
        {
            if (skipWin)
            {
                skipWin = false;
                return false;
            }
            else
            {
                return true;
            }
        }
        return false;
    }

    bool is_draw() override
    {
        if (this->n_moves == this->rows * this->columns + 1)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    void display_board() override
    {

        cout << "    ";
        for (int col = 0; col < columns; ++col)
        {
            cout << "  " << col << "   ";
        }
        cout << "\n";

        for (int row = 0; row < rows; ++row)
        {
            cout << "  ";
            for (int col = 0; col < columns; ++col)
            {
                cout << "------";
            }
            cout << "-\n";

            cout << row << " |";
            for (int col = 0; col < columns; ++col)
            {
                cout << "  " << board[row][col] << "  |";
            }
            cout << "\n";
        }

        cout << "  ";
        for (int col = 0; col < columns; ++col)
        {
            cout << "------";
        }
        cout << "-\n";
    }

    bool update_board(int x, int y, char symbol) override
    {
        if (!skipWin)
        {
            return true;
        }
        if (x < 0 || x >= rows || y < 0 || y >= columns)
        {
            return false;
        }
        if (board[x][y] == '_')
        {
            board[x][y] = symbol;
            n_moves++;
            return true;
        }
        return false;
    }
};

class InversePlayer : public Player<char>
{

public:
    InversePlayer(string n, char s) : Player<char>(n, s) {}

    void getmove(int &x, int &y) override
    {

        cout << name << " (" << symbol << "), enter your move (row and column): ";
        cin >> x >> y;
    }
};

template <typename T>
class InverseRandom : public RandomPlayer<T>
{
private:
    int dimension;

public:
    InverseRandom(T symbol) : RandomPlayer<T>(symbol)
    {
        this->dimension = 3;
        this->name = "Random Computer Player";
        srand(static_cast<unsigned int>(time(0)));
    }

    void getmove(int &x, int &y) override
    {
        x = rand() % this->dimension;
        y = rand() % this->dimension;
        cout << this->name << " (" << this->symbol << ") chooses: " << x << ", " << y << std::endl;
    }
};

#endif // REVERSETICTACTOEBOARD_H
