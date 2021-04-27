#include "RandomAI.h"
#include <vector>
//#include <stdlib.h>

using std::vector;

ChessMove RandomAI::makeMove() {
    vector<ChessMove> caps = board.capturingMoves(isWhite);

    if ( caps.size() > 0 ) {
        return caps[rand() % caps.size()];
    }

    vector<ChessMove> nocaps = board.nonCapturingMoves(isWhite);

    if ( nocaps.size() > 0 ) {
        return nocaps[rand() % nocaps.size()];
    } 

    // Null move
    return ChessMove(0, 0, 0, 0, board.getPiece(0, 0));
}