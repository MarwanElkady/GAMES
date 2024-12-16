#include <iostream>
#include "FiveByFive.h"
#include "ReverseTicTacToe.h"

using namespace std;

int main()
{

    int choice;
    bool playAgain = true;

    while (playAgain)
    {
        cout << "Welcome to the Ultimate Board Game Collection!" << endl;
        cout << "Choose a game to play:" << endl;
        cout << "1. Five-by-Five Tic Tac Toe" << endl;
        cout << "2. Reverse Tic Tac Toe" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Please enter a number between 1 and 8." << endl;
            continue;
        }

        if (choice == 1)
        {
            FiveByFiveBoard board;

            cout << "Choose game mode:\n";
            cout << "1. Player vs Player\n";
            cout << "2. Player vs Computer\n";
            cout << "3. Computer vs Computer\n";
            int choice;
            cin >> choice;

            Player<char> *player2;
            Player<char> *player1;

            if (choice == 1)
            {
                player1 = new FiveByFivePlayer("Player 1", 'X');
                player2 = new FiveByFivePlayer("Player 2", 'O');
            }
            else if (choice == 2)
            {
                player2 = new FiveByFiveRandomPlayer('O');
                player1 = new FiveByFivePlayer("Player 1", 'X');
            }
            else
            {

                player1 = new FiveByFiveRandomPlayer('X');
                player2 = new FiveByFiveRandomPlayer('O');
            }

            Player<char> *players[2] = {player1, player2};

            player1->setBoard(&board);
            player2->setBoard(&board);

            GameManager<char> gameManager(&board, players);

            gameManager.run();

            board.determine_winner();

            if (choice == 2)
            {
                delete player2;
            }
        }
        else if (choice == 2)
        {
            cout << "Welcome to Reverse Tic Tac Toe!" << endl;
            cout << "Choose game mode:\n";
            cout << "1. Player vs Player\n";
            cout << "2. Player vs Computer\n";
            cout << "3. Computer vs Computer\n";

            int choice;
            cin >> choice;

            while (choice < 1 || choice > 3)
            {
                cout << "Invalid choice. Please choose again (1, 2, or 3): ";
                cin >> choice;
            }

            TicTacToeInverse board;

            Player<char> *player1 = nullptr;
            Player<char> *player2 = nullptr;

            if (choice == 1)
            {
                player1 = new InversePlayer("Player 1", 'X');
                player2 = new InversePlayer("Player 2", 'O');
            }
            else if (choice == 2)
            {
                player1 = new InversePlayer("Player 1", 'X');
                player2 = new InverseRandom('O');
            }
            else if (choice == 3)
            {
                player1 = new InverseRandom('X');
                player2 = new InverseRandom('O');
            }

            Player<char> *players[2] = {player1, player2};

            player1->setBoard(&board);
            player2->setBoard(&board);

            GameManager<char> gameManager(&board, players);

            gameManager.run();

            delete player1;
            delete player2;

            cout << "Thanks for playing Reverse Tic Tac Toe!" << endl;
        }
        else
        {
            cout << "Invalid choice. Exiting program." << endl;
            continue;
        }

        char playAgainChoice;
        while (true)
        {
            cout << "\nDo you want to play another game? (y/n): ";
            cin >> playAgainChoice;

            if (playAgainChoice == 'y' || playAgainChoice == 'Y')
            {
                playAgain = true;
                break;
            }
            else if (playAgainChoice == 'n' || playAgainChoice == 'N')
            {
                playAgain = false;
                cout << "\nThank you for playing! Goodbye!" << endl;
                break;
            }
            else
            {
                cout << "Invalid input! Please enter 'y' or 'n'." << endl;
            }
        }
    }

    return 0;
}