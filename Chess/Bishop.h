#ifndef BISHOP
#define BISHOP

#include "ChessPiece.h"

using std::vector;

class Bishop : virtual public ChessPiece {

    protected:
        int validMove(int to_x, int to_y);
        char32_t utfRepresentation();
        char latin1Representation();

    public:
        Bishop(ChessBoard* board, int x, int y, bool isWhite) : ChessPiece(board, x, y, isWhite) {};
        vector<ChessMove> capturingMoves();
        vector<ChessMove> nonCapturingMoves();

        ~Bishop();
        
};

#endif // BISHOP