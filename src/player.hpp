#include <string>

#include "piece.hpp"
#include "square.hpp"

#pragma once


class Player{

    public:

        Player(PieceColor color);

        // Returns color
        PieceColor getColor();

        // Returns player's piece color in the form of an all-caps string (for output purposes)
        std::string getColorStr();

        // Get the piece color of the opposition player, in the form of an all-caps string (for output purposes)
        std::string getOppColorStr();

        // Returns kingSq
        Square getKingSq();

        // Can setKingSq either by passing a complete square object, or a row and col for the square
        void setKingSq(const Square& newSquare);
        void setKingSq(int row, int col);

        // returns canCastleShort        
        bool getCanCastleShort();

        // sets canCastleShort to newVal        
        void setCastleShort(bool newVal);

        // returns canCastleLong
        bool getCanCastleLong();

        // sets canCastleLong to newVal
        void setCastleLong(bool newVal);

    private:

        // Color of the player's pieces
        PieceColor color;

        // The square the player's king is on, stored here for speedy access
        // Will be updated by game::movePiece() as the king moves
        Square kingSq;

        // If player can castle short
        // i.e. king and kingside rook have not moved
        // set to true initially, will be updated by game::movePiece() when the king or rook moves
        bool canCastleShort;

        // If player can castle long
        // i.e. king and queenside rook have not moved
        // set to true initially, will be updated by game::movePiece() when the king or rook moves
        bool canCastleLong;
};