#include "MinimaxMoveChooser.h"

// Calculate the static evaluation of a given state (in maximising player's perspective)
int MinimaxMoveChooser::getStaticEval(BoardState& boardState) {
    int currentEval = 0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (boardState.getCell(i, j) == 1) {
                currentEval += evaluation_table[i][j];
            }
            if (boardState.getCell(i, j) == -1) {
                currentEval -= evaluation_table[i][j];
            }
        }
    }
    return currentEval;
}

// Minimax algorithm with alpha beta pruning
int MinimaxMoveChooser::minimax(BoardState& boardState, int depth, int alpha, int beta) {
    std::vector<std::vector<int>> legalMoves = boardState.getLegalMoves();
    if (depth == 0 || boardState.isGameOver() == true) {
        return getStaticEval(boardState);
    }
    // Calculations made assuming that maximising player has to move
    if (boardState.currentColour == 1) {
        int maxEval = std::numeric_limits<int>::min(); // Placeholder for negative infinity
        if (legalMoves.empty()) { // If there are no legal moves then just swap the turns and calculate minimax from there
            boardState.currentColour *= -1;
            int currentEval = minimax(boardState, depth - 1, alpha, beta);
            maxEval = std::max(maxEval, currentEval);
            alpha = std::max(alpha, currentEval);
        }
        else {
            for (std::vector<int> move : legalMoves) {
                BoardState* boardStateNext = boardState.deepCopy();
                boardStateNext->makeLegalMove(move[0], move[1]);
                int currentEval = minimax(*boardStateNext, depth - 1, alpha, beta);
                maxEval = std::max(maxEval, currentEval);
                alpha = std::max(alpha, currentEval);
                if (alpha >= beta) // Stop processing the current state when alpha becomes greater than or equal to beta (pruning)
                    break;
            }
        }
        return maxEval;
    }
    // Calculations made assuming that minimising player has to move
    else {
        int minEval = std::numeric_limits<int>::max(); // Placeholder for positive infinity
        if (legalMoves.empty()) { // If there are no legal moves then just swap the turns and calculate minimax from there
            boardState.currentColour *= -1;
            int currentEval = minimax(boardState, depth - 1, alpha, beta);
            minEval = std::max(minEval, currentEval);
            beta = std::max(beta, currentEval);
        }
        else {
            for (std::vector<int> move : legalMoves) {
                BoardState* boardStateNext = boardState.deepCopy();
                boardStateNext->makeLegalMove(move[0], move[1]);
                int currentEval = minimax(*boardStateNext, depth - 1, alpha, beta);
                minEval = std::min(minEval, currentEval);
                beta = std::min(beta, currentEval);
                if (alpha >= beta) // Stop processing the current state when alpha becomes greater than or equal to beta (pruning)
                    break;
            }
        }
        return minEval;
    }
}
// Choice of move is made by comparing all minimax values of the possible moves available and selecting the best move for white
std::vector<int> MinimaxMoveChooser::chooseMove(BoardState& boardState){
    int searchDepth = 5;
    std::vector<int> bestMove;
    std::vector<std::vector<int>> legalMoves = boardState.getLegalMoves();
    if (legalMoves.empty()) return bestMove;
    int bestMoveValue = std::numeric_limits<int>::min(); // Placeholder for negative infinity
    for (std::vector<int> move : legalMoves) {
        BoardState* boardStateNext = boardState.deepCopy();
        boardStateNext->makeLegalMove(move[0], move[1]);
        int moveValue = minimax(*boardStateNext, searchDepth - 1, std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
        if (moveValue > bestMoveValue) { // Sift out the weakest moves, leaving with the best move on top
            bestMove = move;
            bestMoveValue = moveValue;
        }
    }
    return bestMove;
}