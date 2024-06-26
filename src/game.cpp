#include <iostream>
#include <string>

#include "game.hpp"
#include "board.hpp"

/*
* Constructor
*/
Game::Game(){
    this->board = new Board();
    this->turn = WHITE;
}


/*
* If currently white's turn, sets turn to black, and vice versa.
*/
void Game::toggleTurn(){
    if (turn == WHITE){
        this->turn = BLACK;
    } else{
        this->turn = WHITE;
    }
}


/*
* Get the color of the player whose turn it is, in the form of an all-caps string
*/
std::string Game::getTurn(){
    return (this->turn == WHITE) ? "WHITE" : "BLACK";
}


/*
* Represents the player whose turn it is resigning
*/
void Game::resign(){
    std::cout << this->getTurn() << " RESIGNS" << std::endl;
}


/*
* Represents the player whose turn it is offering a draw to the other player
*/
void Game::offerDraw(){
    std::string playerOffering = this->getTurn();
    std::string playerRecieving= (this->turn == WHITE) ? "BLACK" : "WHITE";

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
        std::cout << "-------------------------------------------------------------------------------------------------" << std::endl;
    } else {
        std::cout << "DRAW DECLINED, GAME CONTINUES" << std::endl;
    }
}

