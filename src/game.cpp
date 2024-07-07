#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <cmath>

#include "game.hpp"
#include "piece.hpp"
#include "square.hpp"
#include "pawn.hpp"
#include "knight.hpp"
#include "bishop.hpp"
#include "rook.hpp"
#include "queen.hpp"
#include "king.hpp"      


Game::Game(){

    // Populating board with pieces at starting positions
    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){

            switch (i){
                // White officers
                case 0: 
                    switch (j){
                        case 0:
                        case 7:
                            board[i][j] = new Rook;
                            break;
                        case 1:
                        case 6:
                            board[i][j] = new Knight;
                            break;               
                        case 2:
                        case 5:
                            board[i][j] = new Bishop;
                            break;
                        case 3:
                            board[i][j] = new Queen;
                            break;
                        case 4:
                            board[i][j] = new King;
                            break;
                    }
                    board[i][j]->setColor(PieceColor::WHITE);
                    break;
                // White pawns
                case 1:
                    board[i][j] = new Pawn;
                    board[i][j]->setColor(PieceColor::WHITE);
                    break;
                // Black pawns
                case 6:
                    board[i][j] = new Pawn;
                    board[i][j]->setColor(PieceColor::BLACK);
                    break;
                // Black officers
                case 7:
                    switch (j){
                        case 0:
                        case 7:
                            board[i][j] = new Rook;
                            break;
                        case 1:
                        case 6:
                            board[i][j] = new Knight;
                            break;               
                        case 2:
                        case 5:
                            board[i][j] = new Bishop;
                            break;
                        case 3:
                            board[i][j] = new Queen;
                            break;
                        case 4:
                            board[i][j] = new King;
                            break;
                    }
                    board[i][j]->setColor(PieceColor::BLACK);
                    break;
                // Empty squares
                default:
                    board[i][j] = nullptr;
                    break;
            }
        }
    }

    this->turn = PieceColor::WHITE;
}


std::array<std::array<Piece*, 8>, 8> Game::getBoard(){
    return board;
}


void Game::printBoard(){
    std::cout << std::endl;

    // Print file letters above board 
    std::cout << "\033[38;5;2m";  // Switch text color to green to print file letters
    std::cout << "  a    b    c    d    e    f    g    h  " << std::endl;  // Print files
    std::cout << "\033[0m"; // Revert to prior text coloring

    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            if (board[i][j] == nullptr){ // If square is empty
                std::cout << "     ";
            } else {
                char pieceChar = board[i][j]->toChar();
                std::cout << "  " << pieceChar << "  ";
            }

            toggleBackgroundColor();
        }

        // Print rank number after rank
        std::cout << "\033[0m"; // Switch background back to black
        std::cout << "\033[38;5;1m";  // Switch text color to red to print rank no.
        std::cout << "  " << i+1; // Print rank
        std::cout << "\033[0m"; // Revert to prior coloring

        std::cout << std::endl;
        toggleBackgroundColor();
        
    }
    std::cout << "(m) move  (r) resign  (od) offer draw" << std::endl;  // List valid user inputs under board
}


void Game::toggleTurn(){
    turn = (turn == PieceColor::WHITE) ? PieceColor::BLACK : PieceColor::WHITE;
}


PieceColor Game::getTurn(){
    return turn;
}


std::string Game::getTurnStr(){
    return (turn == PieceColor::WHITE) ? "WHITE" : "BLACK";
}


void Game::movePiece(const Square& start, const Square& dest){
    Piece *pieceToMove = board[start.row][start.col];
    Piece *pieceAtDest = board[dest.row][dest.col];

    // If destination square not empty, free memory of piece at destination
    if (pieceAtDest != nullptr){
        delete pieceAtDest;
    }

    board[dest.row][dest.col] = pieceToMove;
    board[start.row][start.col] = nullptr; // Vacate start square by setting it to nullptr
    pieceToMove->moved();

    // Check for a pawn promotion
    // Pawns can be promoted to a queen, rook, bishop or knight,
    // Provided they have reached the end of the board
    // i.e. for a white pawn, has reached row 7; for a black pawn, has reached row 0.
    if (dynamic_cast<Pawn*>(pieceToMove)){ // dynamic_cast will returns a truthy value if pieceToMove is a pawn

        if ( (dest.row == 7 && turn == PieceColor::WHITE) || (dest.row == 0 && turn == PieceColor::BLACK) ) {
            std::string choice;
            do {
                std::cout << "PROMOTE TO: QUEEN (q)  ROOK (r)  BISHOP (b)  KNIGHT (n)" << std::endl;
                std::cout << "> ";
                std::cin >> choice;
                std::cout << std::endl;
            } while (choice != "q" && choice != "r" && choice != "b" && choice != "n");

            // Set move destination to selected piece
            Piece* newPiece;
            if (choice == "q"){ newPiece = new Queen; }
            else if (choice == "r"){ newPiece = new Rook; }
            else if (choice == "b"){ newPiece = new Bishop; }
            else if (choice == "n"){ newPiece = new Knight; }
            newPiece->setColor(turn);
            newPiece->moved(); // hasMoved is false by default, so set it to true for the new piece.
            delete pieceToMove; // Free memory of pawn that was moved before assigning new piece.
            board[dest.row][dest.col] = newPiece;
        }
    }
}


