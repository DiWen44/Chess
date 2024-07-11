#include <string>
#include <vector>
#include <array>

#include "piece.hpp"
#include "square.hpp"
#include "player.hpp"

#pragma once


class Game {

    public:


        // Constructor - this will mainly set up the board in starting position
        Game(Player* white, Player* black);


        std::array<std::array<Piece*, 8>, 8> getBoard();


        void printBoard();


        // If currently white's turn, sets turn to black, and vice versa.
        void toggleTurn(); 


        // Returns turn pointer
        Player* getTurn();


        // Moves a piece from start square to dest (destination) square
        // If a piece is present at the dest square, that piece is removed #
        // and replaced with the piece being moved.
        // THIS ASSUMES THAT THE MOVE IS LEGAL. USE ISLEGALMOVE() TO CHECK FIRST.
        void movePiece(const Square& start, const Square& dest);


        // Checks if move from start square to dest square is legal. 
        // Returns true if legal, returns false if illegal
        bool isLegalMove(const Square& start, const Square& dest);
        

        // Returns true if it's possible for the player whose turn it is
        // to castle short (kingside), otherwise false
        bool shortCastleIsLegal();


        // Player whose turn it is castling kingside (short castle)
        void shortCastle();


        // Returns true if it's possible for the player whose turn it is
        // to castle long (queenside), otherwise false
        bool longCastleIsLegal();


        // Player whose turn it is castle queenside (long castle)
        void longCastle();


        // Determines if the player whose turn it is is in check
        bool isCheck();
        

        // Determines if the player whose turn it is in checkmate
        bool isCheckmate();


        // Represents the player whose turn it is resigning.
        void resign();


        // Represents the player whose turn it is offering a draw to the other player
        // Returns true if the draw was accepted, returns false if declined.
        bool offerDraw();


    private:

        // Used in printBoard() to paint white and black squares in terminal
        // If square background color is white, switches it to black, and vice versa
        void toggleBackgroundColor();

        // Determine if a given square is being attacked by
        // an opposition (player whose turn it is not) piece.
        bool isAttacked(Square target);

        // 2-dimensional 8x8 array representing the board
        // Each empty square on the board is occupied by a nullptr
        std::array<std::array<Piece*, 8>, 8> board;

        // Points to white player object
        Player* white;

        // Points to black player object
        Player* black;

        // Points to player whose turn it is
        Player* turn;
};