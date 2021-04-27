#ifndef QUEEN
#define QUEEN

#include "ChessPiece.h"
#include "Rook.h"
#include "Bishop.h"

using std::vector;

class Queen : public Rook, public Bishop {

    protected:
        int validMove(int to_x, int to_y);
        char32_t utfRepresentation();
        char latin1Representation();

    public:
        Queen(ChessBoard* board, int x, int y, bool isWhite) : ChessPiece(board, x, y, isWhite), Rook(board, x, y, isWhite), Bishop(board, x, y, isWhite) {};
        vector<ChessMove> capturingMoves();
        vector<ChessMove> nonCapturingMoves();

        void testSetInt(int a);
        int getInt();

        ~Queen();
        
};

#endif // QUEEN