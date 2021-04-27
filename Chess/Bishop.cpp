#include "Bishop.h"
#include <stdlib.h>

int Bishop::validMove(int to_x, int to_y) {
    // Check for out of bounds
    if (to_x < 0 || to_x > 7 || to_y < 0 || to_y > 7 || to_x == x || to_y == y) {
        return 0;
    } else if (!(abs(x - to_x) == abs(y - to_y))) {
        return 0;
    }

    int loopModX = to_x > x ? 1 : -1;
    int loopModY = to_y > y ? 1 : -1;

    int loopCoordX = 0;
    int loopCoordY = 0;
    for(int i = 1; (x + loopModX*i < 8) && (x + loopModX*i > -1) && (y + loopModY*i < 8) && (y + loopModY > -1); i++) {
        loopCoordX = x + loopModX*i;
        loopCoordY = y + loopModY*i;

        if (board->occupied(loopCoordX, loopCoordY) != 0) {
            if (board->occupied(loopCoordX, loopCoordY) - isWhite == 1 && (loopCoordX == to_x && loopCoordY == to_y)) {
                return 2;
            } else {
                return 0;
            }
        }
        if (loopCoordX == to_x && loopCoordY == to_y) {
            return 1;
        }
    }

    return 0;
}

char32_t Bishop::utfRepresentation() {
    return isWhite ? U'\u2657' : U'\u265D';
}

char Bishop::latin1Representation() {
    return isWhite ? 'B' : 'b';
}

vector<ChessMove> Bishop::capturingMoves() {
    vector<ChessMove> res;

    for (int i = 1; i < 8; i++) {
        if (x + i < 8 && y + i < 8) {           // Up Right
            if (validMove(x + i, y + i) == 2) {
                res.push_back(ChessMove(x, y, x + i, y + i, this));
            }
        }
        if (x + i < 8 && y - i > -1) {          // Down Right
            if (validMove(x + i, y - i) == 2) {
                res.push_back(ChessMove(x, y, x + i, y - i, this));
            }
        }
        if (x - i > -1 && y + i < 8) {         // Up Left
            if (validMove(x - i, y + i) == 2) {
                res.push_back(ChessMove(x, y, x - i, y + i, this));
            }
        }
        if (x - i > -1 && y - i > -1) {        // Down Left
            if (validMove(x - i, y - i) == 2) {
                res.push_back(ChessMove(x, y, x - i, y - i, this));
            }
        }
    }

    return res;
}

vector<ChessMove> Bishop::nonCapturingMoves() {
    vector<ChessMove> res;

    for (int i = 1; i < 8; i++) {
        if (x + i < 8 && y + i < 8) {           // Up Right
            if (validMove(x + i, y + i) == 1) {
                res.push_back(ChessMove(x, y, x + i, y + i, this));
            }
        }
        if (x + i < 8 && y - i > -1) {          // Down Right
            if (validMove(x + i, y - i) == 1) {
                res.push_back(ChessMove(x, y, x + i, y - i, this));
            }
        }
        if (x - i > - 1 && y + i < 8) {         // Up Left
            if (validMove(x - i, y + i) == 1) {
                res.push_back(ChessMove(x, y, x - i, y + i, this));
            }
        }
        if (x - i > -1 && y - i > - 1) {        // Down Left
            if (validMove(x - i, y - i) == 1) {
                res.push_back(ChessMove(x, y, x - i, y - i, this));
            }
        }
    }

    return res;
}

Bishop::~Bishop() {}