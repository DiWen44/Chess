#include <unordered_map>
#include <string>

#include "piece.hpp"


char pieceToChar(const Piece &piece){

    // Return whitespace for "none" piece
    if (isNone(piece)){
        return ' ';
    }
    
    char res;
    if (piece.color == PieceColor::WHITE){
        switch(piece.type){
            case PieceType::KING:
                res = '♔';
                break;
            case PieceType::QUEEN:
                res = '♕';
                break;
            case PieceType::ROOK:
                res = '♖';
                break;
            case PieceType::BISHOP:
                res = '♗';
                break;
            case PieceType::KNIGHT:
                res = '♘';
                break;
            case PieceType::PAWN:
                res = '♙';
                break;
        }
    } else if (piece.color == PieceColor::BLACK){
        switch(piece.type){
            case PieceType::KING:
                res = '♚';
                break;
            case PieceType::QUEEN:
                res = '♛';
                break;
            case PieceType::ROOK:
                res = '♜';
                break;
            case PieceType::BISHOP:
                res = '♝';
                break;
            case PieceType::KNIGHT:
                res = '♞';
                break;
            case PieceType::PAWN:
                res = '♟';
                break;
        }
    }
    return res;
}


Piece nonePiece(){
    Piece none;
    none.color = PieceColor::NONE;
    none.type = PieceType::NONE;
    return none;
}


bool isNone(const Piece& piece){
    return (piece.type == PieceType::NONE || piece.color == PieceColor::NONE);
}


bool operator==(const Piece& piece1, const Piece& piece2){
    return (piece1.color == piece2.color) && (piece1.type == piece2.type);
}