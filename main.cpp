#include <iostream>
#include "FiveByFive.h"
#include "ReverseTicTacToe.h"
#include "PyramidTicTacToe.h" 
#include "wordtictactoe.h"
#include "ConnectFour.h"  
#include "NumericalGame.h" 


using namespace std;

int main()
{
    
    int choice;
    bool playAgain = true;

    while (playAgain) {
        cout << "Welcome to the Ultimate Board Game Collection!" << endl;
        cout << "Choose a game to play:" << endl;
        cout << "1. Five-by-Five Tic Tac Toe" << endl;
        cout << "2. Reverse Tic Tac Toe" << endl;
        cout << "3. Pyramid Tic Tac Toe" << endl;
        cout << "4. Word Tic Tac Toe" << endl;
        cout << "5. Numerical Tic Tac Toe" << endl;
        cout << "6. Connect Four" << endl; 
        cout << "7. Ultimate Tic Tac Toe" << endl;
        cout << "8. SUS game" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        if (cin.fail()) {
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

                else if (choice == 3)
        {
            int choice;
            Player<char>* players[2];
            PyramidBoard<char>* B = new PyramidBoard<char>();
            string player1Name, player2Name;

            cout << "Welcome to Pyramid Tic Tac Toe !\n";

            cout << "\nEnter Player 1 name: ";
            cin >> player1Name;
            cout << "\nChoose Player 1 type:\n";
            cout << "1. Human\n";
            cout << "2. Random Computer\n";
            cin >> choice;

            switch(choice) {
                case 1:
                    players[0] = new PyramidPlayer<char>(player1Name, 'X');
                    break;
                case 2:
                    players[0] = new PyramidRandom_Player<char>('X');
                    break;
                default:
                    cout << "Invalid choice for Player 1. Exiting the game.\n";
                    return 1;
            }

            cout << "\nEnter Player 2 name: ";
            cin >> player2Name;
            cout << "\nChoose Player 2 type:\n";
            cout << "1. Human\n";
            cout << "2. Random Computer\n";
            cin >> choice;

            switch(choice) {
                case 1:
                    players[1] = new PyramidPlayer<char>(player2Name, 'O');
                    break;
                case 2:
                    players[1] = new PyramidRandom_Player<char>('O');
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

        }
        else if (choice == 4)
        {

            string dictionary_file = "dic.txt";
            WordBoard<char> board(dictionary_file);

            string player1_name, player2_name;
            char player1_symbol = 'X'; 
            char player2_symbol = 'O'; 
            int player2_type, player1_type;

            cout << "\nWelcome to Word Tic Tac Toe! \n";


            while (true) {
                cout << "\nChoose Player 1 type (1 for Human, 2 for Random): ";
                cin >> player1_type;

                if (cin.fail() || (player1_type != 1 && player1_type != 2)) {
                    cin.clear(); 
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                    cout << "Invalid input! Please enter 1 for Human or 2 for Random.\n";
                } else {
                    break; 
                }
            }

            if (player1_type == 1) {
                cout << "\nEnter Player 1's name: ";
                cin >> player1_name;
            }


            while (true) {
                cout << "\nChoose Player 2 type (1 for Human, 2 for Random): ";
                cin >> player2_type;

                if (cin.fail() || (player2_type != 1 && player2_type != 2)) {
                    cin.clear(); 
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                    cout << "Invalid input! Please enter 1 for Human or 2 for Random.\n";
                } else {
                    break; 
                }
            }

            if (player2_type == 1) {
                cout << "\nEnter Player 2's name: ";
                cin >> player2_name;
            }

            Player<char>* player1;
            Player<char>* player2;

            if (player1_type == 1) {
                player1 = new WordPlayer<char>(player1_name, player1_symbol);
            } else {
                player1 = new RandomWordPlayer<char>('A', 3); 
            }

            if (player2_type == 1) {
                player2 = new WordPlayer<char>(player2_name, player2_symbol);
            } else {
                player2 = new RandomWordPlayer<char>('A', 3); 
            }


            player1->setBoard(&board);
            player2->setBoard(&board);


            Player<char>* players[2] = {player1, player2};

            GameManager<char> Wordgame(&board, players);

            cout << "\nStarting Word Tic-Tac-Toe! Players will enter coordinates (x, y) and letters.\n";
            cout << "To win, form a valid word from the dictionary in a row, column, or diagonal.\n";

            Wordgame.run();

            cout << "\nGame Over! Thanks for playing!\n";

            delete player1;
            delete player2;


        }
        else if (choice == 5)
        {
            NumericalBoard<int>* board = new NumericalBoard<int>();
            Player<int>* players[2];
            char choice;

            while (true) {
                cout << "Choose Player 1 (h for human, r for random): ";
                cin >> choice;
                if (choice == 'h' || choice == 'H') {
                    players[0] = new NumericalPlayer<int>("Player 1", {1, 3, 5, 7, 9});
                    break;
                } else if (choice == 'r' || choice == 'R') {
                    players[0] = new NumericalRandomPlayer<int>(0, {1, 3, 5, 7, 9});
                    break;
                } else {
                    cout << "Invalid choice. Please enter 'h' for human or 'r' for random." << endl;
                }
            }


            while (true) {
                cout << "Choose Player 2 (h for human, r for random): ";
                cin >> choice;
                if (choice == 'h' || choice == 'H') {
                    players[1] = new NumericalPlayer<int>("Player 2", {2, 4, 6, 8});
                    break;
                } else if (choice == 'r' || choice == 'R') {
                    players[1] = new NumericalRandomPlayer<int>(0, {2, 4, 6, 8});
                    break;
                } else {
                    cout << "Invalid choice. Please enter 'h' for human or 'r' for random." << endl;
                }
            }


            players[0]->setBoard(board);
            players[1]->setBoard(board);

 
            GameManager<int> gameManager(board, players);
            cout << "Welcome to Numerical Tic-Tac-Toe!" << endl;
            gameManager.run();


            delete players[0];
            delete players[1];
            delete board;

            return 0;
        }
        else if (choice == 6) 
        {
            ConnectFourBoard<char>* board = new ConnectFourBoard<char>();

            Player<char>* players[2];
            char choice;

            while (true) {
                cout << "Choose Player 1 (h for human, r for random): ";
                cin >> choice;
                if (choice == 'h' || choice == 'H') {
                    players[0] = new ConnectFourPlayer<char>("Player 1", 'X');
                    break;
                } else if (choice == 'r' || choice == 'R') {
                    players[0] = new ConnectFourRandomPlayer<char>('X');
                    break;
                } else {
                    cout << "Invalid choice. Please enter 'h' for human or 'r' for random." << endl;
                }
            }

            while (true) {
                cout << "Choose Player 2 (h for human, r for random): ";
                cin >> choice;
                if (choice == 'h' || choice == 'H') {
                    players[1] = new ConnectFourPlayer<char>("Player 2", 'O');
                    break;
                } else if (choice == 'r' || choice == 'R') {
                    players[1] = new ConnectFourRandomPlayer<char>('O');
                    break;
                } else {
                    cout << "Invalid choice. Please enter 'h' for human or 'r' for random." << endl;
                }
            }

            players[0]->setBoard(board);
            players[1]->setBoard(board);

            GameManager<char> gameManager(board, players);
            gameManager.run();

            delete players[0];
            delete players[1];
            delete board;
        }
        else
        {
            cout << "Invalid choice. Exiting program." << endl;
            continue;
        }

    char playAgainChoice;
            while (true) {
                cout << "\nDo you want to play another game? (y/n): ";
                cin >> playAgainChoice;

                if (playAgainChoice == 'y' || playAgainChoice == 'Y') {
                    playAgain = true;
                    break;
                } else if (playAgainChoice == 'n' || playAgainChoice == 'N') {
                    playAgain = false;
                    cout << "\nThank you for playing! Goodbye!" << endl;
                    break;
                } else {
                    cout << "Invalid input! Please enter 'y' or 'n'." << endl;
                }
            }
    }

    return 0;
}