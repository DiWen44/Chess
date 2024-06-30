#include <iostream>
#include <string>
#include <vector>

#include "game.hpp"
#include "piece.hpp"
#include "square.hpp"


Game::Game(){

    Piece whitePawn;
    whitePawn.type = PieceType::PAWN;
    whitePawn.color = PieceColor::WHITE;
    Piece whiteRook;
    whiteRook.type = PieceType::ROOK;
    whiteRook.color = PieceColor::WHITE;
    Piece whiteKnight;
    whiteKnight.type = PieceType::KNIGHT;
    whiteKnight.color = PieceColor::WHITE;
    Piece whiteBish;
    whiteBish.type = PieceType::BISHOP;
    whiteBish.color = PieceColor::WHITE;
    Piece whiteQueen;
    whiteQueen.type = PieceType::QUEEN;
    whiteQueen.color = PieceColor::WHITE;
    Piece whiteKing;
    whiteKing.type = PieceType::KING;
    whiteKing.color = PieceColor::WHITE;

    Piece blackPawn;
    blackPawn.type = PieceType::PAWN;
    blackPawn.color = PieceColor::BLACK;
    Piece blackRook;
    blackRook.type = PieceType::ROOK;
    blackRook.color = PieceColor::BLACK;
    Piece blackKnight;
    blackKnight.type = PieceType::KNIGHT;
    blackKnight.color = PieceColor::BLACK;
    Piece blackBish;
    blackBish.type = PieceType::BISHOP;
    blackBish.color = PieceColor::BLACK;
    Piece blackQueen;
    blackQueen.type = PieceType::QUEEN;
    blackQueen.color = PieceColor::BLACK;
    Piece blackKing;
    blackKing.type = PieceType::KING;
    blackKing.color = PieceColor::BLACK;

    Piece none = nonePiece();

    this->board = {
        {whiteRook, whiteKnight, whiteBish, whiteQueen, whiteKing, whiteBish, whiteKnight, whiteRook},
        {whitePawn, whitePawn, whitePawn, whitePawn, whitePawn, whitePawn, whitePawn, whitePawn},
        {none, none, none, none, none, none, none, none},
        {none, none, none, none, none, none, none, none},
        {none, none, none, none, none, none, none, none},
        {none, none, none, none, none, none, none, none},
        {blackPawn, blackPawn, blackPawn, blackPawn, blackPawn, blackPawn, blackPawn, blackPawn},
        {blackRook, blackKnight, blackBish, blackQueen, blackKing, blackBish, blackKnight, blackRook}
    };

    this->turn = Color::WHITE;
}


std::vector<std::vector<Piece>> Game::getBoard(){
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
            char pieceChar = pieceToChar(board[i][j]);
            std::cout << "  " << pieceChar << "  ";
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
    turn = (turn == Color::WHITE) ? Color::BLACK : Color::WHITE;
}


Color Game::getTurn(){
    return turn;
}


std::string Game::getTurnStr(){
    return (turn == Color::WHITE) ? "WHITE" : "BLACK";
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


bool Game::movePiece(Square start, Square dest){
    Piece pieceToMove = board[start.row][start.col];
    if (isNone(pieceToMove)){ // getPieceAt returns nullptr if piece is a "none" piece
        std::cout << "NO PIECE AT THAT POSITION. TRY AGAIN" << std::endl;
        return false;
    }

    board[dest.row][dest.col] = pieceToMove;
    board[start.row][start.col] = nonePiece(); // Vacate start square by setting it to the "none" piece

    return true;
}


void Game::resign(){
    std::cout << getTurnStr() << " RESIGNS" << std::endl;
    std::cout << "-------------------------------------------------------------------------------------------------" << std::endl;
}


bool Game::offerDraw(){
    std::string playerOffering = getTurnStr();
    std::string playerRecieving = (turn == Color::WHITE) ? "BLACK" : "WHITE";

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

