#include <vector>

#include "board.hpp"


/*
* Board constructor.
* This will set up a starting board.
*/
Board::Board(){

    Piece whitePawn;
    whitePawn.type = PAWN;
    whitePawn.color = WHITE;
    Piece whiteRook;
    whiteRook.type = ROOK;
    whiteRook.color = WHITE;
    Piece whiteKnight;
    whiteKnight.type = KNIGHT;
    whiteKnight.color = WHITE;
    Piece whiteBish;
    whiteBish.type = BISHOP;
    whiteBish.color = WHITE;
    Piece whiteQueen;
    whiteQueen.type = QUEEN;
    whiteQueen.color = WHITE;
    Piece whiteKing;
    whiteKing.type = KING;
    whiteKing.color = WHITE;

    Piece blackPawn;
    blackPawn.type = PAWN;
    blackPawn.color = BLACK;
    Piece blackRook;
    blackRook.type = ROOK;
    blackRook.color = BLACK;
    Piece blackKnight;
    blackKnight.type = KNIGHT;
    blackKnight.color = BLACK;
    Piece blackBish;
    blackBish.type = BISHOP;
    blackBish.color = BLACK;
    Piece blackQueen;
    blackQueen.type = QUEEN;
    blackQueen.color = BLACK;
    Piece blackKing;
    blackKing.type = KING;
    blackKing.color = BLACK;

    Piece none;
    none.type = NONE;
    none.color = NONE;

    this->boardMat = {
        {whiteRook, whiteKnight, whiteBish, whiteKing, whiteQueen, whiteBish, whiteKnight, whiteRook},
        {whitePawn, whitePawn, whitePawn, whitePawn, whitePawn, whitePawn, whitePawn, whitePawn},
        {none, none, none, none, none, none, none, none},
        {none, none, none, none, none, none, none, none},
        {none, none, none, none, none, none, none, none},
        {none, none, none, none, none, none, none, none},
        {blackPawn, blackPawn, blackPawn, blackPawn, blackPawn, blackPawn, blackPawn, blackPawn},
        {blackRook, blackKnight, blackBish, blackKing, blackQueen, blackBish, blackKnight, blackRook}
    };
}