#ifndef _WORD_TICTACTOE_H
#define _WORD_TICTACTOE_H

#include "BoardGame_Classes.h"
#include <unordered_set>
#include <fstream>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <cctype>
#include <cassert>

using namespace std;


unordered_set<string> load_dictionary(const string& file_name) {
    unordered_set<string> words;
    ifstream file(file_name);
    string word;
    while (file >> word) {
        transform(word.begin(), word.end(), word.begin(), ::toupper);
        words.insert(word);
    }
    return words;
}

template <typename T>
class WordBoard : public Board<T> {
private:
    unordered_set<string> dictionary;

public:
    WordBoard(const string& dict_file);
    ~WordBoard(); 
    bool update_board(int x, int y, T symbol);
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();
    bool check_word(const string& word);

    int get_moves() const; 
};


template <typename T>
class WordPlayer : public Player<T> {
public:
    WordPlayer(string name, T symbol);
    void getmove(int& x, int& y) override;
    T getsymbol() const ; 

private:
    T currentSymbol; 
};


template <typename T>
WordPlayer<T>::WordPlayer(string name, T symbol) : Player<T>(name, symbol), currentSymbol(symbol) {}


template <typename T>
void WordPlayer<T>::getmove(int& x, int& y) {
    cout << "\n" << this->getname() << ", enter your move coordinates (x y): ";
    cin >> x >> y;

    cout << "Enter the letter you want to place: ";
    cin >> currentSymbol;
    currentSymbol = toupper(currentSymbol); 
    this->symbol = currentSymbol; 
}


template <typename T>
T WordPlayer<T>::getsymbol() const {
    return currentSymbol;
}


template <typename T>
int WordBoard<T>::get_moves() const {
    return this->n_moves;
}



template <typename T>
WordBoard<T>::WordBoard(const string& dict_file) {
    static_assert(is_same<T, char>::value, "WordBoard can only be used with char type.");
    this->rows = this->columns = 3;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns]();
    }
    this->n_moves = 0;
    dictionary = load_dictionary(dict_file);
}


template <typename T>
WordBoard<T>::~WordBoard() {
    for (int i = 0; i < this->rows; i++) {
        delete[] this->board[i];
    }
    delete[] this->board;
}


template <typename T>
bool WordBoard<T>::update_board(int x, int y, T mark) {
     if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0|| mark == 0)) {
        if (mark == 0){
            this->n_moves--;
            this->board[x][y] = 0;
        }
        else {
            this->n_moves++;
            this->board[x][y] = toupper(mark);
        }

        return true;
    }
    return false;
}


template <typename T>
void WordBoard<T>::display_board() {
    for (int i = 0; i < this->rows; i++) {
        cout << "\n|";
        for (int j = 0; j < this->columns; j++) {
            cout << setw(3) << (this->board[i][j] ? this->board[i][j] : ' ') << " |";
        }
        cout << "\n" << string(6 * this->columns, '-');
    }
    cout << endl;
}


template <typename T>
bool WordBoard<T>::check_word(const string& word) {
    return dictionary.find(word) != dictionary.end();
}


template <typename T>
bool WordBoard<T>::is_win() {
    string word;

    // Check rows
    for (int i = 0; i < this->rows; i++) {
        word.clear();
        for (int j = 0; j < this->columns; j++) {
            if (this->board[i][j] == 0) break; 
            word += this->board[i][j];
        }
        if (check_word(word)) return true;
    }

    
    for (int j = 0; j < this->columns; j++) {
        word.clear();
        for (int i = 0; i < this->rows; i++) {
            if (this->board[i][j] == 0) break; 
            word += this->board[i][j];
        }
        if (check_word(word)) return true;
    }

    
    word.clear();
    for (int i = 0; i < this->rows; i++) {
        if (this->board[i][i] == 0) break;
        word += this->board[i][i];
    }
    if (check_word(word)) return true;

    word.clear();
    for (int i = 0; i < this->rows; i++) {
        if (this->board[i][this->columns - i - 1] == 0) break;
        word += this->board[i][this->columns - i - 1];
    }
    if (check_word(word)) return true;

    return false;
}


template <typename T>
bool WordBoard<T>::is_draw() {
    return this->n_moves == this->rows * this->columns && !is_win();
}

template <typename T>
bool WordBoard<T>::game_is_over() {
    return is_win() || is_draw();
}

template <typename T>
class RandomWordPlayer : public RandomPlayer<T> {
public:
    RandomWordPlayer(T symbol, int dim) : RandomPlayer<T>(symbol), dimension(dim) {
        srand(static_cast<unsigned>(time(0))); 
    }

    void getmove(int& x, int& y) override {
        x = rand() % dimension; 
        y = rand() % dimension; 
        this->symbol = generate_random_symbol(); 
     
    }

private:
    int dimension; 
    char generate_random_symbol() const {
        return 'A' + (rand() % 26); 
    }
};


#endif //_WORD_TICTACTOE_H
