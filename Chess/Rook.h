#ifndef ROOK
#define ROOK

#include "ChessPiece.h"

using std::vector;

class Rook : virtual public ChessPiece {

    protected:
        int validMove(int to_x, int to_y);
        char32_t utfRepresentation();
        char latin1Representation();

    public:
        Rook(ChessBoard* board, int x, int y, bool isWhite) : ChessPiece(board, x, y, isWhite) {};
        vector<ChessMove> capturingMoves();
        vector<ChessMove> nonCapturingMoves();

        ~Rook();
        
};

#endif // ROOK