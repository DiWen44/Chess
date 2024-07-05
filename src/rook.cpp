#include <array>
#include <vector>
#include <cmath>
#include <algorithm>

#include "piece.hpp"
#include "rook.hpp"


Rook::Rook(PieceColor color) : Piece(color){}


char Rook::toChar(){ return (color==PieceColor::WHITE) ? 'R' : 'r'; }


bool Rook::isLegalMove(const Square& start, const Square& dest, const std::array<std::array<int, 8>, 8>& board){
    std::array<int, 2> disp = displacement(start, dest);
    // ROOK MOVE CONDITIONS: Can move by any number of columns on the same row (horizontally), 
    // or by any number of rows on the same column (vertically), 
    // provided it's path isn't blocked by another piece.
    if (disp[0] == 0 || disp[1] == 0){
        return isPathClear(start, dest, board);
    }
}


// This algorithm for finding legal destination squares involves scanning along hypothetical horizontal and vertical axes of the board,
// where the origin of these axis is the start square (on which this rook is located).
//
// First we create an vector of legal destination squares.
// we scan along the vertical axis (i.e. keep column constant, iterate over rows), 
// setting our iterator to begin at the first row (i.e. row 0) and to continue until the last row (i.e. row 8)
// 
// We then use this process to find legal moves:
//
// FOR EACH SQUARE ENCOUNTERED BY ITERATOR:
//
// - IF ITERATOR IS ON EMPTY SQUARE - add square to possible destinations
// 
// - IF ENCOUNTERED NON-EMPTY SQUARE BEFORE REACHING START SQUARE:
// - - Clear/empty legal destinations vector
// - - If square is occupied by enemy piece, add square to legal destinations, as enemy piece can be captured
//
// - IF ITERATOR AT START SQUARE - Pass over start square without action
//
// - IF ENCOUNTERED NON-EMPTY SQUARE AFTER REACHING START SQUARE:
// - - If square is occupied by enemy piece, add square to legal destinations.
// - - Stop iterating - we've found all possible destinations on this axis
//
// 
// Then we apply this same process, but along the horizontal axis (i.e. keep row constant, iterate over columns)
std::vector<Square> Rook::legalDests(const Square& start, const std::array<std::array<int, 8>, 8>& board){

    // VERTICAL AXIS
    std::vector<Square> verticalDests; // Legal destination squares on vertical axis

    // Scanning possible vertical moves (i.e. where start column = dest column)
    // Start from first row on the starting square's column, scan to last row on the same column.
    int i = 0;
    while (i < 8){

        // If encounters non-empty square before reaching rook's position
        if (board[i][start.col] != nullptr && i < start.row){
            verticalDests.clear(); // Clear dests - Those squares are not valid dests if there is a piece between them and the start square

            // If encountered piece is enemy, can capture that piece
            // So add its square to legal dests
            if (board[i][start.col]->getColor() != color){
                    verticalDests.push_back( square(i, start.col) );
            }
        }

        // When i reaches rook's position / start square
        else if (i == start.row){ 
            continue;
        }

        // If encounters non-empty square after rook's position
        else if (board[i][start.col] != nullptr && i > start.row){

            // If encountered piece is enemy, can capture that piece
            // So add its square to legal dests
            if (board[i][start.col]->getColor() != color){
                    verticalDests.push_back( square(i, start.col) );
            }
            break; // Stop scanning - found all possible destinations on this column
        }
        
        // Default case - If i is on an empty square
        else {
            verticalDests.push_back( square(i, start.col) );
        }
        
        i++;
    }

    // HORIZONTAL AXIS
    std::vector<Square> horizontalDests; // Legal destination squares on horizontal axis

    // Scanning possible horizontal moves (i.e. where start row = dest row)
    // Use the same principles as above, except instead of vertical, scan horizontally.
    // Start from first column on the starting square's row, scan to last column on the same row.
    int j = 0;
    while (j < 8){

        // If encounters non-empty square before reaching rook's position
        if (board[start.row][j] != nullptr && j < start.col){
            horizontalDests.clear(); // Clear dests - Those squares are not valid dests if there is a piece between them and the start square

            // If encountered piece is enemy, can capture that piece
            // So add its square to legal dests
            if (board[start.row][j]->getColor() != color){
                    horizontalDests.push_back( square(start.row, j) );
            }
        }

        // When j reaches rook's position/start square, simply pass over
        else if (j == start.col){ 
            continue;
        }

        // If encounters non-empty square after rook's position
        else if (board[start.row][j] != nullptr && j > start.col){

            // If encountered piece is enemy, can capture that piece
            // So add its square to legal dests
            if (board[start.row][j]->getColor() != color){
                    horizontalDests.push_back( square(start.row, j) );
            }
            break; // Stop scanning - found all possible destinations on this row
        }
        
        // Default case - If j is on an empty square
        else {
            horizontalDests.push_back( square(start.row, j) );
        }
        
        j++;
    }

    // Concatenate vertical and horizontal destinations into dests vector, then return
    std::vector<Square> dests;
    std::merge(verticalDests.begin(), verticalDests.end(), horizontalDests.begin(), horizontalDests.end(), dests.begin());
    return horizontalDests;
}


bool Rook::isPathClear(const Square& start, const Square& dest, const std::array<std::array<int, 8>, 8>& board){

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
}
