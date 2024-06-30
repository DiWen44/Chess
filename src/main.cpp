#include <iostream>
#include <string>
#include <vector>

#include "game.hpp"
#include "utils.hpp"


int main(){
    std::cout << "-------------------------------------------------------------------------------------------------" << std::endl;
    std::cout << "CHESS" << std::endl;
    std::cout << "-------------------------------------------------------------------------------------------------" << std::endl;

    Game game;

    std::string input;
    std::vector<std::string> move;
    bool end = false;

    // Game loop
    while(!end){

        game.getBoard()->printBoard();

        std::cout << game.getTurnStr() << "'S TURN" << std::endl;
        std::cout << "> ";
        std::getline(std::cin, input);

        // Resign
        if (input == "r"){
            game.resign();
            end = true;
        } 
  
        // Offer draw
        else if (input == "od"){ 
            bool accepted = game.offerDraw();
            if (accepted){ end = true; }
        } 

        // Move
        else if (input[0] == 'm'){
            std::string start = input.substr(2, 2);
            std::string end = input.substr(5, 2); 


            // Check if square strings are valid
            if (!isValidSquareStr(start)){
                std::cout << "INVALID STARTING SQUARE INPUT. TRY AGAIN" << std::endl;
            }
            else if (!isValidSquareStr(end)){
                std::cout << "INVALID DESTINATION SQUARE INPUT. TRY AGAIN" << std::endl;
            }

            else {
                int* startArr = squareStrToSquareArr(start);
                int* endArr = squareStrToSquareArr(end);
                bool check = game.getBoard()->movePiece(startArr, endArr);
                std::cout << "-------------------------------------------------------------------------------------------------" << std::endl;
                if (check){ // If move was valid and was executed, go to next turn
                    game.toggleTurn();
                } // If move was invalid (i.e check==false), do nothing. The program will take us back to the top of the game loop anyway
            }
        }

        // Unrecognized input
        else{
            std::cout << "INVALID INPUT. TRY AGAIN" << std::endl;
        }

        std::cout << std::endl;
    }
    return 0;
}
