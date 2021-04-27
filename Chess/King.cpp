#include "King.h"
#include <stdlib.h>
#include <stdio.h>

int King::validMove(int to_x, int to_y) {
    // Check for out of bounds
    if (to_x < 0 || to_x > 7 || to_y < 0 || to_y > 7) {
        return 0;
    } else if ( !((abs(x - to_x) * abs(y - to_y) == 1) || (abs(x - to_x) + abs(y - to_y) == 1)) ) {
        return 0;                                               // Out of reach for King
    }

    if (board->occupied(to_x, to_y) == 0) {
        return 1;                                               // Non-capturing move
    } else if (board->occupied(to_x, to_y) - isWhite == 1) {
        return 2;                                               // Capturing move
    }

    return 0;
}

char32_t King::utfRepresentation() {
    return isWhite ? U'\u2654' : U'\u265A';
}

char King::latin1Representation() {
    return isWhite ? 'K' : 'k';
}

vector<ChessMove> King::capturingMoves() {
    vector<ChessMove> res;

    for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
            if (i == 0 && j == 0) {
                continue;
            }
            if (validMove( x + i, y + j ) == 2) {
                res.push_back(ChessMove(x, y, x+i, y+j, this));
            }
        }
    }

    return res;
}

vector<ChessMove> King::nonCapturingMoves() {
    vector<ChessMove> res;

    for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
            if (i == 0 && j == 0) {
                continue;
            }
            if (validMove( x + i, y + j ) == 1) {
                res.push_back(ChessMove(x, y, x+i, y+j, this));
            }
        }
    }

    return res;
}

King::~King() {}