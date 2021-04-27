#ifndef BOARD
#define BOARD

#include <iostream>
#include <vector>
#include "Matrix.h"

// Forward declaration
class ChessPiece;

struct ChessMove {
    int from_x;
    int from_y;
    int to_x;
    int to_y;

    ChessPiece* piece;

    ChessMove(int from_x, int from_y, int to_x, int to_y, ChessPiece* piece) : from_x(from_x), from_y(from_y), to_x(to_x), to_y(to_y), piece(piece) {};
};

using std::vector;
using std::istream;

class ChessBoard {

    private:
        // 0 for human player, 1 for dumb AI player, 2 for smart AI player
        int aiPlayer;
        Matrix<ChessPiece*> state;
        vector<ChessPiece*> whites;
        vector<ChessPiece*> blacks;

        // Helper functions for the AI pawn ascend
        bool selectAscendAI(const char& pick, const int& x, const int& y, const bool& isWhite);
        char selectCharAI(const int& x, const int& y, const bool& isWhite);

    public:
        void move_piece(ChessMove chessmove);
        vector<ChessMove> capturingMoves(bool isWhite);
        vector<ChessMove> nonCapturingMoves(bool isWhite);

        // Populates the board with default piece placements
        void populate();
        void populate(const char* board);
        // Ascends a pawn at x,y which has reached the other end of the board
        void ascendPawn(const int& x, const int& y);
        // Returns 0 if not occupied, 1 is white, 2 if black
        int occupied(int x, int y);
        const Matrix<ChessPiece*> getState();
        ChessPiece* getPiece(int x, int y);
        void display_latin1();
        void display_utf8();

        // Returns 0 if White has won (there are no whites left)
        // Returns 1 if Black has won (there are no blacks left)
        // Returns -1 if neither side has won and 2 if both teams are empty (uninitialized)
        int isFinished();
        bool testMoveLosingChess(ChessMove& move, const bool isWhite);

        ChessBoard();
        ChessBoard(int aiPlayer);
        ~ChessBoard();
};

istream& operator >>(istream&, ChessBoard&);

#endif // BOARD