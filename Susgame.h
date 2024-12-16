#include "boardgame_classes.h"
#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

class SUSBoard : public Board<char>
{
public:
    SUSBoard(int r = 3, int c = 3)
    {
        rows = r;
        columns = c;
        board = new char *[rows];
        for (int i = 0; i < rows; i++)
        {
            board[i] = new char[columns];
            for (int j = 0; j < columns; j++)
                board[i][j] = ' '; // Initialize empty grid
        }
    }

    // Update the board with 'S' or 'U'
    bool update_board(int x, int y, char symbol) override
    {
        if (x >= 0 && x < rows && y >= 0 && y < columns && board[x][y] == ' ')
        {
            board[x][y] = symbol;
            n_moves++;
            return true;
        }
        return false;
    }

    void display_board() override
    {
        cout << "\n";
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < columns; j++)
            {
                cout << setw(2) << board[i][j] << " |";
            }
            cout << "\n-----------\n";
        }
    }

    // Check for SUS sequences
    bool is_win() override
    {
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < columns; ++j)
            {
                if (check_SUS(i, j))
                    return true;
            }
        }
        return false;
    }

    bool is_draw() override
    {
        return n_moves == rows * columns && !is_win();
    }

    bool game_is_over() override
    {
        return is_win() || is_draw();
    }

private:
    bool check_SUS(int x, int y)
    {
        // Directions: Horizontal, Vertical, Diagonals
        int directions[4][2] = {{0, 1}, {1, 0}, {1, 1}, {1, -1}};
        if (board[x][y] == 'S')
        {
            for (auto &dir : directions)
            {
                int dx = dir[0], dy = dir[1];
                if (in_bounds(x + dx, y + dy) && board[x + dx][y + dy] == 'U' && in_bounds(x + 2 * dx, y + 2 * dy) && board[x + 2 * dx][y + 2 * dy] == 'S')
                {
                    return true;
                }
            }
        }
        return false;
    }

    bool in_bounds(int x, int y)
    {
        return x >= 0 && x < rows && y >= 0 && y < columns;
    }
};

// Human player class
class HumanPlayer : public Player<char>
{
public:
    HumanPlayer(string n, char s) : Player<char>(n, s) {}
    void getmove(int &x, int &y) override
    {
        cout << name << "'s turn (" << symbol << "): Enter row and column (0-2): ";
        cin >> x >> y;
    }
};