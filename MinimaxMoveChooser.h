#pragma once

#include "BoardState.h"
#include <vector>
#include <algorithm>
#include <limits>

class MinimaxMoveChooser {
public:
	int getStaticEval(BoardState& boardState);
	std::vector<int> chooseMove(BoardState& boardState);
	int minimax(BoardState& boardState, int depth, int alpha, int beta);
	
private:
	int evaluation_table[8][8] = {
        {120, -20, 20, 5, 5, 20, -20, 120},
        {-20, -40, -5, -5, -5, -5, -40, -20},
        {20, -5, 15, 3, 3, 15, -5, 20},
        {5, -5, 3, 3, 3, 3, -5, 5},
        {5, -5, 3, 3, 3, 3, -5, 5},
        {20, -5, 15, 3, 3, 15, -5, 20},
        {-20, -40, -5, -5, -5, -5, -40, -20},
        {120, -20, 20, 5, 5, 20, -20, 120},
    };
};