bool Game::isLegalMove(const Square& start, const Square& dest){
    Piece *pieceToMove = board[start.row][start.col];
    Piece *pieceAtDest = board[dest.row][dest.col];

    // Return false if user has selected an empty square
    if (pieceToMove == nullptr){ return false; }
    // Return false if user has selected an opposition piece to move,
    else if ( pieceToMove->getColor() != turn){ return false; }

    // Return false if user is trying to move a piece to a square already occupied by a friendly piece
    if (pieceAtDest != nullptr ){ 
        if (pieceAtDest->getColor() == turn){
            return false; 
        }
    }

    // Return false if move results in the player whose turn it is being in check
    // Determine this by simulating the move on the board and calling isCheck()
    board[dest.row][dest.col] = pieceToMove;
    board[start.row][start.col] = nullptr;
    if (isCheck()){
        // Revert board back to previous state that in was in before simulating the move before returning
        board[start.row][start.col] = pieceToMove;
        board[dest.row][dest.col] = pieceAtDest;
        return false;
    }
    // Revert board back to previous state that in was in before simulating the move
    board[start.row][start.col] = pieceToMove;
    board[dest.row][dest.col] = pieceAtDest;

    return pieceToMove->isLegalMove(start, dest, board);
}


// The player is in check if his king is being attacked.
bool Game::isCheck(){

    // Find player's king on board
    Square kingSquare;
    bool brokeInnerLoop = false; // This will allow us to break out of the nested loop.  
    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            if (dynamic_cast<King*>(board[i][j])) { // dynamic_cast here returns a truthy value if piece at board[i][j] is a king
                if (board[i][j]->getColor() == turn){
                    kingSquare = square(i, j);
                    brokeInnerLoop = true;
                    break;
                }
            }
        }
        if (brokeInnerLoop){ break; } // If the inner loop was broken out of, break out of the outer loop
    }

    // Now that king is found, determine if king is being attacked.
    // Do this by scanning the entire board, 
    // and checking if any opposition piece can legally move to the King's square 
    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            if ( board[i][j] != nullptr && board[i][j]->getColor() != turn ){
                Square sqAtIJ = square(i,j); 
                if (board[i][j]->isLegalMove(sqAtIJ, kingSquare, board)){
                    return true;
                } 
            }
        }
    }
    return false;
}


void Game::resign(){
    std::cout << getTurnStr() << " RESIGNS" << std::endl;
    std::cout << "-------------------------------------------------------------------------------------------------" << std::endl;
}


bool Game::offerDraw(){
    std::string playerOffering = getTurnStr();
    std::string playerRecieving = (turn == PieceColor::WHITE) ? "BLACK" : "WHITE";

    std::cout << playerOffering << " OFFERS A DRAW" << std::endl;
    std::cout << playerRecieving<< ", TYPE (y) TO ACCEPT AND (n) TO DECLINE: "; 
    std::string resp;
    std::cin >> resp;

    while(resp != "y" && resp != "n"){
        std::cout << "INVALID INPUT" << std::endl;
        std::cout << playerRecieving << ", TYPE (y) TO ACCEPT AND (n) TO DECLINE: "; 
        std::cin >> resp;
    }

    if (resp == "y"){
        std::cout << "DRAW" << std::endl;
        std::cout << "-------------------------------------------------------------------------------------------------" << std::endl;
        return true;
    } else {
        std::cout << "DRAW DECLINED, GAME CONTINUES." << std::endl;
        return false;
    }
}

void Game::toggleBackgroundColor(){
    static bool isBlack = true; // Tracks whether square background painter is currently black 
    if (isBlack){
        std::cout << "\033[48;5;231m"; // Turn painter white
    } else { 
        std::cout << "\033[0m"; // Turn painter back to black
    }
    isBlack = !isBlack;
}