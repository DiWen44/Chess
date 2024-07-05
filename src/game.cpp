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

    // Allocate pieces using default constructor, can then set their color attribute after allocation.
    Piece *whitePawn = new Pawn; 
    Piece *whiteKnight = new Knight;
    Piece *whiteRook = new Rook;
    Piece *whiteBish = new Bishop;
    Piece *whiteQueen = new Queen;
    Piece *whiteKing = new King;

    Piece *blackPawn = new Pawn; 
    Piece *blackKnight = new Knight;
    Piece *blackRook = new Rook;
    Piece *blackBish = new Bishop;
    Piece *blackQueen = new Queen;
    Piece *blackKing = new King;

    this->board = {{
        {whiteRook, whiteKnight, whiteBish, whiteQueen, whiteKing, whiteBish, whiteKnight, whiteRook},
        {whitePawn, whitePawn, whitePawn, whitePawn, whitePawn, whitePawn, whitePawn, whitePawn},
        {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
        {blackPawn, blackPawn, blackPawn, blackPawn, blackPawn, blackPawn, blackPawn, blackPawn},
        {blackRook, blackKnight, blackBish, blackQueen, blackKing, blackBish, blackKnight, blackRook}
    }};

    // Setting colors of pieces on board
    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            if (i < 2) { // If piece in bottom 2 rows
                board[i][j]->setColor(PieceColor::WHITE); 
            }
            else if (i > 5) { // If piece in top 2 rows
                board[i][j]->setColor(PieceColor::BLACK); 
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
            } else{
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

    board[dest.row][dest.col] = pieceToMove;
    board[start.row][start.col] = nullptr; // Vacate start square by setting it to nullptr

    // Check for a pawn promotion
    // Pawns can be promoted to a queen, rook, bishop or knight.
    // Provided they have reached the end of the board
    // i.e. for a white pawn, has reached row 7; for a black pawn, has reached row 0.
    if (dynamic_cast<Pawn*>(pieceToMove)){ // dynamic_cast will returns a truthy value if pieceToMove is a pawn
        if ( (dest.row == 7 && pieceToMove->getColor() == PieceColor::WHITE) || (dest.row == 0 && pieceToMove->getColor() == PieceColor::BLACK) ) {
            std::string choice;
            do {
                std::cout << "PROMOTE TO: QUEEN (q)  ROOK (r)  BISHOP (b)  KNIGHT (n)" << std::endl;
                std::cout << "> ";
                std::cin >> choice;
                std::cout << std::endl;
            } while (choice != "q" && choice != "r" && choice != "b" && choice != "n");

            // Set move destination to selected piece
            Piece* newPiece;
            if (choice == "q"){ newPiece = new Queen(turn); }
            else if (choice == "r"){ newPiece = new Rook(turn); }
            else if (choice == "b"){ newPiece = new Bishop(turn); }
            else if (choice == "n"){ newPiece = new Knight(turn); }
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

    return pieceToMove->isLegalMove(start, dest, board);
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