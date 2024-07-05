#include <array>
#include <vector>
#include <cmath>

#include "piece.hpp"
#include "pawn.hpp"


Pawn::Pawn(PieceColor color) : Piece(color){ 
    canBeCapturedEnPassant = false; 
}

Pawn::Pawn() : Piece(){}

char Pawn::toChar(){ return (color==PieceColor::WHITE) ? 'P' : 'p'; }


bool Pawn::isLegalMove(const Square& start, const Square& dest, const std::array<std::array<Piece*, 8>, 8>& board) {
    // PAWN MOVE CONDITIONS:
    // - Can move 1 row forward on same col if no piece at dest square
    // - Can move diagonally by 1 and take piece if opposition piece is on that square
    // - Can move 2 rows forward on same col if at starting position (row 1 for white, row 6 for black)
    //   and if no piece is in it's path to or at the destination square.
    // - Can take en passant by moving 1 square diagonally behind a pawn that has advanced by 2 squares, which captures that pawn.
    //   Only possible if the opposing pawn advanced 2 squares on the previous turn, and if the destination square is vacant.
    //
    // Note that for black pawns, a move "forward" will have negative vertical (1st component) displacement,
    // as black pieces start on the last 2 rows and advance towards the first 2


    Piece* pieceAtDest = board[dest.row][dest.col];
    std::array<int, 2> disp = displacement(start, dest);

    // White pawns
    if (disp[0] > 0 && color == PieceColor::WHITE){

        // Moving into an empty square
        if (pieceAtDest == nullptr){

            // Moving 1 square forward
            if  (disp[0] == 1 && disp[1] == 0) {
                return true;
            }
            // Moving 2 squares forward from starting rank
            else if ( (disp[0] == 2 && disp[1] == 0) && (start.row == 1) && (board[dest.row-1][dest.col] == nullptr)){
                return true;
            }
        }
        // Attacking diagonally 1 space
        else if ( (disp[0] == 1 && abs(disp[1]) == 1) && (pieceAtDest->getColor() == PieceColor::BLACK) ) {
            return true;
        }
    }

    // Black pawns
    else if (disp[0] < 0 && color == PieceColor::BLACK){

        // Moving into an empty square
        if (pieceAtDest == nullptr){

            // Moving 1 square forward
            if  (disp[0] == -1 && disp[1] == 0) {
                return true;
            }
            // Moving 2 squares forward from starting rank
            else if ( (disp[0] == -2 && disp[1] == 0) && (start.row == 6) && (board[dest.row-1][dest.col] == nullptr)){
                return true;
            }
        }
        // Attacking diagonally 1 space
        else if ( (disp[0] == -1 && abs(disp[1]) == 1) && (pieceAtDest->getColor() == PieceColor::WHITE) ) {
            return true;
        }
    }

    return false; // return false if has not returned yet
}


std::vector<Square> Pawn::legalDests(const Square& start, const std::array<std::array<Piece*, 8>, 8>& board) {
    // Note that for black pawns, a move "forward" will have negative vertical (1st component) displacement,
    // as black pieces start on the last 2 rows and advance towards the first 2

    std::vector<Square> dests;

    // White pawns
    if(color == PieceColor::WHITE){

        // Moving 1 square forward
        if (board[start.row+1][start.col] == nullptr){
            dests.push_back( square(start.row+1, start.col) );

            // Moving 2 squares forward from starting square
            if (board[start.row+2][start.col] == nullptr && start.row==1){
                dests.push_back( square(start.row+2, start.col) );
            }                
        } 
        
        // Attacking diagonally by 1 square.
        Piece* diagUpRight =  board[start.row+1][start.col+1]; // Piece diagonally right and upwards 1 square
        Piece* diagUpLeft =  board[start.row+1][start.col-1]; // Piece diagonally left and upwards 1 square
        if ( diagUpRight->getColor() == PieceColor::BLACK) { 
            dests.push_back( square(start.row+1, start.col+1) );
        }
        if ( diagUpLeft->getColor() == PieceColor::BLACK) { 
            dests.push_back( square(start.row+1, start.col-1) ); 
        }
    }

    // Black pawns
    else if(color == PieceColor::BLACK){

        // Moving 1 square forward.
        if (board[start.row-1][start.col] == nullptr){
            dests.push_back( square(start.row-1, start.col) );

            // Moving 2 squares forward from starting square.
            if (board[start.row-2][start.col] == nullptr && start.row==1){
                dests.push_back( square(start.row-2, start.col) );
            }                
        } 
        
        // Attacking diagonally by 1 square.
        Piece* diagUpRight =  board[start.row-1][start.col+1]; // Piece diagonally right and upwards 1 square.
        Piece* diagUpLeft =  board[start.row-1][start.col-1]; // Piece diagonally left and upwards 1 square.
        if ( diagUpRight != nullptr && diagUpRight->getColor() == PieceColor::BLACK ) { 
            dests.push_back( square(start.row-1, start.col+1) );
        }
        if ( diagUpRight != nullptr && diagUpLeft->getColor() == PieceColor::BLACK ) { 
            dests.push_back( square(start.row-1, start.col-1) ); 
        }
    }

    return dests;
}


bool Pawn::canBeCapturedEP(){
    return canBeCapturedEnPassant;
}


bool Pawn::toggleEP(){
    canBeCapturedEnPassant = !canBeCapturedEnPassant;
}