#ifndef FIVEBYFIVEBOARD_H
#define FIVEBYFIVEBOARD_H

#include <iostream>
#include "BoardGame_Classes.h"

using namespace std;

class FiveByFiveBoard : public Board<char>
{
private:
    int rows = 5;
    int columns = 5;
    char **board;

public:
    FiveByFiveBoard()
    {
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

    ~FiveByFiveBoard()
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
            return true; // Valid move
        }
        return false; // Invalid move
    }

    void display_board() override
    {
        cout << "  ";
        for (int j = 0; j < columns; j++)
        {
            cout << j << " ";
        }
        cout << endl;

        for (int i = 0; i < rows; i++)
        {
            cout << i << " ";
            for (int j = 0; j < columns; j++)
            {
                cout << board[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }

    bool is_win() override
    {
        return false; // The game does not declare a winner mid-game
    }

    bool is_draw() override
    {
        return false; // The game cannot be a draw mid-game
    }

    bool game_is_over() override
    {
        return all_cells_filled(); // Game ends only when all cells are filled
    }

    void determine_winner()
    {
        int player1_score = calculate_score('X');
        int player2_score = calculate_score('O');

        cout << "Game Over!" << endl;
        cout << "Player 1 (X) Score: " << player1_score << endl;
        cout << "Player 2 (O) Score: " << player2_score << endl;

        if (player1_score > player2_score)
        {
            cout << "Player 1 (X) wins!" << endl;
        }
        else if (player2_score > player1_score)
        {
            cout << "Player 2 (O) wins!" << endl;
        }
        else
        {
            cout << "It's a tie!" << endl;
        }
    }

private:
    bool all_cells_filled()
    {
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < columns; j++)
            {
                if (board[i][j] == ' ')
                {
                    return false; // If any cell is empty, the game continues
                }
            }
        }
        return true; // All cells are filled
    }

    int calculate_score(char symbol)
    {
        int score = 0;

        // Directions to check: Horizontal, Vertical, Diagonal (both directions)
        int directions[4][2] = {{0, 1}, {1, 0}, {1, 1}, {1, -1}};
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < columns; j++)
            {
                if (board[i][j] == symbol)
                {
                    for (auto &dir : directions)
                    {
                        score += check_direction(i, j, symbol, dir[0], dir[1]);
                    }
                }
            }
        }
        return score;
    }

    int check_direction(int x, int y, char symbol, int dx, int dy)
    {
        int count = 0;

        // Check for three-in-a-row sequences in the given direction
        int nx1 = x + dx, ny1 = y + dy;
        int nx2 = nx1 + dx, ny2 = ny1 + dy;

        if (nx1 >= 0 && nx1 < rows && ny1 >= 0 && ny1 < columns &&
            nx2 >= 0 && nx2 < rows && ny2 >= 0 && ny2 < columns)
        {
            if (board[nx1][ny1] == symbol && board[nx2][ny2] == symbol)
            {
                count++;
            }
        }
        return count;
    }
};

class FiveByFivePlayer : public Player<char>
{
public:
    FiveByFivePlayer(string n, char s) : Player<char>(n, s) {}

    void getmove(int &x, int &y) override
    {
        cout << name << " (" << symbol << "), enter your move (row and column): ";
        cin >> x >> y;
    }
};

#endif // FIVEBYFIVEBOARD_H
