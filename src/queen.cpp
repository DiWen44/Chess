#include <array>
#include <vector>
#include <cmath>
#include <algorithm>

#include "piece.hpp"
#include "queen.hpp"
#include "bishop.hpp"
#include "rook.hpp"

Queen::Queen(PieceColor color) : Piece(color){} 


Queen::Queen() : Piece(){} 


char Queen::toChar(){ return (color==PieceColor::WHITE) ? 'Q' : 'q'; }


bool Queen::isLegalMove(const Square& start, const Square& dest, const std::array<std::array<Piece*, 8>, 8>& board){
    // QUEEN MOVE CONDITIONS: 
    // - Can move by any number of columns on the same row (horizontally).
    // - Can move by any number of rows on the same column (vertically).
    // - Can move by the same number of rows as columns (diagonally).
    // Provided it's path isn't blocked by another piece.
    std::array<int, 2> disp = displacement(start, dest);
    if (disp[0] == 0 || disp[1] == 0 || abs(disp[0]) == abs(disp[1])){ // Check if move is horizontal, vertical or diagonal
        return isPathClear(start, dest, board);
    }
    return false;
}


// This combines the bishop's and rook's implementations of legalDests(), 
// to get the legal diagonal and straight (horizontal & vertical) destinations respectively.
// These 2 lists of destinations are then combined and returned to give the complete list of legal destinations for the queen.
std::vector<Square> Queen::legalDests(const Square& start, const std::array<std::array<Piece*, 8>, 8>& board){

    std::array<std::array<Piece*, 8>, 8> boardCopy = board; // Make modifiable copy of board

    // Replace queen with a rook at the start square on the board copy, then get it's legal destinations.
    // This will get the legal horizontal and vertical destinations for the queen on the original board.
    Rook rook(color);
    boardCopy[start.row][start.col] = &rook;
    std::vector<Square> straightDests = rook.legalDests(start, boardCopy);

    // Put a bishop at the start square on the board copy, then get it's legal destinations.
    // This will get the legal diagonal destinations for the queen on the original board.
    Bishop bish(color);
    boardCopy[start.row][start.col] = &bish;
    std::vector<Square> diagDests = bish.legalDests(start, boardCopy);

    // Concatenate straight & diagonal dests into 1 vector to get all possible legal destinations
    std::vector<Square> res;
    res.insert(res.end(), straightDests.begin(), straightDests.end());
    res.insert(res.end(), diagDests.begin(), diagDests.end());

    return res;
}


bool Queen::isPathClear(const Square& start, const Square& dest, const std::array<std::array<Piece*, 8>, 8>& board){

    std::array<int, 2> disp = displacement(start, dest);

    // Horizontal move
    if (disp[0] == 0){
        // Whether to increment or decrement j to scan from start to dest
        bool incJ = start.col < dest.col;
        int j = (incJ) ? start.col+1 : start.col-1;

        while(j != dest.col){
            if (board[start.col][j] != nullptr){  // If piece encountered
                return false; 
            }
            if (incJ) { j++; } else { j--; }; // Bring j 1 square closer to dest
        }
        return true; // Return true if no pieces encountered in the way
    } 

    // Vertical move
    else if (disp[1] == 0){
        // Whether to increment or decrement i to scan from start to dest
        bool incI = start.row < dest.row;
        int i = (incI) ? start.row+1 : start.row-1;

        while(i != dest.row){
            if (board[i][start.col] != nullptr){  // If piece encountered
                return false; 
            }
            if (incI) { i++; } else { i--; }; // Bring i 1 square closer to dest
        }
        return true; // Return true if no pieces encountered in the way
    }

    // Diagonal move
    else if (abs(disp[0]) == abs(disp[1])){ // Move is diagonal if absolute value of row (vertical) displacement = absolute value of column (horizontal) displacement
        bool incI = start.row < dest.row; // Whether to increment or decrement i to scan from start to dest
        bool incJ = start.col < dest.col; // Whether to increment or decrement j to scan from start to dest

        int i = (incI) ? start.row+1 : start.row-1;
        int j = (incJ) ? start.col+1 : start.col-1;

        // Scan path from start to dest
        while(i != dest.row && j != dest.col){
            if ( board[i][j] != nullptr ){ // If piece encountered
                return false;
            }

            // Traverse by 1 square diagonally to get closer to dest
            if (incI) { i++; } else { i--; }; 
            if (incJ) { j++; } else { j--; };
        }
        return true; // Return true if no pieces encountered in the way
    }
}
