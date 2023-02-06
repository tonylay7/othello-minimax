// Othello.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <iostream>
#include <sstream>
#include "BoardState.h"
#include "MinimaxMoveChooser.h"
#include "TextDisplay.h"

class Othello {
public:
	std::vector<int> parseInput(std::string input);
	bool checkInput(std:: string input);
	void printResult(BoardState*);
};
