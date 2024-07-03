#include <string>
#include <vector>

#include "piece.hpp"
#include "move.hpp"

#pragma once


class Game {


    public:

        // Constructor - this will mainly set up the board in starting position
        Game();

        std::vector<std::vector<Piece>> getBoard();

        void printBoard();

        // If currently white's turn, sets turn to black, and vice versa.
        void toggleTurn(); 

        // Get the color of the player whose turn it is as, returning it as an option for the color enum.
        PieceColor getTurn();

        // Get the color of the player whose turn it is, in the form of an all-caps string.
        std::string getTurnStr();

        // Used in printBoard to pain white and black squares
        // If square background color is white, switches it to black, and vice versa
        void toggleBackgroundColor();

        // Moves a piece from start square to dest (destination) square
        // If a piece is present at the dest square, that piece is removed #
        // and replaced with the piece being moved
        void movePiece(const Move& mv);

        // Determines if piece is able to complete a move
        // According to the rules of that piece's movement
        // Returns true if it can, otherwise false.
        bool isLegalMove(const Move& mv);

        // Given a move, determines if the path along that move is clear
        // i.e. there are no other pieces on that path
        // Works for moves that are purely horizontal, vertical or diagonal
        // Returns true if path is clear, otherwise returns false.
        bool isPathClear(const Move& mv);

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
        PieceColor turn;

};