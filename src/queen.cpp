#include <array>
#include <vector>
#include <cmath>

#include "piece.hpp"
#include "queen.hpp"


Queen::Queen(PieceColor color) : Piece(color){} 


char Queen::toChar(){ return (color==PieceColor::WHITE) ? 'Q' : 'q'; }


bool Queen::isLegalMove(const Square& start, const Square& dest, const std::array<std::array<int, 8>, 8>& board){
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
std::vector<Square> Queen::legalDests(const Square& start, const std::array<std::array<int, 8>, 8>& board){
    std::vector<Square> res;
    std::vector<Square> straightDests = legalStraightDests(start, board);
    std::vector<Square> diagDests = legalDiagDests(start, board);

    // Concatenate straight & diagonal dests into 1 vector to get all possible legal destinations
    res.insert(res.end(), straightDests.begin(), straightDests.end());
    res.insert(res.end(), diagDests.begin(), diagDests.end());

    return res;
}


bool Queen::isPathClear(const Square& start, const Square& dest, const std::array<std::array<int, 8>, 8>& board){

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



std::vector<Square> Queen::legalDiagDests(const Square& start, const std::array<std::array<int, 8>, 8>& board){
    std::vector<Square> dests;

    int i = start.row;
    int j = start.col;
    // Scanning diagonally right-upwards
    while (i < 8 && j < 8){

        // If non-empty square encountered, stop traversing
        if (board[i][j] != nullptr){ 
            // If opponent's piece encountered, add that square to valid moves,
            // as taking opposition piece is valid move
            if (board[i][j]->getColor() != color){
                dests.push_back( square(i, j) );
            }
            break;
        }

        dests.push_back( square(i, j) );
        i++;
        j++;
    }

    // Reset I and J to bishop's position
    i = start.row;
    j = start.col;
    // Scanning diagonally right-downwards
    while (i >= 0 && j < 8){
        // If non-empty square encountered, we need to stop traversing
        if (board[i][j] != nullptr){ 
            // If opponent's piece encountered, add that square to valid moves,
            // as taking opposition piece is valid move
            if (board[i][j].color != color){
                dests.push_back( square(i, j) );
            }
            break;
        }

        dests.push_back( square(i, j) );
        i--;
        j++;
    }

    i = start.row;
    j = start.col;
    // Scanning diagonally left-upwards
    while (i < 8 && j >= 0){
        // If non-empty square encountered, we need to stop traversing
        if (board[i][j] != nullptr){ 
            // If opponent's piece encountered, add that square to valid moves,
            // as taking opposition piece is valid move
            if (board[i][j].color != color){
                dests.push_back( square(i, j) );
            }
            break;
        }

        dests.push_back( square(i, j) );
        i++;
        j--;
    }

    i = start.row;
    j = start.col;
    // Scanning diagonally left-downwards
    while (i >= 0 && j >= 0){
        // If non-empty square encountered, we need to stop traversing
        if (board[i][j] != nullptr){ 
            // If opponent's piece encountered, add that square to valid moves,
            // as taking opposition piece is valid move
            if (board[i][j].color != color){
                dests.push_back( square(i, j) );
            }
            break;
        }

        dests.push_back( square(i, j) );
        i--;
        j--;
    }
    return dests;
}


std::vector<Square> Queen::legalStraightDests(const Square& start, const std::array<std::array<int, 8>, 8>& board){

    std::vector<Square> dests;

    // Scanning possible vertical moves (i.e. where start column = dest column)
    // Start from first row on the starting square's column, scan to last row on the same column.
    int i = 0;
    while (i < 8){

        // If encounters non-empty square before reaching rook's position
        if (board[i][start.col] != nullptr && i < start.row){
            dests.clear(); // Clear dests - Those squares are not valid dests if there is a piece between them and the start square

            // If encountered piece is enemy, can capture that piece
            // So add its square to legal dests
            if (board[i][start.col]->getColor() != color){
                    dests.push_back( square(i, start.col) );
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
                    dests.push_back( square(i, start.col) );
            }
            break; // Stop scanning - found all possible destinations on this column
        }
        
        // Default case - If i is on an empty square
        else {
            dests.push_back( square(i, start.col) );
        }
        
        i++;
    }

    // Scanning possible horizontal moves (i.e. where start row = dest row)
    // Use the same principles as above, except instead of vertical, scan horizontally.
    // Start from first column on the starting square's row, scan to last column on the same row.
    int j = 0;
    while (j < 8){

        // If encounters non-empty square before reaching rook's position
        if (board[start.row][j] != nullptr && j < start.col){
            dests.clear(); // Clear dests - Those squares are not valid dests if there is a piece between them and the start square

            // If encountered piece is enemy, can capture that piece
            // So add its square to legal dests
            if (board[start.row][j]->getColor() != color){
                    dests.push_back( square(start.row, j) );
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
                    dests.push_back( square(start.row, j) );
            }
            break; // Stop scanning - found all possible destinations on this row
        }
        
        // Default case - If j is on an empty square
        else {
            dests.push_back( square(start.row, j) );
        }
        
        j++;
    }

    return dests;
}