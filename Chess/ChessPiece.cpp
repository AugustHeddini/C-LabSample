#include "ChessPiece.h"

bool ChessPiece::colour() {
    return isWhite;
}

bool ChessPiece::capturingMove(int to_x, int to_y) {
    return (validMove(to_x, to_y) == 2);
}

/**
 * Checks if this move is valid but does not capture a piece.
 */
bool ChessPiece::nonCapturingMove(int to_x, int to_y) {
    return (validMove(to_x, to_y) == 1);
}

void ChessPiece::move(int to_x, int to_y) {
    if (to_x < 0 || to_x > 7 || to_y < 0 || to_y > 7) {
        throw std::out_of_range("Move indices out of bounds");
    }
    x = to_x;
    y = to_y; 
    return;
}