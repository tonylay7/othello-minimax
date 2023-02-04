#pragma once

#include <vector>

class BoardState {
private:
	int _board[8][8] = {};

	bool checkOnBoard(int, int);
	int checkLeft(int, int);
	int checkRight(int, int);
	int checkUp(int, int);
	int checkDown(int, int);
	int checkUpLeft(int, int);
	int checkUpRight(int, int);
	int checkDownLeft(int, int);
	int checkDownRight(int, int);


public:
	int currentColour; // -1 if Black, 1 if White

	BoardState();
	std::vector<std::vector<int>> getLegalMoves();
	bool isGameOver();
	bool checkLegalMove(int, int);
	void makeLegalMove(int, int);
	BoardState* deepCopy();
	int getCell(int, int);
	void setCell(int, int, int);
	int getResult();
};
