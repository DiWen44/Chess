#include <iostream>
#include <string>
#include <vector>

#include "game.hpp"
#include "square.hpp"


int main(){
    std::cout << "-------------------------------------------------------------------------------------------------" << std::endl;
    std::cout << "CHESS" << std::endl;
    std::cout << "-------------------------------------------------------------------------------------------------" << std::endl;

    Game game;

    // Print starting board & "white's turn"
    std::cout << "WHITE'S TURN" << std::endl;
    game.printBoard();

    std::string input;
    std::vector<std::string> move;
    bool end = false;

    // Game loop
    while(!end){
        
        std::cout << "> ";
        std::cin >> input;

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
        else if (input == "m"){
            
            bool check; // Will hold the bool returned by game.movePiece() and thus will validate moves.
            do {

                // Get & validate starting square string (square on which piece to move is located).
                std::string startStr;
                do {
                    std::cout << "START SQUARE: ";
                    std::cin >> startStr;
                    if (!isValidSquareStr(startStr)){
                        std::cout << "INVALID SQUARE. TRY AGAIN" << std::endl;
                    }
                } while (!isValidSquareStr(startStr));

                // Get & validate destination square string.
                std::string destStr;
                do {
                    std::cout << "DESTINATION SQUARE: ";
                    std::cin >> destStr;
                    if (!isValidSquareStr(destStr)){
                        std::cout << "INVALID SQUARE. TRY AGAIN" << std::endl;
                    }
                } while (!isValidSquareStr(destStr));


                Square startArr = strToSquare(startStr);
                Square endArr = strToSquare(destStr);
                check = game.movePiece(startArr, endArr);

            } while (!check); // If move was invalid (i.e check==false).
            
            game.toggleTurn();
            // Print board and turn for next turn.
            std::cout << "-------------------------------------------------------------------------------------------------" << std::endl;
            std::cout << std::endl;
            std::cout << game.getTurnStr() << "'S TURN" << std::endl;
            game.printBoard();
        }

        // Unrecognized input
        else{
            std::cout << "INVALID INPUT. TRY AGAIN" << std::endl;
        }

        std::cout << std::endl;
    }
    return 0;
}
