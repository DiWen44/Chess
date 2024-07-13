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

        // Overload constructors with default constructor so that 
        // we can allocate pieces on the heap using new.
        // Once pieces are allocated, we can set their colors
        // Each piece will have an overloaded default constructor
        Piece();

        // Returns piece's color
        PieceColor getColor();
        
        // Sets hasMoved to true
        // Has no effect if called when hasMoved = true, as hasMoved is already true.
        void moved();

        // Returns value of hasMovedFromOrigin.
        bool getHasMoved();

        // Sets piece's color to provided PieceColor
        void setColor(PieceColor color);

        // Returns the appropriate character for the piece, for display purposes
        // White pieces will be in uppercase, black pieces in lowercase.
        // The char-to-piece mappings are listed below:
        // P/p - pawn
        // N/n - knight
        // B/b - bishop
        // R/r - rook
        // Q/q - queen
        // K/k - king
        virtual char toChar() = 0;

        // Given a starting square (at which the piece is located), and destination square, determine if the piece can legally move from start to dest
        // as per the rules of the piece's movement. Also takes the board as a param.
        //
        // NOTE THAT THIS DOES NOT ACCOUNT FOR:
        // - A start square being provided that does not contain the piece concerned
        // - A dest square being provided that contains a friendly piece
        // - The move resulting in the player whose turn it is being in check
        // These are to be dealt with by the Game::isValidMove() method, which performs the relevant checks before calling this method.
        virtual bool isLegalMove(const Square& start, const Square& dest, const std::array<std::array<Piece*, 8>, 8>& board) = 0;

        // Given a starting square (at which the piece is located), returns a vector of destination squares to which the piece can legally move
        // Also takes the board as a param.
        virtual std::vector<Square> legalDests(const Square& start, const std::array<std::array<Piece*, 8>, 8>& board) = 0;

    protected:

        // Piece's color
        PieceColor color;

        // True if piece has moved from original position, otherwise false
        bool hasMoved;
};


// Determine if a given "target" square is being attacked by
// an opposition piece.
// Takes as parameters:
// - target square
// - game board array
// - color of friendly (i.e. non-opposition) pieces
bool isAttacked(Square target, const std::array<std::array<Piece*, 8>, 8>& board, PieceColor friendlyColor);

