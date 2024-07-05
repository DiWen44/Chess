#include <array>
#include <vector>
#include <cmath>
#include <algorithm>

#include "piece.hpp"
#include "queen.hpp"


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


// This concatenates into 1 vector the results of legalStraightDests() and legalDiagDests()
std::vector<Square> Queen::legalDests(const Square& start, const std::array<std::array<Piece*, 8>, 8>& board){
    std::vector<Square> res;
    std::vector<Square> straightDests = legalStraightDests(start, board);
    std::vector<Square> diagDests = legalDiagDests(start, board);

    // Concatenate straight & diagonal dests into 1 vector to get all possible legal destinations
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
    else if (abs(disp[0]) == abs(disp[1])){
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


// This is exactly the same algorithm used for the bishop's implementation of legalDests()
std::vector<Square> Queen::legalDiagDests(const Square& start, const std::array<std::array<Piece*, 8>, 8>& board){

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
    i = start.row;
    j = start.col;
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

    // Concatenate 1st and 2nd axes' destinations into single dests vector, then return
    std::vector<Square> dests;
    dests.insert(dests.end(), dests1stAxis.begin(), dests1stAxis.end());
    dests.insert(dests.end(), dests2ndAxis.begin(), dests2ndAxis.end());
    return dests;
}


// This is exactly the same algorithm used for the rook's implementation of legalDests()
std::vector<Square> Queen::legalStraightDests(const Square& start, const std::array<std::array<Piece*, 8>, 8>& board){

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

    // Concatenate vertical and horizontal destinations into single dests vector, then return
    std::vector<Square> dests;
    dests.insert(dests.end(), verticalDests.begin(), verticalDests.end());
    dests.insert(dests.end(), horizontalDests.begin(), horizontalDests.end());
    return dests;
}
