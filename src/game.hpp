#include <string>
#include <vector>

#include "piece.hpp"
#include "square.hpp"

#pragma once


// Color enum used to track whether it's white or black's turn to move
enum class Color {
    WHITE, 
    BLACK
};


class Game {


    public:

        // Constructor - this will mainly set up the board in starting position
        Game();

        std::vector<std::vector<Piece>> getBoard();

        void printBoard();

        // If currently white's turn, sets turn to black, and vice versa.
        void toggleTurn(); 

        // Get the color of the player whose turn it is as, returning it as an option for the color enum.
        Color getTurn();

        // Get the color of the player whose turn it is, in the form of an all-caps string.
        std::string getTurnStr();

        // Used in printBoard to pain white and black squares
        // If square background color is white, switches it to black, and vice versa
        void toggleBackgroundColor();

        // Moves a piece from start square to dest (destination) square
        // Returns true if move completed, 
        // if move is found to be illegal/invalid, prints appropriate error msg then returns false
        bool movePiece(Square start, Square dest);

        bool isCheckMate();
        bool isCheck();

        // Represents the player whose turn it is resigning.
        void resign();

        // Represents the player whose turn it is offering a draw to the other player
        // Returns true if the draw was accepted, returns false if declined.
        bool offerDraw();


    private:

        // 2-dimensional 8x8 vector representing the board
        // Each empty square on the board is occupied by the "none" piece
        std::vector<std::vector<Piece>> board;

        // Holds color of player whose turn it is.
        Color turn;

};