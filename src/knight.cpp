#include <array>
#include <vector>
#include <cmath>

#include "piece.hpp"
#include "knight.hpp"


Knight::Knight(PieceColor color) : Piece(color){}


Knight::Knight() : Piece(){}


char Knight::toChar(){ return (color==PieceColor::WHITE) ? 'N' : 'n'; }


bool Knight::isLegalMove(const Square& start, const Square& dest, const std::array<std::array<Piece*, 8>, 8>& board){
    // KNIGHT MOVE CONDITIONS: Can move either 2 rows and 1 column, or by 1 row and 2 columns, in any direction
    // Unlike other pieces, the knight can do this even if another piece is in it's path (jumping).
    std::array<int, 2> disp = displacement(start, dest);
    return ( (abs(disp[0]) == 1 && abs(disp[1]) == 2) || (abs(disp[0]) == 2 && abs(disp[1])  == 1) );
}


std::vector<Square> Knight::legalDests(const Square& start, const std::array<std::array<Piece*, 8>, 8>& board){
    std::vector<Square> dests;

    // Array of valid displacements (differences between start and dest squares in form {row, col}) for a knight move
    // These will each in turn be added to the starting square to get potential destination squares
    std::array<std::array<int, 2>, 8> displacements = { { {2,1}, {2,-1}, {1,2}, {1, -2}, {-1,2}, {-1,-2}, {-2,1}, {-2,-1} } };

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