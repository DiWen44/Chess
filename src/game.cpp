#include <iostream>
#include <string>
#include <vector>
#include <cmath>

#include "game.hpp"
#include "piece.hpp"
#include "move.hpp"


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

    this->turn = PieceColor::WHITE;
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
    turn = (turn == PieceColor::WHITE) ? PieceColor::BLACK : PieceColor::WHITE;
}


PieceColor Game::getTurn(){
    return turn;
}


std::string Game::getTurnStr(){
    return (turn == PieceColor::WHITE) ? "WHITE" : "BLACK";
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


void Game::movePiece(const Move& mv){
    Piece pieceToMove = board[mv.startRow][mv.startCol];
    Piece pieceAtDest = board[mv.destRow][mv.destCol];

    board[mv.destRow][mv.destCol] = pieceToMove;
    board[mv.startRow][mv.startCol] = nonePiece(); // Vacate start square by setting it to the "none" piece
}


bool Game::isLegalMove(const Move& mv){

    Piece pieceToMove = board[mv.startRow][mv.startCol];
    Piece pieceAtDest = board[mv.destRow][mv.destCol];
    int* disp = displacement(mv);

    // Return false here if:
    // - Empty square was selected as start
    // - Attempting to move opponent's piece
    // - Destination square has one of the mover's pieces on it already
    if (isNone(pieceToMove) || pieceToMove.color != turn || pieceAtDest.color == pieceToMove.color){ 
        return false;
    }

    switch (pieceToMove.type){

        case PieceType::PAWN:
            // PAWN MOVE CONDITIONS:
            // - Can move 1 row forward on same col if no piece at dest square
            // - Can move diagonally by 1 and take piece if opposition piece is on that square
            // - Can move 2 rows forward on same col if at starting position (row 1 for white, row 6 for black)
            //   and if no piece is in it's path to or at the destination square.
            // - Can take en passant by moving 1 square diagonally behind a pawn that has advanced by 2 squares, which captures that pawn.
            //   Only possible if the opposing pawn advanced 2 squares on the previous turn, and if the destination square is vacant.
            //
            // Note that for black pawns, a move "forward" will have negative vertical displacement,
            // as black pieces start on the last 2 rows and advance towards the first 2

            // White pawns
            if (disp[0] > 0 && pieceToMove.color == PieceColor::WHITE){
                // Moving 1 square forward
                if  (disp[0] == 1 && disp[1] == 0 && isNone(pieceAtDest)) {
                    return true;
                }
                // Attacking diagonally 1 space
                else if ( (disp[0] == 1 && abs(disp[1]) == 1) && (pieceAtDest.color == PieceColor::BLACK) ) {
                    return true;
                }
                // Moving 2 squares forward
                if ( (disp[0] == 2 && disp[1] == 0) && (mv.startRow == 1) && (isNone(board[mv.destRow-1][mv.destCol])) && isNone(pieceAtDest) ){
                    return true;
                }
            }

            // Black pawns
            else if (disp[0] < 0 && pieceToMove.color == PieceColor::BLACK){
                // Moving 1 square forward
                if  ( (disp[0] == -1 && disp[1]) == 0 && isNone(pieceAtDest) ) {
                    return true;
                }
                // Attacking diagonally forward
                else if ( (disp[0] == -1 && abs(disp[1]) == 1) && (pieceAtDest.color == PieceColor::WHITE) ) {
                    return true;
                }
                // Moving 2 squares forward
                if ( (disp[0] == -2 && disp[1] == 0) && (mv.startRow == 1) && (isNone(board[mv.destRow+1][mv.destCol])) && isNone(pieceAtDest) ){
                    return true;
                }
            }
            break;
        
        case PieceType::KNIGHT:
            // KNIGHT MOVE CONDITIONS: Can move either 2 rows and 1 column, or by 1 row and 2 columns, in any direction
            // Unlike other pieces, the knight can do this even if another piece is in it's path (jumping).
            return ( (abs(disp[0]) == 1 && abs(disp[1]) == 2) || (abs(disp[0]) == 2 && abs(disp[1])  == 1) );
            break;

        case PieceType::BISHOP:
            // BISHOP MOVE CONDITIONS: Can move by the same number of rows as columns e.g. (1,1), (3,3), if it's path is not blocked by another piece.
            if (abs(disp[0]) == abs(disp[1])){
                return pathClear(mv);
            }
            break;
        
        case PieceType::ROOK:
            // ROOK MOVE CONDITIONS: Can move by any number of columns on the same row (horizontally), 
            // or by any number of rows on the same column (vertically), 
            // provided it's path isn't blocked by another piece.
            if (disp[0] == 0 || disp[1] == 0){
                return pathClear(mv);
            }
            break;

        case PieceType::QUEEN:
            // QUEEN MOVE CONDITIONS: 
            // - Can move by any number of columns on the same row (horizontally).
            // - Can move by any number of rows on the same column (vertically).
            // - Can move by the same number of rows as columns (diagonally).
            // Provided it's path isn't blocked by another piece.
            if (disp[0] == 0 || disp[1] == 0 || abs(disp[0]) == abs(disp[1])){
                return pathClear(mv);
            }
            break;

        case PieceType::KING:
            // KING MOVE CONDITIONS:
            // - Can move by 1 row (horizontally 1 space) in any direction
            // - Can move by 1 column (vertically 1 space) in any direction
            // - Can move by 1 row and 1 column (diagonally 1 space) in any direction.
            // - Can castle if neither king nor rook has moved, and if no pieces are between the rook and king
            return ( (abs(disp[0]) == 1 && disp[1] == 0) || (disp[0] == 0 && abs(disp[1]) == 1) || (abs(disp[0]) == 1 && abs(disp[1]) == 1) );
            break;
        
        return false; // Return false if method has not returned yet
    }
}


bool Game::pathClear(const Move& mv){

    int* disp = displacement(mv);

    // Diagonal move
    if (abs(disp[0]) == abs(disp[1])){
        bool incI = mv.startRow < mv.destRow;
        bool incJ = mv.startCol < mv.destCol;
        int i = (incI) ? mv.startRow+1 : mv.startRow-1;
        int j = (incJ) ? mv.startCol+1 : mv.startCol-1;

        while(i != mv.destRow && j != mv.destCol){
            if ( !isNone(board[i][j]) ){ // If piece encountered
                return false;
            }

            // Traverse by 1 square diagonally to get closer to dest
            if (incI) { i++; } else { i--; }; 
            if (incJ) { j++; } else { j--; };
        }
        return true; // Return true if no pieces encountered in the way
    }

    // Horizontal move
    else if (disp[0] == 0){
        bool incJ = mv.startCol < mv.destCol;
        int j = (incJ) ? mv.startCol+1 : mv.startCol-1;

        while(j != mv.destCol){
            if ( !isNone(board[mv.startCol][j]) ){  // If piece encountered
                return false; 
            }
            if (incJ) { j++; } else { j--; }; // Bring j 1 square closer to dest
        }
        return true; // Return true if no pieces encountered in the way
    } 

    // Vertical move
    else if (disp[1] == 0){
        bool incI = mv.startRow < mv.destRow;
        int i = (incI) ? mv.startRow+1 : mv.startRow-1;

        while(i != mv.destRow){
            if ( !isNone(board[i][mv.startCol]) ){  // If piece encountered
                return false; 
            }
            if (incI) { i++; } else { i--; }; // Bring i 1 square closer to dest
        }
        return true; // Return true if no pieces encountered in the way
    }
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

