#include <unordered_map>
#include <string>

#include "piece.hpp"

Piece::Piece(){}

Piece::Piece(PieceColor color): color(color){}

PieceColor Piece::getColor(){ return color; }

void Piece::setColor(PieceColor color){ this->color = color; }
