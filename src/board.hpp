#include <vector>
#include <string>

#include "piece.hpp"

#pragma once


class Board{

    public:
        Board();
        void printBoard();

        // Used in printBoard to pain white and black squares
        // If background color is white, switches it to black, and vice versa
        void toggleBackgroundColor();

        // Returns pointer to the piece located at a specified position
        // If piece is a "none" piece, returns a nullptr
        Piece* getPieceAt(int* pos);

        // Puts a piece at a specified position on the board
        // If a piece already exists at that position, 
        // it is replaced with the new piece.
        void putPieceAtPos(Piece* piece, int* pos);
        
        // Puts the "none" piece at a given position, 
        // effectively vacating that position.
        void vacatePos(int* pos);

        // Moves a piece from position start to position end
        // Returns true if move completed, returns false and prints an error msg
        // if move is found to be illegal/invalid
        bool movePiece(int* start, int* end);

        bool isCheckMate();
        bool isCheck();

    private:
        // 2-dimensional 8x8 vector representing the board
        // Each empty square on the board is occupied by the "none" piece
        std::vector<std::vector<Piece>> boardMat;
};
