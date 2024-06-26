#include <string>

#include "board.hpp"

#pragma once

enum Color {WHITE, BLACK};

class Game {

    public:
        Game();
        void toggleTurn();
        std::string getTurn();
        void move(std::string start, std::string end);
        void resign();
        void offerDraw();

    private:
        Board* board;
        Color turn;

};