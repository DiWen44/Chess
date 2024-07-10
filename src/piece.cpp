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
