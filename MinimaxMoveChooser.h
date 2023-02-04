#pragma once

#include <vector>
#include "BoardState.h"
#include <algorithm>
#include <limits>

class MinimaxMoveChooser {
public:
	int getStaticEval(BoardState boardState);
	int minimax(BoardState boardState, int depth, int alpha, int beta);
	std::vector<int> chooseMove(BoardState boardState);
private:
	int evaluation_table[8][8];

}
