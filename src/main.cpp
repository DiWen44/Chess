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
            
            bool legal; // Will hold the bool returned by game.movePiece() and thus will validate moves.
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


                Square start = squareFromStr(startStr);
                Square dest = squareFromStr(destStr);
                legal = game.isLegalMove(start, dest); 

                if (legal){
                    game.movePiece(start, dest);
                } else {
                    std::cout << "ILLEGAL MOVE. TRY AGAIN" << std::endl;
                }

            } while (!legal);
            
            game.toggleTurn();
            // Print board and turn for next turn.
            std::cout << "-------------------------------------------------------------------------------------------------" << std::endl;
            if (game.isCheck()){std::cout << "CHECK" << std::endl;} // Notify players if a check was given.
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
