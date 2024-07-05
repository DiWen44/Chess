#include <unordered_map>
#include <string>
#include <array>
#include <vector>

#include "square.hpp"
#pragma once


// Represent's a pieces color
enum class PieceColor{
    WHITE, 
    BLACK
};


class Piece{
    public:
        Piece(PieceColor color);

        // Returns piece's color
        PieceColor getColor();

        // Returns the appropriate character for the piece, for display purposes
        // White pieces will be in uppercase, black pieces in lowercase.
        // The char-to-piece mappings are listed below:
        // P/p - pawn
        // N/n - knight
        // B/b - bishop
        // R/r - rook
        // Q/q - queen
        // K/k - king
        virtual char toChar();

        // Given a starting square (at which the piece is located), and destination square, determine if the piece can legally move from start to dest
        // Also takes the board as a param
        virtual bool isLegalMove(const Square& start, const Square& dest, const std::array<std::array<int, 8>, 8>& board);

        // Given a starting square (at which the piece is located), returns a vector of destination squares to which the piece can legally move
        // Also takes the board as a param
        virtual std::vector<Square> legalDests(const Square& start, const std::array<std::array<int, 8>, 8>& board);

    protected:
        // Piece's color
        PieceColor color;
};

