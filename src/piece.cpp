#include <unordered_map>
#include <string>

#include "piece.hpp"


Piece::Piece(){
    hasMoved = false;
}


Piece::Piece(PieceColor color): color(color){
    hasMoved = false;
}


void Piece::moved(){ 
    hasMoved = true; 
}


PieceColor Piece::getColor(){ 
    return color; 
}


void Piece::setColor(PieceColor color){ 
    this->color = color; 
}
