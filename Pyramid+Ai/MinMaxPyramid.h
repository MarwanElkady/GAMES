
#ifndef _MINMAXPLAYER_H
#define _MINMAXPLAYER_H

#include "BoardGame_Classes.h"

template <typename T>
class PyramidMinMax_Player : public Player<T> {
public:
    PyramidMinMax_Player(T symbol);

    void getmove(int& x, int& y) override;

private:
    int calculateMinMax(T s, bool isMaximizing);
    pair<int, int> getBestMove();
};



#include <limits>
#include <algorithm> 
using namespace std;

template <typename T>
PyramidMinMax_Player<T>::PyramidMinMax_Player(T symbol) : Player<T>(symbol) {
    this->name = "AI Player";
}


template <typename T>
void PyramidMinMax_Player<T>::getmove(int& x, int& y) {
    pair<int, int> bestMove = getBestMove();
    x = bestMove.first;
    y = bestMove.second;
}



template <typename T>
int PyramidMinMax_Player<T>::calculateMinMax(T s, bool isMaximizing) {
    if (this->boardPtr->is_win()) {
        return isMaximizing ? -1 : 1;
    } else if (this->boardPtr->is_draw()) {
        return 0;
    }

    int bestValue = isMaximizing ? numeric_limits<int>::min() : numeric_limits<int>::max();
    T opponentSymbol = (s == 'X') ? 'O' : 'X';

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 5; ++j) {
            if (this->boardPtr->update_board(i, j, s)) {
                int value = calculateMinMax(opponentSymbol, !isMaximizing);
                this->boardPtr->update_board(i, j, 0); 

                if (isMaximizing) {
                    bestValue = max(bestValue, value);
                } else {
                    bestValue = min(bestValue, value);
                }
            }
        }
    }

    return bestValue;
}


template <typename T>
pair<int, int> PyramidMinMax_Player<T>::getBestMove() {
    int bestValue = numeric_limits<int>::min();
    pair<int, int> bestMove = {-1, -1};
    T opponentSymbol = (this->symbol == 'X') ? 'O' : 'X';

   
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 5; ++j) {
            if (this->boardPtr->update_board(i, j, this->symbol)) {
                if (this->boardPtr->is_win()) {
                    this->boardPtr->update_board(i, j, 0); 
                    return {i, j}; 
                }
                this->boardPtr->update_board(i, j, 0); 
            }
        }
    }

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 5; ++j) {
            if (this->boardPtr->update_board(i, j, opponentSymbol)) {
                if (this->boardPtr->is_win()) {
                    this->boardPtr->update_board(i, j, 0); 
                    return {i, j}; 
                }
                this->boardPtr->update_board(i, j, 0); 
            }
        }
    }

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 5; ++j) {
            if (this->boardPtr->update_board(i, j, this->symbol)) {
                int moveValue = calculateMinMax(this->symbol, false);
                this->boardPtr->update_board(i, j, 0); 

                if (moveValue > bestValue) {
                    bestMove = {i, j};
                    bestValue = moveValue;
                }
            }
        }
    }

    return bestMove;
}



#endif //_MINMAXPLAYER_H