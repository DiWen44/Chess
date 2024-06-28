#include <unordered_map>
#include <string>

#pragma once


enum class PieceType{
    NONE,
    PAWN,
    KNIGHT,
    BISHOP,
    ROOK,
    QUEEN,
    KING
};


enum class PieceColor{
    NONE, 
    WHITE, 
    BLACK
};


typedef struct {
    PieceType type;
    PieceColor color;
} Piece;


// Maps pieces to their unicode chess piece characters 
char pieceToChar(const Piece &piece);


// Returns a "none" piece
Piece nonePiece();


// Returns true if a given piece is a "none" piece, otherwise false
bool isNone(const Piece& piece);


// Overload == operator to allow straightforward comparison between pieces
bool operator==(const Piece& piece1, const Piece& piece2);