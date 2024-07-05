#include <array>
#include <vector>
#include <cmath>
#include <algorithm>

#include "piece.hpp"
#include "bishop.hpp"


Bishop::Bishop(PieceColor color) : Piece(color){}


char Bishop::toChar(){ return (color==PieceColor::WHITE) ? 'B' : 'b'; }


bool Bishop::isLegalMove(const Square& start, const Square& dest, const std::array<std::array<int, 8>, 8>& board){
    // BISHOP MOVE CONDITIONS: Can move by the same number of rows as columns e.g. (1,1), (3,3), if it's path is not blocked by another piece.
    std::array<int, 2> disp = displacement(start, dest);
    if (abs(disp[0]) == abs(disp[1])){ // Move is diagonal if absolute value of row (vertical) displacement = absolute value of column (horizontal) displacement
        return isPathClear(start, dest, board);
    }
    return false;
}


// This algorithms involves scanning along the 2 axes of diagonal movement: bottomleft-topright, and topleft-bottomright
// where the origin of these axis is the start square (on which this rook is located).
//
// First we create an vector of legal destination squares.
// Then we find the bottomleftmost position on the bottomleft-topright axis, and set iterators i and j equal to its row and column respectively
// we scan along this axis (i.e. incrementing both i and j until we reach the other end of the board, when i=8 or j=8 ), 
// 
// We then use this process to find legal moves:
//
// FOR EACH SQUARE ENCOUNTERED BY ITERATORS:
//
// - IF ITERATORS ON EMPTY SQUARE - add square to possible destinations
// 
// - IF ENCOUNTERED NON-EMPTY SQUARE BEFORE REACHING START SQUARE:
// - - Clear/empty legal destinations vector
// - - If square is occupied by enemy piece, add square to legal destinations, as enemy piece can be captured
//
// - IF ITERATORS AT START SQUARE - Pass over start square without action
//
// - IF ENCOUNTERED NON-EMPTY SQUARE AFTER REACHING START SQUARE:
// - - If square is occupied by enemy piece, add square to legal destinations.
// - - Stop iterating - we've found all possible destinations on this axis
//
// 
// Then we apply this same process, but along the topleft-bottomright axis
// (i.e. starting i and j at topleftmost point on axis, then decrementing i while incrementing j to 
// traverse the axis until we reach the other end of the board, when either i=0 or j=7)
std::vector<Square> Bishop::legalDests(const Square& start, const std::array<std::array<int, 8>, 8>& board){
    
    // 1ST (BOTTOMLEFT-TOPRIGHT) AXIS
    std::vector<Square> dests1stAxis; // Legal destination squares on the 1st (bottomleft-topright) axis
    // Get bottom-left-most point on the bottomleft-topright axis
    // By iterating bottomleft-wards from start square until we reach the edge of the board i.e. when either i or j equals 0
    int i = start.row;
    int j = start.col;
    while (i >= 0 && j >= 0){
        i--;
        j--;
    }
    Square bottomLeft = square(i, j);

     // Starting from bottomleft, iterate over axis until the other end of the board is reached
    i = bottomLeft.row;
    j = bottomLeft.col;
    while (i < 8 && j < 8){

        // If encounters non-empty square before reaching rook's position
        if (board[i][j] != nullptr && i < start.row){
            dests1stAxis.clear(); // Clear dests - Those squares are not valid dests if there is a piece between them and the start square

            // If encountered piece is enemy, can capture that piece
            // So add its square to legal dests
            if (board[i][j]->getColor() != color){
                    dests1stAxis.push_back( square(i, j) );
            }
        }

        // When i and j reach bishop's position / start square
        else if (i == start.row && j == start.col){ 
            continue;
        }

        // If encounters non-empty square after bishop's position
        else if (board[i][j] != nullptr && i > start.row){

            // If encountered piece is enemy, can capture that piece
            // So add its square to legal dests
            if (board[i][j]->getColor() != color){
                    dests1stAxis.push_back( square(i, j) );
            }
            break; // Stop scanning - found all possible destinations on this column
        }
        
        // Default case - If i and j on an empty square
        else {
            dests1stAxis.push_back( square(i, j) );
        }

        i++;
        j++;
    }

    // 2ND (TOPLEFT-BOTTOMRIGHT) AXIS
    std::vector<Square> dests2ndAxis; // Legal destination squares on the 2nd (topleft-bottomright) axis
    // Get top-left-most point on the topleft-bottomright axis
    // By iterating topleft-wards from start square until we reach the edge of the board i.e. when either i or j equals 0
    int i = start.row;
    int j = start.col;
    while (i < 8 && j > 0){
        i++;
        j--;
    }
    Square topLeft = square(i, j);

    // Starting from topleft, iterate over axis until the other end of the board is reached
    i = topLeft.row;
    j = topLeft.col;
    while (i >= 0 && j < 8){

        // If encounters non-empty square before reaching rook's position
        if (board[i][j] != nullptr && i < start.row){
            dests2ndAxis.clear(); // Clear dests - Those squares are not valid dests if there is a piece between them and the start square

            // If encountered piece is enemy, can capture that piece
            // So add its square to legal dests
            if (board[i][j]->getColor() != color){
                    dests2ndAxis.push_back( square(i, j) );
            }
        }

        // When i and j reach bishop's position / start square
        else if (i == start.row && j == start.col){ 
            continue;
        }

        // If encounters non-empty square after bishop's position
        else if (board[i][j] != nullptr && i > start.row){

            // If encountered piece is enemy, can capture that piece
            // So add its square to legal dests
            if (board[i][j]->getColor() != color){
                    dests2ndAxis.push_back( square(i, j) );
            }
            break; // Stop scanning - found all possible destinations on this column
        }
        
        // Default case - If i and j on an empty square
        else {
            dests2ndAxis.push_back( square(i, j) );
        }

        i--;
        j++;
    }

    // Concatenate 1st and 2nd axes' destinations into dests vector, then return
    std::vector<Square> dests;
    std::merge(dests1stAxis.begin(), dests1stAxis.end(), dests2ndAxis.begin(), dests2ndAxis.end(), dests.begin());
    return dests;
}


bool Bishop::isPathClear(const Square& start, const Square& dest, const std::array<std::array<int, 8>, 8>& board){

    std::array<int, 2> disp = displacement(start, dest);

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
