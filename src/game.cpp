#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <cmath>
#include <stdlib.h>

#include "game.hpp"
#include "player.hpp"
#include "piece.hpp"
#include "square.hpp"
#include "pawn.hpp"
#include "knight.hpp"
#include "bishop.hpp"
#include "rook.hpp"
#include "queen.hpp"
#include "king.hpp"      


Game::Game(Player* white, Player* black) : white(white), black(black) {

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

    this->turn = white;
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
    std::cout << "(m) move (cs) castle short (cl) castle long (r) resign (od) offer draw " << std::endl;  // List valid user inputs under board
}


void Game::toggleTurn(){
    turn = (turn == white) ? black : white;
}


Player* Game::getTurn(){
    return turn;
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

    // Update player's kingSq if piece being moved is the king
    if ( dynamic_cast<King*>(pieceToMove)){ // dynamic_cast will returns a truthy value if pieceToMove is of the specified class
        turn->setKingSq(dest);
    }

    // Check for a pawn promotion
    // Pawns can be promoted to a queen, rook, bishop or knight,
    // Provided they have reached the end of the board
    // i.e. for a white pawn, has reached row 7; for a black pawn, has reached row 0.
    else if (dynamic_cast<Pawn*>(pieceToMove)){ 

        if ( (dest.row == 7 && turn->getColor() == PieceColor::WHITE) || (dest.row == 0 && turn->getColor() == PieceColor::BLACK) ) {
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
            newPiece->setColor(turn->getColor());
            newPiece->moved(); // hasMoved is false by default, so set it to true for the new piece.
            delete pieceToMove; // Free memory of pawn that was moved before assigning new piece.
            board[dest.row][dest.col] = newPiece;
        }
    }
}


// A player-inputted move is valid if:
// - the start square contains one of the player's pieces
// - The end square is either empty or occupied by an enemy piece
// - The move does not result in check
// - The piece is legally able to make the move (as per the rules of that piece's movement)
bool Game::isValidMove(const Square& start, const Square& dest){
    Piece *pieceToMove = board[start.row][start.col];
    Piece *pieceAtDest = board[dest.row][dest.col];

    // Return false if user has selected an empty square or an opposition piece
    if (pieceToMove == nullptr || pieceToMove->getColor() != turn->getColor()){ 
        return false; 
    }

    // Return false if user is trying to move a piece to a square already occupied by a friendly piece
    if (pieceAtDest != nullptr ){ 
        if (pieceAtDest->getColor() == turn->getColor()){
            return false; 
        }
    }

    // Return false if move results in the player whose turn it is being in check
    if (moveResultsInCheck(start, dest)){
        return false;
    }

    return pieceToMove->isLegalMove(start, dest, board);
}


bool Game::shortCastleIsLegal(){
    Piece* kingPiece = board[turn->getKingSq().row][turn->getKingSq().col];
    King* king = dynamic_cast<King*>(kingPiece);
    // If for whatever reason cast fails
    if (king == nullptr){
        std::cerr << "ERROR: FAILED TO FIND KING AT PLAYER.KINGSQ" << std::endl;
        exit(1);
    }

    return king->canCastleShort(board);
}


void Game::shortCastle(){

    // Get current and new (after castling) squares 
    // on which the king & kingside rook are/will be located.
    Square kingSquare, rookSquare, newKingSquare, newRookSquare;
    if (turn->getColor() == PieceColor::WHITE){
        kingSquare = square(0, 4);
        rookSquare = square(0, 7);
        newKingSquare = square(0, 6);
        newRookSquare = square(0, 5);
    }
    else if(turn->getColor() == PieceColor::BLACK){
        kingSquare = square(7, 4);
        rookSquare = square(7, 7);
        newKingSquare = square(7, 6);
        newRookSquare = square(7, 5);   
    }

    // Move king
    Piece* king = board[kingSquare.row][kingSquare.col];
    board[newKingSquare.row][newKingSquare.col] = king;
    turn->setKingSq(newKingSquare);
    board[kingSquare.row][kingSquare.col] = nullptr;
    king->moved();

    // Move rook
    Piece* rook = board[rookSquare.row][rookSquare.col];
    board[newRookSquare.row][newRookSquare.col] = rook;
    board[rookSquare.row][rookSquare.col] = nullptr;
    rook->moved();
}


