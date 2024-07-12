#include "player.hpp"
#include "piece.hpp"
#include "square.hpp"


Player::Player(PieceColor color) : color(color) {
        if (color == PieceColor::WHITE){
            this->kingSq = square(0, 4);
        } else if (color == PieceColor::BLACK){
            this->kingSq = square(7, 4);
        }
}


PieceColor Player::getColor(){ return color; }


std::string Player::getColorStr(){ 
    std::string res = (color == PieceColor::WHITE)  ? "WHITE" : "BLACK";
    return res;
}


std::string Player::getOppColorStr(){
    std::string res = (color == PieceColor::WHITE)  ?  "BLACK" : "WHITE";
    return res;
}


Square Player::getKingSq(){ return kingSq; }


void Player::setKingSq(const Square& newSquare){ kingSq = newSquare; }
void Player::setKingSq(int row, int col){ kingSq = square(row, col); }


