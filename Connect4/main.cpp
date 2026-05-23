#include <iostream>
#include "Board.h"
#include "HumanPlayer.h"
#include "ComputerPlayer.h"

int main() {
    bool playAgain = true;

    while (playAgain) {
        Board gameBoard;

        Player* player1 = new HumanPlayer("Player 1", 'X');
        Player* player2 = nullptr;

        char choice;
        std::cout << "Play against: \n1. Human\n2. Computer\nChoice: ";
        std::cin >> choice;

        if (choice == '1') {
            player2 = new HumanPlayer("Player 2", 'O');
        } else {
            player2 = new ComputerPlayer("Computer", 'O');
        }

        Player* currentPlayer = player1;
        bool gameOver = false;

        gameBoard.display();
        while (!gameOver) {
            int col = currentPlayer->getMove(gameBoard);
            int final_y = gameBoard.dropToken(col, currentPlayer->getToken());

            if (gameBoard.checkWin(col, final_y, currentPlayer->getToken())) {
                std::cout << "\n*** " << currentPlayer->getName() << " WINS! ***\n\n";
                gameOver = true;
            } else {
                currentPlayer = (currentPlayer == player1) ? player2 : player1;
            }
        }

        delete player1;
        delete player2;

        std::cout << "Play again? (y/n): ";
        char replay;
        std::cin >> replay;
        if (replay != 'y' && replay != 'Y') {
            playAgain = false;
        }
    }

    std::cout << "Thanks for playing!\n";
    return 0;
}