#include <iostream>
#include <codecvt>
#include <string>
#include <locale>
#include <cassert>
#include <algorithm>
#include "ChessBoard.h"
#include "Pawn.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"

using std::cout;
using std::endl;

ChessBoard::ChessBoard() : state(Matrix<ChessPiece*>(8)) {}
ChessBoard::ChessBoard(int aiPlayer) : aiPlayer(aiPlayer), state(Matrix<ChessPiece*>(8)) {}
ChessBoard::~ChessBoard() {}

void ChessBoard::populate() {
    // Create PAWNS
    for (int i = 0; i < 8; i++) {
        state(1, i) = new Pawn(this, i, 1, 1);    // Whites
        whites.push_back(state(1, i));
        state(6, i) = new Pawn(this, i, 6, 0);    // Blacks
        blacks.push_back(state(6, i));
    }

    // Create ROOKS
    state(0, 0) = new Rook(this, 0, 0, 1);        // Whites
    whites.push_back(state(0, 0));
    state(0, 7) = new Rook(this, 7, 0, 1);
    whites.push_back(state(0, 7));
    state(7, 0) = new Rook(this, 0, 7, 0);        // Blacks
    blacks.push_back(state(7, 0));
    state(7, 7) = new Rook(this, 7, 7, 0);
    blacks.push_back(state(7, 7));

    // Create KNIGHTS
    state(0, 1) = new Knight(this, 1, 0, 1);        // Whites
    whites.push_back(state(0, 1));
    state(0, 6) = new Knight(this, 6, 0, 1);
    whites.push_back(state(0, 6));
    state(7, 1) = new Knight(this, 1, 7, 0);        // Blacks
    blacks.push_back(state(7, 1));
    state(7, 6) = new Knight(this, 6, 7, 0);
    blacks.push_back(state(7, 6));

    // Create BISHOPS
    state(0, 2) = new Bishop(this, 2, 0, 1);        // Whites
    whites.push_back(state(0, 2));
    state(0, 5) = new Bishop(this, 5, 0, 1);
    whites.push_back(state(0, 5));
    state(7, 2) = new Bishop(this, 2, 7, 0);        // Blacks
    blacks.push_back(state(7, 2));
    state(7, 5) = new Bishop(this, 5, 7, 0);
    blacks.push_back(state(7, 5));

    // Create QUEEN
    state(0, 3) = new Queen(this, 3, 0, 1);         // White Queen
    whites.push_back(state(0, 3));
    state(7, 3) = new Queen(this, 3, 7, 0);         // Black Queen
    blacks.push_back(state(7, 3));

    // Create KING
    state(0, 4) = new King(this, 4, 0, 1);         // White King
    whites.push_back(state(0, 4));
    state(7, 4) = new King(this, 4, 7, 0);         // Black King
    blacks.push_back(state(7, 4));
}

void ChessBoard::populate(const char* board) {
    // Clear the ChessBoard of old pieces
    whites.clear();
    blacks.clear();

    // Empty the state matrix of garbage pointers
    for ( int i = 0; i < 8; i++ ) {
        for ( int j = 0; j < 8; j++ ) {
            state(i, j) = 0;
        }
    }

    bool isWhite;
    int x,y;
    char piece;
    for ( int i = 0; i < 64; i++ ) {
        piece = board[i];
        if (piece == '\0') {                                        // End of input string
            cout << "Insufficient characters in populate input! Expected 64 and found " << i << "." << endl;
            return;
        }
        if (piece == '.') { continue; }                             // No piece

        isWhite = (piece < 91); 
        //cout << "Examining piece " << piece << " which is white: " << isWhite << endl;
        vector<ChessPiece*>& curr = isWhite ? whites : blacks;
        y = i % 8;
        x = 7 - (i / 8);

        if (piece == 'Q' || piece == 'q') {
            state(x, y) = new Queen(this, y, x, isWhite);
        } else if (piece == 'K' || piece == 'k') {
            state(x, y) = new King(this, y, x, isWhite);
        } else if (piece == 'B' || piece == 'b') {
            state(x, y) = new Bishop(this, y, x, isWhite);
        } else if (piece == 'N' || piece == 'n') {
            state(x, y) = new Knight(this, y, x, isWhite);
        } else if (piece == 'R' || piece == 'r') {
            state(x, y) = new Rook(this, y, x, isWhite);
        } else if (piece == 'P' || piece == 'p') {
            state(x, y) = new Pawn(this, y, x, isWhite);
        } else {
            cout << "Invalid characters in populate input! Expected chess character QKBNRP. and found " << board[i] << "!" << endl;
            return;
        }
        curr.push_back(state(x, y));
    }
}

