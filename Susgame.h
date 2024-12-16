#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "boardgame_classes.h"

using namespace std;


template <typename T>
class SUSBoard : public Board<T> {
private:
    int player1_score = 0;
    int player2_score = 0;
    bool should_pass_to_player2() {
        return (this->n_moves == this->rows * this->columns - 1 && player2_score == player1_score + 1);
    }


public:
    SUSBoard(int rows, int columns) {
        this->rows = rows;
        this->columns = columns;
        this->board = new T*[rows];
        for (int i = 0; i < rows; ++i) {
            this->board[i] = new T[columns];
            for (int j = 0; j < columns; ++j) {
                this->board[i][j] = ' '; 
            }
        }
    }

    ~SUSBoard() {
        for (int i = 0; i < this->rows; ++i) {
            delete[] this->board[i];
        }
        delete[] this->board;
    }

bool update_board(int x, int y, T symbol) override {
    if (x >= 0 && x < this->rows && y >= 0 && y < this->columns && this->board[x][y] == ' ') {
        this->board[x][y] = symbol;
        this->n_moves++;

        // Update scores dynamically
        int points = count_SUS(x, y);
        if (symbol == 'U') {
            player2_score += points;
        } else if (symbol == 'S') {
            player1_score += points;
        }

        // Check if Player 2 should take the final move
        if (should_pass_to_player2()) {
            // Make a "dummy move" for Player 2 on the last available cell
            for (int i = 0; i < this->rows; ++i) {
                for (int j = 0; j < this->columns; ++j) {
                    if (this->board[i][j] == ' ') {
                        this->board[i][j] = 'S';
                        this->n_moves++;
                        int dummy_points = count_SUS(i, j);
                        player1_score += dummy_points; // Update Player 1's score

                        // If Player 1's score exceeds Player 2's due to the dummy move, revert to Player 1's turn
                        if (player1_score > player2_score) {
                            this->board[i][j] = ' '; // Undo dummy move
                            this->n_moves--;
                            player1_score -= dummy_points; // Revert Player 1's score
                            return false; // Pass the turn back to Player 1
                        }

                        return true; // Final dummy move successful
                    }
                }
            }
        }

        return true; // Valid move
    }
    return false; // Invalid move
}




    void display_board() override {
        for (int i = 0; i < this->rows; ++i) {
            for (int j = 0; j < this->columns; ++j) {
                cout << this->board[i][j];
                if (j < this->columns - 1) cout << " | ";
            }
            cout << endl;
            if (i < this->rows - 1) cout << "--+---+--\n";
        }
        cout << "Player 1 (S) Score: " << player1_score << endl;
        cout << "Player 2 (U) Score: " << player2_score << endl;
        cout << endl;
    }

    bool is_win() override {
        if (this->n_moves == this->rows * this->columns) { // Only check when the board is full
            if (player1_score > player2_score) {
                return true; // Player 1 wins
            } else if (player2_score > player1_score) {
                return true; // Player 2 wins
            }
        }
        return false; // No winner yet
    }


    bool is_draw() override {   
        return (this->n_moves == this->rows * this->columns && player1_score==player2_score);
    }

    bool game_is_over() override {
        return this->n_moves == this->rows * this->columns ;
    }

    int get_player1_score() const {
        return player1_score;
    }

    int get_player2_score() const {
        return player2_score;
    }

private:
    int count_SUS(int x, int y) {
        int score = 0;
        score += check_SUS(x, y, 1, 0);  
        score += check_SUS(x, y, 0, 1);  
        score += check_SUS(x, y, 1, 1);  
        score += check_SUS(x, y, 1, -1); 
        return score;
    }

    int check_SUS(int x, int y, int dx, int dy) {
    int prev_x = x - dx, next_x = x + dx;
    int prev_y = y - dy, next_y = y + dy;

    
    if (prev_x >= 0 && prev_x < this->rows && next_x >= 0 && next_x < this->rows &&
        prev_y >= 0 && prev_y < this->columns && next_y >= 0 && next_y < this->columns) {

        
        if (this->board[prev_x][prev_y] == 'S' && this->board[x][y] == 'U' && this->board[next_x][next_y] == 'S') {
            return 1; 
        }

        
    }

    if (x >= 0 && x < this->rows && y >= 0 && y < this->columns) {
    

    
    if (next_x >= 0 && next_x < this->rows && next_y >= 0 && next_y < this->columns) {
        if (this->board[x][y] == 'S' && this->board[next_x][next_y] == 'U' &&
            next_x + (next_x - x) >= 0 && next_x + (next_x - x) < this->rows &&
            next_y + (next_y - y) >= 0 && next_y + (next_y - y) < this->columns &&
            this->board[next_x + (next_x - x)][next_y + (next_y - y)] == 'S') {
            return 1; 
        }
    }

    
    if (prev_x >= 0 && prev_x < this->rows && prev_y >= 0 && prev_y < this->columns) {
        if (this->board[x][y] == 'S' && this->board[prev_x][prev_y] == 'U' &&
            prev_x - (x - prev_x) >= 0 && prev_x - (x - prev_x) < this->rows &&
            prev_y - (y - prev_y) >= 0 && prev_y - (y - prev_y) < this->columns &&
            this->board[prev_x - (x - prev_x)][prev_y - (y - prev_y)] == 'S') {
            return 1; 
        }
    }

}

    return 0;
}

};


template <typename T>
class SUSHumanPlayer : public Player<T> {
public:
    SUSHumanPlayer(string name, T symbol) : Player<T>(name, symbol) {}

    void getmove(int& x, int& y) override {
        cout << this->getname() << " (" << this->getsymbol() << "), enter your move (row and column): ";
        cin >> x >> y;
    }
};


template <typename T>
class RandomSUSPlayer : public RandomPlayer<T> {
public:
    RandomSUSPlayer(T symbol, int dim) : RandomPlayer<T>(symbol) { this->dimension = dim; }

    void getmove(int& x, int& y) override {
        x = rand() % this->dimension;
        y = rand() % this->dimension;
    }
};

