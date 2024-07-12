#include <array>
#include <vector>
#include <cmath>

#include "piece.hpp"
#include "square.hpp"
#include "king.hpp"


King::King(PieceColor color) : Piece(color){}


King::King() : Piece(){}


char King::toChar(){ return (color==PieceColor::WHITE) ? 'K' : 'k'; }


bool King::isLegalMove(const Square& start, const Square& dest, const std::array<std::array<Piece*, 8>, 8>& board){
    // KING MOVE CONDITIONS:
    // - Can move by 1 row (horizontally 1 space) in any direction
    // - Can move by 1 column (vertically 1 space) in any direction
    // - Can move by 1 row and 1 column (diagonally 1 space) in any direction.
    // - Can castle if neither king nor rook has moved, and if no pieces are between the rook and king
    std::array<int, 2> disp = displacement(start, dest);
    return ( (abs(disp[0]) == 1 && disp[1] == 0) || (disp[0] == 0 && abs(disp[1]) == 1) || (abs(disp[0]) == 1 && abs(disp[1]) == 1) );
}


std::vector<Square> King::legalDests(const Square& start, const std::array<std::array<Piece*, 8>, 8>& board){
    std::vector<Square> dests;

    // Array of valid displacements (differences between start and dest squares in form {row, col}) for a king move
    // These will each in turn be added to the starting square to get potential destination squares
    std::array<std::array<int, 2>, 8> displacements = { { {1,1}, {1,0}, {1,-1}, {0,1}, {0,-1}, {-1,1}, {-1,0}, {-1,-1} } };

    for (int i = 0; i < 8; i++){

        int destRow = start.row+displacements[i][0];
        int destCol = start.col+displacements[i][1];

        // If calculated new row & column lie within the dimensions of the board
        if ( (destRow >= 0 && destRow < 8) && (destCol >= 0 && destCol < 8) ){

            Piece *pieceAtDest = board[destRow][destCol];
            
            // If destination square is either empty or has opposition piece
            if (pieceAtDest == nullptr || pieceAtDest->getColor() != color){ 
                dests.push_back( square(destRow, destCol) ); 
            }
        }
    }
    return dests;
}


bool King::canCastleShort(const std::array<std::array<Piece*, 8>, 8>& board){

    if (hasMovedFromOrigin){ return false; } // Can't castle if king has moved

    Square s1, s2; // These 2 squares are the squares that the king will move through when castling. 
    Square rookSq; // Starting square of kingside rook
    if (color == PieceColor::WHITE){
        s1 = square(0, 5);
        s2 = square(0, 6);
        rookSq = square(0, 7);  
    } 
    else if(color == PieceColor::BLACK){
        s1 = square(7, 5);
        s2 = square(7, 6);
        rookSq = square(7, 7);   
    }

    // If kingside rook is not at starting square i.e. 
    // the piece at that square has moved (meaning that piece is not the rook that was originally there)
    // or that square is empty, then can't castle
    if (board[rookSq.row][rookSq.col] == nullptr || board[rookSq.row][rookSq.col]->hasMoved()){
        return false;
    }

    // Can't castle if there's a piece on either of the squares that the king passes over
    if (board[s1.row][s1.col] != nullptr || board[s2.row][s2.col] != nullptr){
        return false;
    }

    // Can't castle if king would be passing through an attacked square
    if (isAttacked(s1, board, color) || isAttacked(s2, board, color)){
        return false;
    }

    return true;
}


bool King::canCastleLong(const std::array<std::array<Piece*, 8>, 8>& board){

    if (hasMovedFromOrigin){ return false; } // Can't castle if king has moved

    Square s1, s2, s3; // These 3 squares are the squares that the king will move through when castling. 
    Square rookSq; // Starting square of queenside rook
    if (color == PieceColor::WHITE){
        s1 = square(0, 1);
        s2 = square(0, 2);
        s3 = square(0, 3);
        rookSq = square(0, 0);          
    } 
    else if(color == PieceColor::BLACK){
        s1 = square(7, 1);
        s2 = square(7, 2);
        s3 = square(7, 3);
        rookSq = square(7, 0);
    }

    // If queenside rook is not at starting square i.e. that square is empty or
    // the piece at that square has moved (meaning that piece is not the rook that was originally there),
    // then can't castle
    if (board[rookSq.row][rookSq.col] == nullptr || board[rookSq.row][rookSq.col]->hasMoved()){
        return false;
    }

    // Can't castle if there's a piece on a square that the king passes over
    if (board[s1.row][s1.col] != nullptr || board[s2.row][s2.col] != nullptr|| board[s3.row][s3.col] != nullptr){
        return false;
    }

    // Can't castle if king would be passing through an attacked square
    if (isAttacked(s1, board, color) || isAttacked(s2, board, color) || isAttacked(s3, board, color)){
        return false;
    }

    return true;
}
