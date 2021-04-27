#ifndef KING
#define KING

#include "ChessPiece.h"
#include "Rook.h"
#include "Bishop.h"

using std::vector;

class King : public ChessPiece {

    protected:
        int validMove(int to_x, int to_y);
        char32_t utfRepresentation();
        char latin1Representation();

    public:
        King(ChessBoard* board, int x, int y, bool isWhite) : ChessPiece(board, x, y, isWhite) {};
        vector<ChessMove> capturingMoves();
        vector<ChessMove> nonCapturingMoves();

        ~King();
};

#endif // KING