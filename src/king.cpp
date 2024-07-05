#include <array>
#include <vector>
#include <cmath>

#include "piece.hpp"
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
        // Get piece at start + displacement
        Piece *pieceAtDest = board[start.row+displacements[i][0]][start.col+displacements[i][1]];
        
        // If destination square is either empty or has opposition piece
        if (pieceAtDest == nullptr){ 
            dests.push_back( square(start.row+displacements[i][0], start.col+displacements[i][1]) ); 
        } else if (pieceAtDest->getColor() != color){
            dests.push_back( square(start.row+displacements[i][0], start.col+displacements[i][1]) );
        }
    }
}
