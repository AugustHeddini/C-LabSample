#ifndef PAWN
#define PAWN

#include "ChessPiece.h"

using std::vector;

class Pawn : public ChessPiece {

    protected:
        int validMove(int to_x, int to_y);
        char32_t utfRepresentation();
        char latin1Representation();

    public:
        Pawn(ChessBoard* board, int x, int y, bool isWhite) : ChessPiece(board, x, y, isWhite) {};
        vector<ChessMove> capturingMoves();
        vector<ChessMove> nonCapturingMoves();

        void move(int to_x, int to_y);

        ~Pawn();
        
};

#endif // PAWN