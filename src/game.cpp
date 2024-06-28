#include <iostream>
#include <string>

#include "game.hpp"
#include "board.hpp"
#include "utils.hpp"


Game::Game(){
    this->board = new Board();
    this->turn = Color::WHITE;
}


Board* Game::getBoard(){
    return board;
}


void Game::toggleTurn(){
    turn = (turn == Color::WHITE) ? Color::WHITE : Color::BLACK;
}


Color Game::getTurn(){
    return turn;
}


std::string Game::getTurnStr(){
    return (turn == Color::WHITE) ? "WHITE" : "BLACK";
}



void Game::resign(){
    std::cout << getTurnStr() << " RESIGNS" << std::endl;
    std::cout << "-------------------------------------------------------------------------------------------------" << std::endl;
}


bool Game::offerDraw(){
    std::string playerOffering = getTurnStr();
    std::string playerRecieving= (turn == Color::WHITE) ? "BLACK" : "WHITE";

    std::cout << playerOffering << " OFFERS A DRAW" << std::endl;
    std::cout << playerRecieving<< ", TYPE y TO ACCEPT AND n TO DECLINE: "; 
    std::string resp;
    std::cin >> resp;
    std::cout << std::endl;

    while(resp != "y" && resp != "n"){
        std::cout << "INVALID INPUT" << std::endl;
        std::cout << playerRecieving << ", TYPE y TO ACCEPT AND n TO DECLINE: "; 
        std::cin >> resp;
        std::cout << std::endl;
    }

    if (resp == "y"){
        std::cout << "DRAW" << std::endl;
        return true;
        std::cout << "-------------------------------------------------------------------------------------------------" << std::endl;
    } else {
        std::cout << "DRAW DECLINED, GAME CONTINUES" << std::endl;
        return false;
    }
}

