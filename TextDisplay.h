#pragma once

#include <vector>
#include "BoardState.h"
#include <iostream>

class TextDisplay {
public:
	BoardState* boardState;
	char boardDisplay[8][8];
	int currentColour;

	void refreshDisplay();
	void printDisplay();
};
