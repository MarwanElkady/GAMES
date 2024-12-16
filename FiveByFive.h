#ifndef FIVEBYFIVEBOARD_H
#define FIVEBYFIVEBOARD_H

#include <iostream>
#include "BoardGame_Classes.h"

using namespace std;

class FiveByFive : public Board<char>
{
private:
    int rows = 5;
    int columns = 5;
    char **board;
    int player1_score = 0; // Score for Player 1 ('X')
    int player2_score = 0; // Score for Player 2 ('O')

public:
    FiveByFive()
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

    ~FiveByFive()
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

            // Update the score dynamically for the player
            int points = count_sequences(x, y, symbol);
            if (symbol == 'X')
            {
                player1_score += points;
            }
            else if (symbol == 'O')
            {
                player2_score += points;
            }

            // Debugging
            cout << "Move at (" << x << ", " << y << ") by " << symbol << " scores " << points << " points." << endl;

            return true;
        }
        return false;
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

        cout << "Player 1 (X) Score: " << player1_score << endl;
        cout << "Player 2 (O) Score: " << player2_score << endl;
    }

    bool is_win() override
    {
        // Only check if all cells are filled and return true if the game is over
        return all_cells_filled();
    }

    bool is_draw() override
    {
        return all_cells_filled() && (player1_score == player2_score);
    }

    bool game_is_over() override
    {
        return all_cells_filled();
    }

    string determine_winner()
    {
        if (player1_score > player2_score)
        {
            return "Player 1 (X) wins!";
        }
        else if (player2_score > player1_score)
        {
            return "Player 2 (O) wins!";
        }
        else
        {
            return "It's a tie!";
        }
    }

private:
    bool winner_determined = false;
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

    int count_sequences(int x, int y, char symbol)
    {
        int score = 0;
        score += check_sequence(x, y, symbol, 1, 0);  // Horizontal
        score += check_sequence(x, y, symbol, 0, 1);  // Vertical
        score += check_sequence(x, y, symbol, 1, 1);  // Diagonal
        score += check_sequence(x, y, symbol, 1, -1); // Diagonal
        return score;
    }

    int check_sequence(int x, int y, char symbol, int dx, int dy)
    {
        int forward_count = 0, backward_count = 0;

        // Move forward in the direction
        int nx = x + dx, ny = y + dy;
        while (nx >= 0 && nx < rows && ny >= 0 && ny < columns && board[nx][ny] == symbol)
        {
            forward_count++;
            nx += dx;
            ny += dy;
        }

        // Move backward in the opposite direction
        nx = x - dx, ny = y - dy;
        while (nx >= 0 && nx < rows && ny >= 0 && ny < columns && board[nx][ny] == symbol)
        {
            backward_count++;
            nx -= dx;
            ny -= dy;
        }

        // Total count includes the current cell
        int total_count = forward_count + backward_count + 1;

        // Adjust score based on sequence length
        if (total_count == 3)
        {
            return 1; // Score 3 for sequence of exactly 3
        }
        else if (total_count == 4)
        {
            return 1; // Add 2 to align with scoring logic
        }
        else if (total_count == 5)
        {
            return 1; // Subtract 2 to ensure the total is reduced to match the requirement
        }

        return 0; // No points for sequences shorter than 3 or longer than 5
    }
};

// FiveByFiveRandomPlayer Implementation
class FiveByFiveRandomPlayer : public RandomPlayer<char>
{
public:
    FiveByFiveRandomPlayer(char symbol) : RandomPlayer<char>(symbol)
    {
        srand(static_cast<unsigned int>(time(0))); // Seed for random number generation
    }

    void getmove(int &x, int &y) override
    {
        x = rand() % 5;
        y = rand() % 5;
    }
};

// FiveByFivePlayer Implementation
class FiveByFivePlayer : public Player<char>
{
public:
    FiveByFivePlayer(string name, char symbol) : Player<char>(name, symbol) {}

    void getmove(int &x, int &y) override
    {
        cout << this->getname() << " (" << this->getsymbol() << "), enter your move (row and column): ";
        cin >> x >> y;
    }
};
#endif // FIVEBYFIVEBOARD_H
