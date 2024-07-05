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

        // Determines if piece is able to complete a move from start to dest
        // According to the rules of that piece's movement
        // Returns true if it can, otherwise false.
        bool isLegalMove(const Square& start, const Square& dest);

        // Returns a vector of legal destination squares (a square is represented in form of 2-item array: {row, col} )
        // that the piece at the provided square can legally move to.
        std::vector<std::array<int, 2>> legalMoves(const Square& sq);

        // Determines if the player whose turn it is is currently in check
        bool isCheck();
        
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

        // Given a move, determines if the path along that move is clear
        // i.e. there are no other pieces on that path
        // Works for moves that are purely horizontal, vertical or diagonal
        // Returns true if path is clear, otherwise returns false.
        // Used in isLegalMove()
        bool isPathClear(const Square& start, const Square& dest);
        
        // Check if the square at board[row][col] is attacked by an opposition piece
        // i.e. a piece of the opposite color to the player whose turn it is.
        bool isAttacked(const Square& square);

        // Used in printBoard() to paint white and black squares in terminal
        // If square background color is white, switches it to black, and vice versa
        void toggleBackgroundColor();

};