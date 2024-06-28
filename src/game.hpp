#include <string>

#include "board.hpp"

#pragma once


// Color enum used to track whether it's white or black's turn to move
enum class Color {
    WHITE, 
    BLACK
};


class Game {

    public:
    
        Game();

        Board* getBoard();

        // If currently white's turn, sets turn to black, and vice versa.
        void toggleTurn();

        Color getTurn();

        // Get the color of the player whose turn it is, in the form of an all-caps string.
        std::string getTurnStr();

        // Represents the player whose turn it is resigning.
        void resign();

        // Represents the player whose turn it is offering a draw to the other player
        // Returns true if the draw was accepted, returns false if declined.
        bool offerDraw();

    private:
        Board* board;

        // Holds color of player whose turn it is.
        Color turn;

};