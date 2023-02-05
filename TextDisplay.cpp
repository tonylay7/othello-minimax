#include "TextDisplay.h"

void TextDisplay::refreshDisplay() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (boardState->getCell(i, j) == 0) boardDisplay[i][j] = '-';
            else if (boardState->getCell(i, j) == -1) boardDisplay[i][j] = 'b';
            else if (boardState->getCell(i, j) == 1) boardDisplay[i][j] = 'w';
        }
    }
    printDisplay(); // Show board
}

void TextDisplay::printDisplay() {
    std::cout << "   0  1  2  3  4  5  6  7\n";
    for (int i = 0; i < 8; ++i) {
        std::cout << (i) << "  ";
        for (int j = 0; j < 8; ++j) {
            std::cout << boardDisplay[i][j] << "  ";
        }
        std::cout << '\n';
    }
}