// Othello.cpp : Defines the entry point for the application.
//

#include "Othello.h"

using namespace std;

int main(){
    BoardState *initialState = new BoardState();
    initialState->setCell(3, 3, 1);
    initialState->setCell(3, 4, -1);
    initialState->setCell(4, 3, -1);
    initialState->setCell(4, 4, 1);
    initialState->currentColour = -1; // Black to start

    MinimaxMoveChooser *mc = new MinimaxMoveChooser();

    TextDisplay *textDisplay = new TextDisplay();
    textDisplay->boardState = initialState;
    textDisplay->refreshDisplay();
    return 0;
}
