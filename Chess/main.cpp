#ifndef MAIN_HEADER
#define MAIN_HEADER

#include <iostream>
#include "ChessBoard.h"
#include "ChessPiece.h"
#include "Queen.h"
#include "RandomAI.h"
#include "LookaheadAI.h"

using namespace std;

void play(ChessBoard& board) {
    srand(time(nullptr));
    LookaheadAI player1 = LookaheadAI(board, true);
    LookaheadAI player2 = LookaheadAI(board, false);

    cout << "BEGINNING AI PLAYER MATCH!" << endl;

    board.display_utf8();
    rand();

    int turn = 0;
    while ( board.isFinished() == -1 ) {
        if ( turn % 2 == 0 ) {
            board.move_piece(player1.makeMove());
        } else {
            board.move_piece(player2.makeMove());
        }
        turn++;
        board.display_utf8();
    }
    //board.display_utf8();

    cout << "FINISHED AI PLAYER MATCH!" << endl;
    cout << ((board.isFinished() == 0) ? "White" : "Black") << " has WON! They lost all their pieces first!" << endl;  

}

int main(int argc, char* argv[]) {

    ChessBoard board = ChessBoard(2);

    // QUEEN TEST
    // Queen* q = new Queen(&board, 0, 0, true);
    // q->testSetInt(42);
    // cout << q->getInt() << endl;

    board.populate();

    play(board);
    return 0;       // Run only AI tests

    cout << "Construction complete" << endl;
    cout << "Expected 0: " << board.occupied(0, 0) << endl;
    cout << "Expected 1: " << board.occupied(0, 1) << endl;
    cout << "Expected 2: " << board.occupied(4, 6) << endl;

    cout << endl;

    vector<ChessMove> caps;

    board.display_utf8();

    // caps = board.capturingMoves(1);
    // for (u_int i = 0; i < caps.size(); i++) {
    //     cout << "White move at " << caps[i].from_x << ", " << caps[i].from_y << " to " << caps[i].to_x << ", " << caps[i].to_y << std::endl;
    // }
    // caps = board.capturingMoves(0);
    // for (u_int i = 0; i < caps.size(); i++) {
    //     cout << "Black move at " << caps[i].from_x << ", " << caps[i].from_y << " to " << caps[i].to_x << ", " << caps[i].to_y << std::endl;
    // }

    board.move_piece(ChessMove(0, 6, 2, 2, board.getPiece(0, 6)));
    board.display_utf8();
    caps = board.capturingMoves(1);
    for (u_int i = 0; i < caps.size(); i++) {
        cout << "White move at " << caps[i].from_x << ", " << caps[i].from_y << " to " << caps[i].to_x << ", " << caps[i].to_y << std::endl;
    }
    // caps = board.capturingMoves(0);
    // for (u_int i = 0; i < caps.size(); i++) {
    //     cout << "Black move at " << caps[i].from_x << ", " << caps[i].from_y << " to " << caps[i].to_x << ", " << caps[i].to_y << std::endl;
    // }
    // caps = board.capturingMoves(1);
    // for (u_int i = 0; i < caps.size(); i++) {
    //     cout << "White move at " << caps[i].from_x << ", " << caps[i].from_y << " to " << caps[i].to_x << ", " << caps[i].to_y << std::endl;
    // }

    board.move_piece(ChessMove(1, 1, 2, 2, board.getPiece(1, 1)));
    board.move_piece(ChessMove(0, 1, 4, 4, board.getPiece(0, 1)));
    board.move_piece(ChessMove(3, 0, 3, 5, board.getPiece(4, 0)));
    
    board.display_utf8();

    caps = board.capturingMoves(1);

    for (u_int i = 0; i < caps.size(); i++) {
        cout << "White move at " << caps[i].from_x << ", " << caps[i].from_y << " to " << caps[i].to_x << ", " << caps[i].to_y << std::endl;
    }
    // caps = board.capturingMoves(0);
    // for (u_int i = 0; i < caps.size(); i++) {
    //     cout << "Black move at " << caps[i].from_x << ", " << caps[i].from_y << " to " << caps[i].to_x << ", " << caps[i].to_y << std::endl;
    // }

    cout << "\nRUNNING iSTREAM TESTS\n" << endl;

    stringstream s;
    s << "........" << endl;
    s << ".......P" << endl;
    s << "........" << endl;
    s << "........" << endl;
    s << "........" << endl;
    s << "Q.P..pp." << endl;
    s << ".....PPP" << endl;
    s << "......NR";
    s >> board;

    board.display_utf8();

    caps = board.capturingMoves(1);
    cout << "Found " << caps.size() << " moves for white!" << endl;

    caps = board.capturingMoves(0);
    cout << "Found " << caps.size() << " moves for black!" << endl;

    cout << "\nTest AscendPawn\n" << endl;

    board.move_piece(ChessMove(7, 6, 7, 7, board.getPiece(7, 6)));

    board.display_utf8();

    return 0;
}

#endif // MAIN_HEADER