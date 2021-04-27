#ifndef PIECE
#define PIECE

#include <vector>
#include "ChessBoard.h"

using std::vector;

class ChessPiece {
	friend void ChessBoard::move_piece(ChessMove p);

    protected:
        ChessBoard* board;
        int x,y;
        bool isWhite;
        /**
         * Returns 0 if target square is unreachable.
         * Returns 1 if target square is reachable and empty.
         * Returns 2 if move captures a piece.
         */
        virtual int validMove(int to_x, int to_y)=0;

    public:
        virtual char32_t utfRepresentation()=0;
        virtual char latin1Representation()=0;
        virtual void move(int to_x, int to_y);
        /**
         * Checks if this move is valid for this piece and captures
         * a piece of the opposite color.
         */
        bool capturingMove(int to_x, int to_y);
        /**
         * Checks if this move is valid but does not capture a piece.
         */
        bool nonCapturingMove(int to_x, int to_y);
        virtual vector<ChessMove> capturingMoves()=0;
        virtual vector<ChessMove> nonCapturingMoves()=0;
        bool colour();

        ChessPiece(ChessBoard* board, int x, int y, bool isWhite) : board(board), x(x), y(y), isWhite(isWhite) {};
        virtual ~ChessPiece() {};

		/**
		* For testing multiple inheritance
		*/
		int unnecessaryInt;
};

#endif // PIECE