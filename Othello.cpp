// Othello.cpp : Defines the entry point for the application.
//

#include "Othello.h"


std::vector<int> parseInput(std::string input) {
    std::vector<int> move = {input[0] - '0',input[2] - '0'};
    std::cout << move[0] << std::endl;
    std::cout << move[1] << std::endl;
    return move;
}

bool checkInput(std::string input) {
    if (input.length() == 3) {
        if (isdigit(input[0]) && (input[1] = ',') && isdigit(input[2])) {
            int x = input[0] - '0';
            int y = input[0] - '0';
            if ((x < 8) && (y < 8) && (x >= 0) && (y >= 0)) return true;
        }
    }
    return false;
}
int main(){
    BoardState *currentState = new BoardState();
    currentState->setCell(3, 3, 1);
    currentState->setCell(3, 4, -1);
    currentState->setCell(4, 3, -1);
    currentState->setCell(4, 4, 1);
    currentState->currentColour = -1; // Black to start

    MinimaxMoveChooser *mc = new MinimaxMoveChooser();
    TextDisplay *textDisplay = new TextDisplay();
    textDisplay->boardState = currentState;

    // Loop until the game is over
    while (!currentState->isGameOver()) {
        textDisplay->refreshDisplay();

        std::vector<std::vector<int>> legalMoves = currentState->getLegalMoves();

        // If the player has no legal moves to make then swap the turn over to the AI, then the AI makes a move
        if (legalMoves.empty()) {
            if (currentState->currentColour == -1) std::cout << "You have no legal moves. It's the AI's turn." << std::endl;
            currentState->currentColour *= -1;

            // AI chooses a move and makes the move
            std::vector<int> move = mc->chooseMove(*currentState);
            if (!move.empty()) {
                currentState->makeLegalMove(move[0], move[1]);
                textDisplay->refreshDisplay();
            }
        }

        // The player has legal moves to make so allow them to make a move
        else {
            // Print the list of legal moves that the player can make
            for (std::vector<int> move : legalMoves) {
                std::cout << move[0] << ',';
                std::cout << move[1];
                std::cout << '\n';
            }

            // Prompt the user to a move
            if (currentState->currentColour == -1) {
                std::string coords;

                // Input validation to ensure the user enters the coordinates in the correct form
                while (true) {
                    std::cout << "It's your turn! Enter the coordinates of your move in the form x,y" << std::endl;
                    std::cin >> coords;
                    if (checkInput(coords)) {
                        // Check the move is legal
                        std::vector<int> move = parseInput(coords);
                        if (currentState->checkLegalMove(move[0], move[1])) {
                            currentState->makeLegalMove(move[0], move[1]);
                            textDisplay->refreshDisplay();
                        }
                        break;
                    }
                    else std::cout << "This input is not valid. Please try again." << std::endl;
                }

                // AI chooses a move and makes the move
                std::vector<int> move = mc->chooseMove(*currentState);
                if (!move.empty()) {
                    currentState->makeLegalMove(move[0], move[1]);
                    textDisplay->refreshDisplay();
                }
                // AI cannot move, so change back colour
                else {  
                    currentState->currentColour *= -1;
                    if (currentState->getLegalMoves().empty()) {  // Computer has no moves either game over
                        std::cout << "Game over: " << std::endl;
                        textDisplay->refreshDisplay();
                    }
                }
            }
        }
    }

    return 0;
}
