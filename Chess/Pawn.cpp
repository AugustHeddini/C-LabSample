#include "Pawn.h"

int Pawn::validMove(int to_x, int to_y) {
    // Check for out of bounds
    if (to_x < 0 || to_x > 7 || to_y < 0 || to_y > 7) {
        return 0;
    }
    int colourMod = isWhite ? 1 : -1;
    // Check for capture
    if (abs(x - to_x) == 1 && to_y == y + 1 * colourMod) {
        if (board->occupied(to_x, to_y) - isWhite == 1) {
            return 2;
        }
    }
    // Check for move
    if (to_x == x && to_y == y + 1 * colourMod && board->occupied(to_x, to_y) == 0) {
        return 1;
    }
    // Check first move
    int startRow = isWhite ? 1 : 6;
    if (to_x == x && y == startRow && to_y == y + 2 * colourMod && board->occupied(to_x, to_y) == 0 && board->occupied(to_x, to_y - colourMod) == 0) {
        return 1;
    }
    return 0;
}

void Pawn::move(int to_x, int to_y) {
    if (to_x < 0 || to_x > 7 || to_y < 0 || to_y > 7) {
        throw std::out_of_range("Move indices out of bounds");
    }
    x = to_x;
    y = to_y;

    int oppositeEnd = isWhite ? 7 : 0;
    if (y == oppositeEnd) {
        board->ascendPawn(x, y);
    }

    return;
}

char32_t Pawn::utfRepresentation() {
    return isWhite ? U'\u2659' : U'\u265F';
}

char Pawn::latin1Representation() {
    return isWhite ? 'P' : 'p';
}

vector<ChessMove> Pawn::capturingMoves() {
    vector<ChessMove> res;
    int colourMod = isWhite ? 1 : -1;

    if (validMove(x - 1, y + colourMod) == 2) {
        res.push_back(ChessMove(x, y, x - 1, y + colourMod, this));
    }
    if (validMove(x + 1, y + colourMod) == 2) {
        res.push_back(ChessMove(x, y, x + 1, y + colourMod, this));
    }

    return res;
}

vector<ChessMove> Pawn::nonCapturingMoves() {
    vector<ChessMove> res;
    int colourMod = isWhite ? 1 : -1;

    if (validMove(x, y + colourMod) == 1) {
        res.push_back(ChessMove(x, y, x, y + colourMod, this));
    }
    if (validMove(x, y + 2 * colourMod) == 1) {
        res.push_back(ChessMove(x, y, x, y + 2 * colourMod, this));
    }

    return res;
}

Pawn::~Pawn() {}