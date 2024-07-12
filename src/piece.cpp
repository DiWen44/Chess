#include <unordered_map>
#include <string>

#include "piece.hpp"


Piece::Piece(){
    hasMovedFromOrigin = false;
}


Piece::Piece(PieceColor color): color(color){
    hasMovedFromOrigin = false;
}


void Piece::moved(){ 
    hasMovedFromOrigin = true; 
}


bool Piece::hasMoved(){
    return hasMovedFromOrigin;
}


PieceColor Piece::getColor(){ 
    return color; 
}


void Piece::setColor(PieceColor color){ 
    this->color = color; 
}


// Determine if a target square is being attacked by opposition piece.
// Do this by scanning the entire board, 
// and checking if any opposition piece can legally move to the given square.
bool isAttacked(Square target, const std::array<std::array<Piece*, 8>, 8>& board, PieceColor friendlyColor){
    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            // If square contains enemy piece
            if ( board[i][j] != nullptr && board[i][j]->getColor() != friendlyColor ){
                Square sqAtIJ = square(i,j); 
                if (board[i][j]->isLegalMove(sqAtIJ, target, board)){
                    return true;
                } 
            }
        }
    }
    return false; // If no enemy piece is found to be attacking the square
}