#ifndef _3X5_O_H
#define _3X5_O_H
#include <iostream>
#include <iomanip>
#include <limits>
#include <cstdlib>
#include <ctime>

template <typename T>
class PyramidBoard:public Board<T> {
public:
    PyramidBoard ();
    bool update_board (int x , int y , T symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();

};

template <typename T>
class PyramidPlayer : public Player<T> {
public:
    PyramidPlayer (string name, T symbol);
    void getmove(int& x, int& y) ;

};

template <typename T>
class PyramidRandom_Player : public RandomPlayer<T>{
public:
    PyramidRandom_Player (T symbol);
    void getmove(int &x, int &y) ;
};

//--------------------------------------- IMPLEMENTATION

#include <iostream>
#include <iomanip>
#include <cctype>  

using namespace std;


template <typename T>
PyramidBoard<T>::PyramidBoard() {
    this->rows = 3;  
    this->columns = 5;  
    int total_cells = 0;
    this->board = new T*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new T[2 * i + 1];
        for (int j = 0; j < (2 * i + 1); j++) {
            this->board[i][j] = 0;
            total_cells++;
        }
    }
    this->n_moves = 0;
}

template <typename T>
bool PyramidBoard<T>::update_board(int x, int y, T mark) {
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
void PyramidBoard<T>::display_board() {
    cout << "\nCurrent Board:\n";
    for (int i = 0; i < this->rows; i++) {
        
        int spaces = (this->rows - i - 1) * 7; 
        cout << string(spaces, ' ');

        
        for (int j = 0; j < (2 * i + 1); j++) {
            cout << "[" << i << "," << j << " "<< (this->board[i][j] == 0 ? ' ' : this->board[i][j]) << "]";
        }
        cout << endl;
    }
}



template <typename T>
bool PyramidBoard<T>::is_win() {
    

    if (this->board[0][0] != 0 &&
        this->board[0][0] == this->board[1][0] &&
        this->board[1][0] == this->board[2][0]) {
        return true;
    }

  
    if (this->board[0][0] != 0 &&
        this->board[0][0] == this->board[1][2] &&
        this->board[1][2] == this->board[2][4]) {
        return true;
    }

    if (this->board[0][0] != 0 &&
        this->board[0][0] == this->board[1][1] &&
        this->board[1][1] == this->board[2][2]) {
        return true;
    }

    if (this->board[1][0] != 0 &&
        this->board[1][0] == this->board[1][1] &&
        this->board[1][1] == this->board[1][2]) {
        return true;
    }

  
    if (this->board[2][0] != 0 &&
        this->board[2][0] == this->board[2][1] &&
        this->board[2][1] == this->board[2][2]) {
        return true;
    }

    if (this->board[2][1] != 0 &&
        this->board[2][1] == this->board[2][2] &&
        this->board[2][2] == this->board[2][3]) {
        return true;
    }

    if (this->board[2][2] != 0 &&
        this->board[2][2] == this->board[2][3] &&
        this->board[2][3] == this->board[2][4]) {
        return true;
    }

    return false; 
}



template <typename T>
bool PyramidBoard<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

template <typename T>
bool PyramidBoard<T>::game_is_over() {
    return is_win() || is_draw();
}


template <typename T>
PyramidPlayer<T>::PyramidPlayer(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void PyramidPlayer<T>::getmove(int& x, int& y) {
    cout <<Player<T>::name << "(" << Player<T>::symbol << ") Please enter your move x and y (0 to 2) separated by spaces: ";
    cin >> x >> y;
    while (cin.fail() || x < 0 || x >= 3 || y < 0 || y >= 5) {  
        cin.clear();  // clear the fail state
        cin.ignore(numeric_limits<streamsize>::max(), '\n');  
        cout << "Invalid move, try again: ";
        cin >> x >> y;
    }
}

template <typename T>
PyramidRandom_Player<T>::PyramidRandom_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension =  5;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  
}

template <typename T>
void PyramidRandom_Player<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;  
    y = rand() % this->dimension;
}

#endif //_3X5_O_H
