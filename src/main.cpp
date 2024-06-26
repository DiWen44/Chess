#include <iostream>
#include <string>
#include <vector>

#include "game.hpp"


int main(){
    std::cout << "-------------------------------------------------------------------------------------------------" << std::endl;
    std::cout << "CHESS" << std::endl;

    Game game;

    std::string input;
    std::vector<std::string> move;
    bool end = false;
    // Game loop
    while(!end){

        std::cout << game.getTurn() << "'S TURN" << std::endl;
        std::cin >> input;
        std::cout << std::endl;

        game.toggleTurn();
    }
}


/*
* Provided a string representing a users input, tokenizes it into an array of strings, 
* using whitespaces as seperating chars. 
*/
std::vector<std::string> tokenizeInput(std::string input){

    std::vector<std::string> tokens;
    std::string token = "";
    for (int i = 0; i < input.length(); i++){
        if (input[i] == ' '){
            tokens.push_back(token);
            token = "";
        } else{
            token += input[i];
        }
    }
    return tokens;
}