bool ChessBoard::selectAscendAI(const char& pick, const int& x, const int& y, const bool& isWhite) {

    vector<ChessPiece*>& curr = isWhite ? whites : blacks;
    int movesBefore = capturingMoves(isWhite).size();

    ChessPiece* newPiece;
    switch (pick) {
        case 'q':
            newPiece = new Queen(this, x, y, isWhite);
            break;
        case 'b':
            newPiece = new Bishop(this, x, y, isWhite);
            break;
        case 'n':
            newPiece = new Knight(this, x, y, isWhite);
            break;
        case 'r':
            newPiece = new Rook(this, x, y, isWhite);
            break;
        case 'p':
            newPiece = new Pawn(this, x, y, isWhite);
            break;
    }

    state(y, x) = newPiece;
    curr.push_back(newPiece);

    bool goodAscend = capturingMoves(isWhite).size() == movesBefore;

    curr.pop_back();    
    delete newPiece;

    state(y, x) = nullptr;

    return goodAscend;
}

// Helper function for ascendPawn
char ChessBoard::selectCharAI(const int& x, const int& y, const bool& isWhite) {
    if (aiPlayer == 2) {          // Check for smart choice
        char letters[5] = {'q', 'b', 'n', 'r', 'p'};
        for (char choice : letters) {
            if (selectAscendAI(choice, x, y, isWhite)) {
                return choice;
            }
        }
    }
    int choice = rand() % 5;
        switch (choice) {
            case 0:
                return 'q';
            case 1:
                return 'b';
            case 2:
                return 'n';
            case 3:
                return 'r';
            default:
                return 'p';
        }
}

void ChessBoard::ascendPawn(const int& x, const int& y) {
    if (dynamic_cast<Pawn*>(state(y, x))) {     // Check that the piece at x,y is a Pawn
        ChessPiece*& p = state(y, x);

        bool isWhite = p->colour();
        vector<ChessPiece*>& curr = isWhite ? whites : blacks;
        vector<ChessPiece*>::iterator toErase = std::find(curr.begin(), curr.end(), p);

        assert(toErase != curr.end());  // Ensure you are altering a valid piece

        delete *toErase;
        curr.erase(toErase);

        char pick;
        cout << "Please pick a piece to promote to [Q, B, N, R, P]: ";

        while (true) {
            if (aiPlayer) {
                pick = selectCharAI(x, y, isWhite);
                cout << "\nPicked random piece: " << pick << endl;
            } else {
                std::cin >> pick;
            }
            if ( pick == 'Q' || pick == 'q' ) {
                state(y, x) = new Queen(this, x, y, isWhite);
                break;
            } else if ( pick == 'B' || pick == 'b' ) {
                state(y, x) = new Bishop(this, x, y, isWhite);
                break;
            } else if ( pick == 'N' || pick == 'n' ) {
                state(y, x) = new Knight(this, x, y, isWhite);
                break;
            } else if ( pick == 'R' || pick == 'r' ) {
                state(y, x) = new Rook(this, x, y, isWhite);
                break;
            } else if ( pick == 'P' || pick == 'p') {
                state(y, x) = new Pawn(this, x, y, isWhite);
                break;
            } else {
                cout << "Invalid piece selection please choose one of [Q, B, N, R, P]: ";
            }
        }
        curr.push_back(state(y, x));
        return;
    }

    cout << "Invalid piece to ascend! Piece is not a Pawn!" << endl;
}

int ChessBoard::occupied(int x, int y) {
    if (!state(y, x)) {
        return 0;
    } else {
        return state(y, x)->colour() ? 1 : 2;
    }
}

void ChessBoard::move_piece(ChessMove chessmove) {
    int& x = chessmove.from_x;
    int& y = chessmove.from_y;
    int& to_x = chessmove.to_x;
    int& to_y = chessmove.to_y;
    // Handle null move
    if ((x == to_x) && (y == to_y)) { return; }

    ChessPiece*& piece = chessmove.piece;

    if (state(to_y, to_x)) {            // Handle capturing move
        ChessPiece*& enemy = state(to_y, to_x);
        int enemyclr = enemy->colour();
        int clr = piece->colour();

        assert(enemyclr != clr);        // Ensure you do not capture own pieces

        // Delete the piece from the vector of coloured pieces
        vector<ChessPiece*>& curr = enemyclr ? whites : blacks;
        vector<ChessPiece*>::iterator toErase = std::find(curr.begin(), curr.end(), enemy);

        assert(toErase != curr.end());  // Ensure you are capturing a valid piece

        delete *toErase;
        curr.erase(toErase);
    }

    state(y, x) = 0;                    // Remove piece from old location
    state(to_y, to_x) = piece;          // Set piece at new location
    piece->move(to_x, to_y);            // Set piece internals to new location

    return;
}

