#ifndef RANDOMAI
#define RANDOMAI

#include "ChessBoard.h"

class RandomAI {

    private:
        ChessBoard& board;
        bool isWhite;

    public:
        RandomAI(ChessBoard& board, bool isWhite) : board(board), isWhite(isWhite) {};

        ChessMove makeMove();

};

#endif