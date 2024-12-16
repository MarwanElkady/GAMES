#ifndef REVERSETICTACTOEBOARD_H
#define REVERSETICTACTOEBOARD_H

#include "BoardGame_Classes.h"
#include <iostream>
using namespace std;

class ReverseTicTacToeBoard : public Board<char>
{
public:
    ReverseTicTacToeBoard()
    {
        rows = 3;
        columns = 3;
        board = new char *[rows];
        for (int i = 0; i < rows; i++)
        {
            board[i] = new char[columns];
            for (int j = 0; j < columns; j++)
            {
                board[i][j] = ' '; // Initialize all positions as empty
            }
        }
    }

    ~ReverseTicTacToeBoard()
    {
        for (int i = 0; i < rows; i++)
        {
            delete[] board[i];
        }
        delete[] board;
    }

    bool update_board(int x, int y, char symbol) override
    {
        if (x >= 0 && x < rows && y >= 0 && y < columns && board[x][y] == ' ')
        {
            board[x][y] = symbol;
            return true;
        }
        return false;
    }

    void display_board() override
    {
        cout << "  ";
        for (int j = 0; j < columns; j++)
            cout << j << " ";
        cout << "\n";

        for (int i = 0; i < rows; i++)
        {
            cout << i << " ";
            for (int j = 0; j < columns; j++)
            {
                cout << board[i][j];
                if (j < columns - 1)
                    cout << "|";
            }
            cout << "\n";
            if (i < rows - 1)
            {
                cout << "  ";
                for (int k = 0; k < columns; k++)
                {
                    cout << "-";
                    if (k < columns - 1)
                        cout << "+";
                }
                cout << "\n";
            }
        }
        cout << endl;
    }

    bool is_win() override
    {
        // Check rows
        for (int i = 0; i < rows; i++)
        {
            if (board[i][0] != ' ' && board[i][0] == board[i][1] && board[i][1] == board[i][2])
            {
                return true; // A player hits 3 in a row
            }
        }

        // Check columns
        for (int j = 0; j < columns; j++)
        {
            if (board[0][j] != ' ' && board[0][j] == board[1][j] && board[1][j] == board[2][j])
            {
                return true; // A player hits 3 in a column
            }
        }

        // Check diagonals
        if (board[0][0] != ' ' && board[0][0] == board[1][1] && board[1][1] == board[2][2])
        {
            return true; // A player hits 3 diagonally
        }

        if (board[0][2] != ' ' && board[0][2] == board[1][1] && board[1][1] == board[2][0])
        {
            return true; // A player hits 3 diagonally
        }

        return false;
    }

    bool is_draw() override
    {
        int filledCells = 0;
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < columns; j++)
            {
                if (board[i][j] != ' ')
                {
                    filledCells++;
                }
            }
        }
        return filledCells == rows * columns && !is_win();
    }

    bool game_is_over() override
    {
        return is_win() || is_draw();
    }
};

#endif // REVERSETICTACTOEBOARD_H
