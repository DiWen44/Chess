#include <string>
#include <vector>
#include <array>

#include "piece.hpp"
#include "square.hpp"

#pragma once


class Game {


    public:

        // Constructor - this will mainly set up the board in starting position
        Game();

        std::array<std::array<Piece*, 8>, 8> getBoard();

        void printBoard();

        // If currently white's turn, sets turn to black, and vice versa.
        void toggleTurn(); 

        // Get the color of the player whose turn it is as, returning it as an option for the color enum.
        PieceColor getTurn();

        // Get the color of the player whose turn it is, in the form of an all-caps string.
        std::string getTurnStr();

        // Moves a piece from start square to dest (destination) square
        // If a piece is present at the dest square, that piece is removed #
        // and replaced with the piece being moved
        void movePiece(const Square& start, const Square& dest);

        // Checks if move from start square to dest square is legal. 
        // Returns true if legal, returns false if illegal
        bool isLegalMove(const Square& start, const Square& dest);
        
        // Determines if the player whose turn it is in checkmate
        bool isCheckMate();

        // Represents the player whose turn it is resigning.
        void resign();

        // Represents the player whose turn it is offering a draw to the other player
        // Returns true if the draw was accepted, returns false if declined.
        bool offerDraw();


    private:

        // 2-dimensional 8x8 vector representing the board
        // Each empty square on the board is occupied by the "none" piece
        std::array<std::array<Piece*, 8>, 8> board;

        // Holds color of player whose turn it is.
        PieceColor turn;

        // Used in printBoard() to paint white and black squares in terminal
        // If square background color is white, switches it to black, and vice versa
        void toggleBackgroundColor();

};