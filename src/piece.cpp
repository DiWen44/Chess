#include <unordered_map>
#include <string>

#include "piece.hpp"


Piece::Piece(PieceColor color): color(color){}

PieceColor Piece::getColor(){ return color; }