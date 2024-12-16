#include <iostream>
#include "BoardGame_Classes.h"
#include "MinMaxPyramid.h"
#include "PyramidTicTacToe.h"

using namespace std;

int main() {
    int choice;
    Player<char>* players[2];
    PyramidBoard<char>* B = new PyramidBoard<char>();
    string player1Name, player2Name;

    cout << "Welcome to Pyramid Tic Tac Toe. :)\n";

    cout << "Enter Player 1 name: ";
    cin >> player1Name;
    cout << "Choose Player 1 type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cout << "3. Smart Computer (AI)\n";
    cin >> choice;

    switch(choice) {
        case 1:
            players[0] = new PyramidPlayer<char>(player1Name, 'X');
            break;
        case 2:
            players[0] = new PyramidRandom_Player<char>('X');
            break;
        case 3:
            players[0] = new PyramidMinMax_Player<char>('X');
            players[0]->setBoard(B);
            break;
        default:
            cout << "Invalid choice for Player 1. Exiting the game.\n";
            return 1;
    }

    cout << "Enter Player 2 name: ";
    cin >> player2Name;
    cout << "Choose Player 2 type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cout << "3. Smart Computer (AI)\n";
    cin >> choice;

    switch(choice) {
        case 1:
            players[1] = new PyramidPlayer<char>(player2Name, 'O');
            break;
        case 2:
            players[1] = new PyramidRandom_Player<char>('O');
            break;
        case 3:
            players[1] = new PyramidMinMax_Player<char>('O');
            players[1]->setBoard(B);
            break;
        default:
            cout << "Invalid choice for Player 2. Exiting the game.\n";
            return 1;
    }

    GameManager<char> Pyramidgame(B, players);
    Pyramidgame.run();


    delete B;
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }

    return 0;
}


