#include <vector>
#include <iostream>

#include "board.hpp"
#include "piece.hpp"
#include "utils.hpp"


Board::Board(){

    Piece whitePawn;
    whitePawn.type = PieceType::PAWN;
    whitePawn.color = PieceColor::WHITE;
    Piece whiteRook;
    whiteRook.type = PieceType::ROOK;
    whiteRook.color = PieceColor::WHITE;
    Piece whiteKnight;
    whiteKnight.type = PieceType::KNIGHT;
    whiteKnight.color = PieceColor::WHITE;
    Piece whiteBish;
    whiteBish.type = PieceType::BISHOP;
    whiteBish.color = PieceColor::WHITE;
    Piece whiteQueen;
    whiteQueen.type = PieceType::QUEEN;
    whiteQueen.color = PieceColor::WHITE;
    Piece whiteKing;
    whiteKing.type = PieceType::KING;
    whiteKing.color = PieceColor::WHITE;

    Piece blackPawn;
    blackPawn.type = PieceType::PAWN;
    blackPawn.color = PieceColor::BLACK;
    Piece blackRook;
    blackRook.type = PieceType::ROOK;
    blackRook.color = PieceColor::BLACK;
    Piece blackKnight;
    blackKnight.type = PieceType::KNIGHT;
    blackKnight.color = PieceColor::BLACK;
    Piece blackBish;
    blackBish.type = PieceType::BISHOP;
    blackBish.color = PieceColor::BLACK;
    Piece blackQueen;
    blackQueen.type = PieceType::QUEEN;
    blackQueen.color = PieceColor::BLACK;
    Piece blackKing;
    blackKing.type = PieceType::KING;
    blackKing.color = PieceColor::BLACK;

    Piece none = nonePiece();

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


void Board::printBoard(){
    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            char pieceChar = pieceToChar(boardMat[i][j]);
            std::cout << pieceChar;
            toggleBackgroundColor();
        }
        std::cout << std::endl;
    }
}


void Board::toggleBackgroundColor(){
    static bool isBlack = true; // Tracks whether background is currently black 

    if (isBlack){
        std::cout << "\033[48;5;" << 231 << "m"; // Turn background white
    } else { 
        std::cout << "\033[0m"; // Turn background black
    }

    isBlack = !isBlack;
}


Piece* Board::getPieceAt(int* pos){
    Piece* res = &(boardMat[pos[0]][pos[1]]);
    // Return nullptr if piece is none
    if ( isNone(*res) ){
        return nullptr;
    }
    return res;
}


void Board::putPieceAtPos(Piece* piece, int* pos){
    boardMat[pos[0]][pos[1]] = *piece;
}


void Board::vacatePos(int* pos){
    Piece none;
    none.color = PieceColor::NONE;
    none.type = PieceType::NONE;
    boardMat[pos[0]][pos[1]] = none;
}


bool Board::movePiece(int* start, int* end){
    Piece* pieceToMove = getPieceAt(start);
    if (pieceToMove == nullptr){ // getPieceAt returns nullptr if piece is a "none" piece
        std::cout << "INVALID MOVE: NO PIECE AT THAT POSITION" << std::endl;
        return false;
    }

    putPieceAtPos(pieceToMove, end);
    vacatePos(start);
    return true;
}
