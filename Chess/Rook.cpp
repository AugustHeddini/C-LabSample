#include "Rook.h"

int Rook::validMove(int to_x, int to_y) {
    // Check for out of bounds
    if (to_x < 0 || to_x > 7 || to_y < 0 || to_y > 7) {
        return 0;
    } else if (!((to_x == x) ^ (to_y == y))) {
        return 0;
    }
    int loopMod;

    if (y == to_y) {
        loopMod = to_x > x ? 1 : -1;
        for (int i = x + loopMod; i < 8 && i >= 0; i+= loopMod) {
            if (board->occupied(i, y) != 0) {
                if (board->occupied(i, y) - isWhite == 1 && i == to_x) {
                    return 2;                                               // This is a capturing move
                } else {
                    return 0;                                               // There is apiece in the way of this move
                }
            }
            if (i == to_x) {
                return 1;                                                   // This is a non-capturing move
            }
        }
    }

    if (x == to_x) {
        loopMod = to_y > y ? 1 : -1;
        for (int i = y + loopMod; i < 8 && i >= 0; i+= loopMod) {
            if (board->occupied(x, i) != 0) {
                if (board->occupied(x, i) - isWhite == 1 && i == to_y) {
                    return 2;                                               // This is a capturing move
                } else {
                    return 0;                                               // There is a piece in the way of this move
                }
            }
            if (i == to_y) {
                return 1;                                                   // This is a non-capturing move
            }
        }
    }

    return 0;
}

char32_t Rook::utfRepresentation() {
    return isWhite ? U'\u2656' : U'\u265C';
}

char Rook::latin1Representation() {
    return isWhite ? 'R' : 'r';
}

vector<ChessMove> Rook::capturingMoves() {
    vector<ChessMove> res;

    // X direction
    for (int i = 0; i < 8; i++) {
        if (validMove(i, y) == 2) {
            res.push_back(ChessMove(x, y, i, y, this));
        }
    }

    // Y direction
    for (int i = 0; i < 8; i++) {
        if (validMove(x, i) == 2) {
            res.push_back(ChessMove(x, y, x, i, this));
        }
    }

    return res;
}

vector<ChessMove> Rook::nonCapturingMoves() {
     vector<ChessMove> res;

    int valMove;
    // X direction
    for (int i = 0; i < 8; i++) {
        valMove = validMove(i, y);
        if (valMove == 1) {
            res.push_back(ChessMove(x, y, i, y, this));
        }
    }

    // Y direction
    for (int i = 0; i < 8; i++) {
        valMove = validMove(x, i);
        if (valMove == 1) {
            res.push_back(ChessMove(x, y, x, i, this));
        }
    }

    return res;
}

Rook::~Rook() {}


/* 
bool n = 1;
    bool e = 1;
    bool s = 1; 
    bool w = 1;
    int vMove = 0;
    for (int i = 0; i < 8; i++) {
        // Check north
        if (n && y + i < 8) {
            vMove = validMove(x, y + i);
            if (vMove == 2) {
                res.push_back(ChessMove(x, y, x, y + i, this));
                n = 0;
            } else if (vMove == 0) {
                n = 0;
            }
        }

        // Check East
        if (e && x + i < 8) {
            vMove = validMove(x + i, y);
            if (vMove == 2) {
                res.push_back(ChessMove(x, y, x + i, y, this));
                e = 0;
            } else if (vMove == 0) {
                e = 0;
            }
        }

        // Check South
        if (s && y - i >= 0) {
            vMove = validMove(x, y - i);
            if (vMove == 2) {
                res.push_back(ChessMove(x, y, x, y - i, this));
                s = 0;
            } else if (vMove == 0) {
                s = 0;
            }
        }

        //Check West
        if (w && x - i >= 0) {
            vMove = validMove(x - 1, y);
            if (vMove == 2) {
                res.push_back(ChessMove(x, y, x - 1, y, this));
                w = 0;
            } else if (vMove == 0) {
                w = 0;
            }
        }

    }
    */