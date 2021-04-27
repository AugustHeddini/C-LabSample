#include "Queen.h"
#include <stdlib.h>

int Queen::validMove(int to_x, int to_y) {
    // Check for out of bounds
    if (to_x < 0 || to_x > 7 || to_y < 0 || to_y > 7) {
        return 0;
    }

    int parentRes = Rook::validMove(to_x, to_y);
    if (parentRes != 0) {
        return parentRes;
    }
    parentRes = Bishop::validMove(to_x, to_y);
    if (parentRes != 0) {
        return parentRes;
    }

    return 0;
}

char32_t Queen::utfRepresentation() {
    return isWhite ? U'\u2655' : U'\u265B';
}

char Queen::latin1Representation() {
    return isWhite ? 'Q' : 'q';
}

vector<ChessMove> Queen::capturingMoves() {
    vector<ChessMove> res;
    vector<ChessMove> parentRes;

    parentRes = Rook::capturingMoves();
    res.insert(res.end(), parentRes.begin(), parentRes.end());

    parentRes = Bishop::capturingMoves();
    res.insert(res.end(), parentRes.begin(), parentRes.end());

    return res;
}

vector<ChessMove> Queen::nonCapturingMoves() {
    vector<ChessMove> res;
    vector<ChessMove> parentRes;

    parentRes = Rook::nonCapturingMoves();
    res.insert(res.end(), parentRes.begin(), parentRes.end());

    parentRes = Bishop::nonCapturingMoves();
    res.insert(res.end(), parentRes.begin(), parentRes.end());

    return res;
}

void Queen::testSetInt(int a) {
    Rook::unnecessaryInt = a;
}

int Queen::getInt() {
    return Bishop::unnecessaryInt;
}

Queen::~Queen() {}