#include "BoardState.h"

BoardState::BoardState() {
};

// Get the currentColour of the cell at (x,y)
int BoardState::getCell(int x, int y) {
	return _board[x][y];
}

// Set the cell at (x,y) of the specified currentColour
void BoardState::setCell(int x, int y, int currentColour) {
	_board[x][y] = currentColour;
}

// Check if the game is over
bool BoardState::isGameOver() {

    bool gameOver = false;
    if (getLegalMoves().empty()) {
        currentColour = -currentColour; // change currentColour temporarily to check the legal moves
        if (getLegalMoves().empty())
            gameOver = true;
        currentColour = -currentColour; // change currentColour back
    }
    return gameOver;
}


// Check if the move made is legal
bool BoardState::checkLegalMove(int x, int y) {
    return
        checkOnBoard(x, y) && (getCell(x, y) == 0) &&
        ((checkLeft(x, y) != -1) || (checkRight(x, y) != -1) ||
            (checkUp(x, y) != -1) || (checkDown(x, y) != -1) ||
            (checkUpLeft(x, y) != -1) || (checkUpRight(x, y) != -1) ||
            (checkDownLeft(x, y) != -1) || (checkDownRight(x, y) != -1));
}

// Make a legal move and then switch the turn over to the other player
void BoardState::makeLegalMove(int x, int y) {

    int a, b = 0;

    // Squares to left
    a = checkLeft(x, y);
    if (a != -1)
        for (int i = x; i > a; i--)
            setCell(i, y, currentColour);

    // Squares to right
    a = checkRight(x, y);
    if (a != -1)
        for (int i = x; i < a; i++)
            setCell(i, y, currentColour);

    // Squares above
    a = checkUp(x, y);
    if (a != -1)
        for (int j = y; j > a; j--)
            setCell(x, j, currentColour);

    // Squares below
    a = checkDown(x, y);
    if (a != -1)
        for (int j = y; j < a; j++)
            setCell(x, j, currentColour);

    // Squares to above left
    a = checkUpLeft(x, y);
    if (a != -1)
        for (int i = x, j = y; i > a; i--, j--)
            setCell(i, j, currentColour);

    // Squares above right
    a = checkUpRight(x, y);
    if (a != -1)
        for (int i = x, j = y; i < a; i++, j--)
            setCell(i, j, currentColour);

    // Squares to below left
    a = checkDownLeft(x, y);
    if (a != -1)
        for (int i = x, j = y; i > a; i--, j++)
            setCell(i, j, currentColour);

    // Squares below right
    a = checkDownRight(x, y);
    if (a != -1)
        for (int i = x, j = y; i < a; i++, j++)
            setCell(i, j, currentColour);

    // Change player
    currentColour = -currentColour;
}


// Check if the move is on the board
bool BoardState::checkOnBoard(int x, int y) {
	return (x >= 0) && (x < 8) && (y >= 0) && (y < 8);
}

// Return the legal moves of the current player
std::vector<std::vector<int>> BoardState::getLegalMoves() {
	std::vector<std::vector<int>> legalMoves;
	// Iterate through every cell and check if the cell is legal
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			if (checkLegalMove(i, j)) {
				// Create a vector representation of the move and push it to the move list
				std::vector<int> move = {i, j};
				legalMoves.push_back(move);
			}
	return legalMoves;
}

// Return a deep copy of the current board state
BoardState *BoardState::deepCopy() {
	BoardState *newBoardState = new BoardState();
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			newBoardState->setCell(i, j, getCell(i, j));
	newBoardState->currentColour = currentColour;
	return newBoardState;
}

// Return largest value of i < x such that board[j][i] is opposite to currentColour for all
// j where (i < j < x) and board[i][y] is currentColour. Return -1 if none in range
int BoardState::checkLeft(int x, int y) {

    int i = x - 1;
    while ((i > 0) && (getCell(i, y) == -currentColour)) i--;
    if ((i < x - 1) && getCell(i, y) == currentColour) return i;
    else return -1;
}


// Return largest value of i > x such that board[j][i] is opposite to currentColour for all
// j where (i > j > x) and board[i][y] is currentColour. Return -1 if none in range
int BoardState::checkRight(int x, int y) {

    int i = x + 1;
    while ((i < 7) && (getCell(i, y) == -currentColour)) i++;
    if ((i > x + 1) && getCell(i, y) == currentColour) return i;
    else return -1;
}

// Return largest value of i < y such that board[x][j] is opposite to currentColour for all
// j where (i < j < y) and board[x][i] is currentColour. Return -1 if none in range
int BoardState::checkUp(int x, int y) {

    int i = y - 1;
    while ((i > 0) && (getCell(x, i) == -currentColour)) i--;
    if ((i < y - 1) && getCell(x, i) == currentColour) return i;
    else return -1;
}


// Return largest value of i > y such that board[x][j] is opposite to currentColour for all
// j where (i > j > y) and board[x][i] is currentColour. Return -1 if none in range
int BoardState::checkDown(int x, int y) {

    int i = y + 1;
    while ((i < 7) && (getCell(x, i) == -currentColour)) i++;
    if ((i > y + 1) && getCell(x, i) == currentColour) return i;
    else return -1;
}


// Return largest value of i < x such that board[x-j][y-j] is opposite to currentColour for all
// j where (i < j < endOfBoard) and board[i][y] is currentColour. Return -1 if none in range
int BoardState::checkUpLeft(int x, int y) {

    int i = x - 1;
    int j = y - 1;
    while ((i > 0) && (j > 0) && (getCell(i, j) == -currentColour)) {
        i--;
        j--;
    }
    if ((i < x - 1) && getCell(i, j) == currentColour) return i;
    else return -1;
}


// Return largest value of i > x such that board[j][i] is opposite to currentColour for all
// where j (i > j > x) and board[i][y] is currentColour. Return -1 if none in range
int BoardState::checkUpRight(int x, int y) {

    int i = x + 1;
    int j = y - 1;
    while ((i < 7) && (j > 0) && (getCell(i, j) == -currentColour)) { 
        i++;
        j--;
    }
    if ((i > x + 1) && getCell(i, j) == currentColour) return i;
    else return -1;
}



// Return largest value of i < x such that board[x-j][y-j] is opposite to currentColour for all
// where j (i < j < endOfBoard) and board[i][y] is currentColour. Return -1 if none in range
int BoardState::checkDownLeft(int x, int y) {

    int i = x - 1;
    int j = y + 1;
    while ((i > 0) && (j < 7) && (getCell(i, j) == -currentColour)) {
        i--;
        j++;
    }
    if ((i < x - 1) && getCell(i, j) == currentColour) return i;
    else return -1;
}


// Return largest value of i > x such that board[j][i] is opposite to currentColour for all
// where j (i > j > x) and board[i][y] is currentColour. Return -1 if none in range
int BoardState::checkDownRight(int x, int y) {

    int i = x + 1;
    int j = y + 1;
    while ((i < 7) && (j < 7) && (getCell(i, j) == -currentColour)) {
        i++;
        j++;
    }
    if ((i > x + 1) && getCell(i, j) == currentColour) return i;
    else return -1;
}

int BoardState::getResult() {
    int scores[2]{}; // white count then black count
    int white = 0;
    int black = 0;
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            if (getCell(i, j) == 1)
                white++;
            else if (getCell(i, j) == -1)
                black++;
    scores[0] = white;
    scores[1] = black;
    return scores[0] - scores[1];
}