vector<ChessMove> ChessBoard::capturingMoves(bool isWhite) {
    const vector<ChessPiece*>& curr = isWhite ? whites : blacks;       // Select the correct piece list
    vector<ChessMove> res;

    for (u_int i = 0; i < curr.size(); i++) {
        vector<ChessMove> iMoves = curr[i]->capturingMoves();
        res.insert(res.end(), iMoves.begin(), iMoves.end());        // Concatenate vectors
    }

    return res;
}

vector<ChessMove> ChessBoard::nonCapturingMoves(bool isWhite) {
    const vector<ChessPiece*>& curr = isWhite ? whites : blacks;       // Select the correct piece list
    vector<ChessMove> res;

    for (u_int i = 0; i < curr.size(); i++) {
        vector<ChessMove> iMoves = curr[i]->nonCapturingMoves();
        res.insert(res.end(), iMoves.begin(), iMoves.end());        // Concatenate vectors
    }

    return res;
}

const Matrix<ChessPiece*> ChessBoard::getState() {
    return state;
}

ChessPiece* ChessBoard::getPiece(int x, int y) {
    if (x < 0 || x > 7 || y < 0 || y > 7) {
        throw std::out_of_range("Invalid get piece indices.");
    }
    return state(y, x);
}

void ChessBoard::display_latin1() {
    for (int i = 7; i >= 0; i--) {
        for (int j = 0; j < 8; j++) {
            if (state(i, j)) {
                cout << state(i, j)->latin1Representation();
            } else {
                cout << ".";
            }
            cout << " ";
        }
        cout << endl;
    }
    cout << endl;
    // std::cout << state << std::endl;

    return;
}

void ChessBoard::display_utf8() {
    for (int i = 7; i >= 0; i--) {
        for (int j = 0; j < 8; j++) {
            if (state(i, j)) {
                std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> converter;
                cout << converter.to_bytes(state(i, j)->utfRepresentation());
            } else {
                cout << ".";
            }
            cout << " ";
        }
        cout << endl;
    }
    cout << endl;
    // std::cout << state << std::endl;

    return;
}

/** 
 * Returns 0 if White has won (there are no whites left)
 * Returns 1 if Black has won (there are no blacks left)
 * Returns -1 if neither side has won and 2 if both teams are empty (uninitialized)
*/
int ChessBoard::isFinished() {
    bool whiteEmpty = whites.empty();
    bool blackEmpty = blacks.empty();
    if (whiteEmpty && blackEmpty) { return 2; }
    if (whiteEmpty) { return 0; }
    if (blackEmpty) { return 1; }
    return -1;
}

bool ChessBoard::testMoveLosingChess(ChessMove& move, const bool isWhite) {
    int numMovesInitial = capturingMoves(!isWhite).size();

    ChessPiece* piece = move.piece;
    bool goodMove = false;

    if (occupied(move.to_x, move.to_y)) {
        vector<ChessPiece*>& opponent = isWhite ? blacks : whites;
        ChessPiece* target = state(move.to_y, move.to_x);

        vector<ChessPiece*>::iterator toErase = std::find(opponent.begin(), opponent.end(), target);
        assert(toErase != opponent.end());  // Ensure you are altering a valid piece
        opponent.erase(toErase);

        // Test move piece
        state(move.to_y, move.to_x) = piece;
        state(move.from_y, move.from_x) = nullptr;

        goodMove = capturingMoves(!isWhite).size() > numMovesInitial;

        // Restore board
        state(move.to_y, move.to_x) = target;
        opponent.push_back(target);
        state(move.from_y, move.from_x) = piece;
    } else {
        // Test move piece
        state(move.to_y, move.to_x) = piece;
        state(move.from_y, move.from_x) = nullptr;

        goodMove = capturingMoves(!isWhite).size() > numMovesInitial;
        
        // Restore board
        state(move.to_y, move.to_x) = nullptr;
        state(move.from_y, move.from_x) = piece;
    }

    return goodMove;
}

istream& operator >>(istream& in, ChessBoard& board) {

    char input[64];
    char read;
    int currSquare = 0;
    while (in.get(read) && currSquare < 64) {
        if (
            read == '.' ||
            read == 'Q' || read == 'q' ||
            read == 'K' || read == 'k' ||
            read == 'B' || read == 'b' ||
            read == 'R' || read == 'r' ||
            read == 'N' || read == 'n' ||
            read == 'P' || read == 'p'
        ) {
            input[currSquare++] = read;
        }
    }

    board.populate(input);
    
    return in;
}