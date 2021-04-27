#ifndef LOOKAHEADAI
#define LOOKAHEADAI

#include "ChessBoard.h"

class LookaheadAI {

    private:
        ChessBoard& board;
        bool isWhite;

    public:
        LookaheadAI(ChessBoard& board, bool isWhite) : board(board), isWhite(isWhite) {};

        ChessMove makeMove();

};

#endif