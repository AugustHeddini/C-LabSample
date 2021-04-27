#include "Knight.h"
#include <stdlib.h>

int Knight::validMove(int to_x, int to_y) {
    // Check for out of bounds
    if (to_x < 0 || to_x > 7 || to_y < 0 || to_y > 7) {
        return 0;
    } else if (!((pow(abs(x - to_x), 2) + pow(abs(y - to_y), 2)) == 5)) {
        return 0;                                               // Out of bounds for Knight
    }

    if (board->occupied(to_x, to_y) == 0) {
        return 1;                                               // Non-capturing move
    } else if (board->occupied(to_x, to_y) - isWhite == 1) {
        return 2;                                               // Capturing move
    }

    return 0;
}

char32_t Knight::utfRepresentation() {
    return isWhite ? U'\u2658' : U'\u265E';
}

char Knight::latin1Representation() {
    return isWhite ? 'N' : 'n';
}

vector<ChessMove> Knight::capturingMoves() {
    vector<ChessMove> res;

    for (int i = -1; i < 2; i += 2) {
        for (int j = -1; j < 2; j += 2) {
            if (validMove(x + i, y + 2*j) == 2) {
                res.push_back(ChessMove(x, y, x + i, y + 2*j, this));
            }
            if (validMove(x + 2*i, y + j) == 2) {
                res.push_back(ChessMove(x, y, x + 2*i, y + j, this));
            }
        }
    }

    return res;
}

vector<ChessMove> Knight::nonCapturingMoves() {
    vector<ChessMove> res;

    for (int i = -1; i < 2; i += 2) {
        for (int j = -1; j < 2; j += 2) {
            if (validMove(x + i, y + 2*j) == 1) {
                res.push_back(ChessMove(x, y, x + i, y + 2*j, this));
            }
            if (validMove(x + 2*i, y + j) == 1) {
                res.push_back(ChessMove(x, y, x + 2*i, y + j, this));
            }
        }
    }

    return res;
}

Knight::~Knight() {}