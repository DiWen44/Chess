#include <iostream>
#include <string>
#include <vector>

#include "game.hpp"
#include "square.hpp"
#include "piece.hpp"


int main(){
    std::cout << "-------------------------------------------------------------------------------------------------" << std::endl;
    std::cout << "CHESS" << std::endl;
    std::cout << "-------------------------------------------------------------------------------------------------" << std::endl;

    Player white(PieceColor::WHITE);
    Player black(PieceColor::BLACK);
    Game game(&white, &black);

    bool end = false;

    // Game loop
    while(!end){

        // If last turn's move has resulted in a checkmate
        if (game.isCheckmate()) {
            std::cout << "CHECKMATE - " << game.getTurn()->getOppColorStr() << " WINS" << std::endl;
            std::cout << "-------------------------------------------------------------------------------------------------" << std::endl;
            end = true;
            continue;
        } 
        else {
            std::cout << "-------------------------------------------------------------------------------------------------" << std::endl;
            if (game.isCheck()){std::cout << "CHECK" << std::endl;} // Notify players if a check was given.
            std::cout << std::endl;
            std::cout << game.getTurn()->getColorStr() << "'S TURN" << std::endl;
            game.printBoard();
        }

        std::string input;

        // Tracks whether to switch turns from white to black or vice versa
        // Will be initialized to false, set to true within the below loop at some stage, then be reset to false here when the next turn begins
        bool turnChange = false; 
        do {
        
            std::cout << "> ";
            std::cin >> input;

            // Resign
            if (input == "r"){
                std::cout << game.getTurn()->getColorStr() << " RESIGNS - " << game.getTurn()->getOppColorStr() << " WINS" << std::endl;
                std::cout << "-------------------------------------------------------------------------------------------------" << std::endl;
                turnChange = true;
                end = true;
            } 
    
            // Offer draw
            else if (input == "od"){ 
                
                std::cout << game.getTurn()->getColorStr() << " OFFERS A DRAW" << std::endl;
                std::string resp;
                do {
                    std::cout << game.getTurn()->getOppColorStr() << ", TYPE (y) TO ACCEPT AND (n) TO DECLINE: "; 
                    std::cin >> resp;
                } while(resp != "y" && resp != "n");

                if (resp == "y"){
                    std::cout << "DRAW" << std::endl;
                    std::cout << "-------------------------------------------------------------------------------------------------" << std::endl;
                    turnChange = true;
                    end = true; 
                } else {
                    std::cout << "DRAW DECLINED, GAME CONTINUES." << std::endl;
                }
            } 

            // Regular move
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
                    Square start = squareFromStr(startStr);

                    // Get & validate destination square string.
                    std::string destStr;
                    do {
                        std::cout << "DESTINATION SQUARE: ";
                        std::cin >> destStr;
                        if (!isValidSquareStr(destStr)){
                            std::cout << "INVALID SQUARE. TRY AGAIN" << std::endl;
                        }
                    } while (!isValidSquareStr(destStr));
                    Square dest = squareFromStr(destStr);
                    
                    legal = game.isLegalMove(start, dest); 

                    if (legal){
                        game.movePiece(start, dest);
                        turnChange = true;
                    } else {
                        std::cout << "ILLEGAL MOVE. TRY AGAIN" << std::endl;
                    }

                } while (!legal); // Repeat move process until user inputs a legal move
            }

            // Castling kingside/short
            else if (input == "cs"){
                if (game.shortCastleIsLegal()){
                    game.shortCastle();
                    turnChange = true;
                }
                else {
                    std::cout << "CAN'T CASTLE SHORT HERE" << std::endl;
                }
            }

            // Castling queenside/long
            else if (input == "cl"){
                if (game.longCastleIsLegal()){
                    game.longCastle();
                    turnChange = true;
                }
                else {
                    std::cout << "CAN'T CASTLE LONG HERE" << std::endl;
                }
            }

            // Unrecognized input
            else { 
                std::cout << "INVALID INPUT. TRY AGAIN" << std::endl;
            }

            std::cout << std::endl;

        } while (!turnChange);

        game.toggleTurn();
    }
    return 0;
}
