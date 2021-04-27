#include "LookaheadAI.h"
#include <vector>

using std::vector;

ChessMove LookaheadAI::makeMove() {
    vector<ChessMove> caps = board.capturingMoves(isWhite);

    if ( caps.size() > 0 ) {
        for (ChessMove move : caps) {
            if (board.testMoveLosingChess(move, isWhite)) {
                return move;
            }
        }
        return caps[rand() % caps.size()];
    }

    vector<ChessMove> nocaps = board.nonCapturingMoves(isWhite);

    if ( nocaps.size() > 0 ) {
        for (ChessMove move : caps) {
            if (board.testMoveLosingChess(move, isWhite)) {
                return move;
            }
        }
        return nocaps[rand() % nocaps.size()];
    } 

    // Null move
    return ChessMove(0, 0, 0, 0, board.getPiece(0, 0));
}