bool Game::longCastleIsLegal(){
    Piece* kingPiece = board[turn->getKingSq().row][turn->getKingSq().col];
    King* king = dynamic_cast<King*>(kingPiece);
    // If for whatever reason cast fails
    if (king == nullptr){
        std::cerr << "ERROR: FAILED TO FIND KING AT PLAYER.KINGSQ" << std::endl;
        exit(1);
    }

    return king->canCastleLong(board);
}


void Game::longCastle(){

    // Get current and new (after castling) squares 
    // on which the king & kingside rook are/will be located.
    Square kingSquare, rookSquare, newKingSquare, newRookSquare;
    if (turn->getColor() == PieceColor::WHITE){
        kingSquare = square(0, 4);
        rookSquare = square(0, 0);
        newKingSquare = square(0, 2);
        newRookSquare = square(0, 3);      
    } 
    else if(turn->getColor() == PieceColor::BLACK){
        kingSquare = square(7, 4);
        rookSquare = square(7, 0);
        newKingSquare = square(7, 2);
        newRookSquare = square(7, 3);
    }

    // Move king
    Piece* king = board[kingSquare.row][kingSquare.col];
    board[newKingSquare.row][newKingSquare.col] = king;
    turn->setKingSq(newKingSquare);
    board[kingSquare.row][kingSquare.col] = nullptr;
    king->moved();

    // Move rook
    Piece* rook = board[rookSquare.row][rookSquare.col];
    board[newRookSquare.row][newRookSquare.col] = rook;
    board[rookSquare.row][rookSquare.col] = nullptr;
    rook->moved();
}


bool Game::isCheck(){
    return isAttacked(turn->getKingSq(), board, turn->getColor());
}


// Player is in checkmate if:
// - He is currently in check
// - He has no legal moves that can get him out of check
//
// Stalemate if:
// - Has no legal moves that don't put himself in check
// - But is NOT currently in check
// 
// Game is contested if neither of the above are true.
// So this algorithm involves scanning the entire board, checking if there is a legal move the player could make
// that does not result in check. If not, whether it is checkmate or stalemate is determined by whether the player is in check currently.
GameState Game::getGameState(){

    // Scan entire board, checking, for each friendly piece, 
    // if that piece has a legal move that does not result in, or perpetuate, a check 
    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            
            if ( board[i][j] != nullptr && board[i][j]->getColor() == turn->getColor() ){ // If square contains player's piece
                
                // Get all legal destinations for piece at board[i][j]
                Piece* pieceToMove = board[i][j];
                Square sqAtIJ = square(i,j); 
                std::vector<Square> dests = pieceToMove->legalDests(sqAtIJ, board);

                // Iterate through all legal dests for pieceToMove.
                for (auto dest: dests){
                    
                    // If a legal smove is found that does not result in check, game is still contested
                    if (!moveResultsInCheck(sqAtIJ, dest)){
                        return GameState::CONTESTED;
                    }
                }
            }
        }
    }
    // If no move was found that could break the check
    // Checkmate if player is currently in check, otherwise stalemate
    return (isCheck()) ? GameState::CHECKMATE : GameState::STALEMATE;
}


// To determine if a move results in a check for the player making the move,
// we simulate the move taking place on the board, call isCheck(), 
// then revert the board back to it's state prior to simulating the move.
bool Game::moveResultsInCheck(const Square& start, const Square& dest){

    Piece *pieceToMove = board[start.row][start.col];
    Piece *pieceAtDest = board[dest.row][dest.col];

    // Simulate move taking place
    board[dest.row][dest.col] = pieceToMove;
    board[start.row][start.col] = nullptr;
    if ( dynamic_cast<King*>(pieceToMove) ){  // If king is being moved, update player's kingSq attribute
        turn->setKingSq(dest);
    }

    bool check = isCheck();

    // Before returning, revert board & kingSq (if necessary) back to previous state that in was in before simulating the move
    board[start.row][start.col] = pieceToMove;
    board[dest.row][dest.col] = pieceAtDest;
    if ( dynamic_cast<King*>(pieceToMove) ){
        turn->setKingSq(start);
    }

    return check;
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