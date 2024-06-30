#include <unordered_map>
#include <string>

#include "piece.hpp"


char pieceToChar(const Piece &piece){

    // Return whitespace for "none" piece
    if (isNone(piece)){
        return ' ';
    }
    
    if (piece.color == PieceColor::WHITE){
        switch(piece.type){
            case PieceType::KING:
                return 'K';
                break;
            case PieceType::QUEEN:
                return 'Q';
                break;
            case PieceType::ROOK:
                return 'R';
                break;
            case PieceType::BISHOP:
                return 'B';
                break;
            case PieceType::KNIGHT:
                return 'N';
                break;
            case PieceType::PAWN:
                return 'P';
                break;
        }
    } else if (piece.color == PieceColor::BLACK){
        switch(piece.type){
            case PieceType::KING:
                return 'k';
                break;
            case PieceType::QUEEN:
                return 'q';
                break;
            case PieceType::ROOK:
                return 'r';
                break;
            case PieceType::BISHOP:
                return 'b';
                break;
            case PieceType::KNIGHT:
                return 'n';
                break;
            case PieceType::PAWN:
                return 'p';
                break;
        }
    }
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