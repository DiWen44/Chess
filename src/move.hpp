#include <string>

#pragma once


// Represents a move from the square at board[startRow][startCol], to the square at board[destRow][destCol].
// Like the board matrix itself, the row and column numbers are 0-base-indexed.
// e.g. 
// "a1" -> row 0 col 0, 
// "b1" -> row 0 col 1
// "a2" -> row 1 col 0
// Note that "a" is considered the first file (col 0), and "1" is considered the first rank (row 0). 
struct Move{
    int startRow;
    int startCol;
    int destRow;
    int destCol;
};


// Creates an instance of move struct.
Move move(int startRow, int startCol, int destRow, int destCol);


// Takes 2 square strings (e.g. "a4", "g7", "c6"),
// One representing the start square of the move and the other the destination square
// returns a corresponding instance of the move struct.
Move moveFromSquareStrs(const std::string& startStr, const std::string& destStr);


// Check if a square string (e.g. "a4", "g7", "c6") is valid. Valid square strings
// have 2 chars, a letter from 'a' through 'h' followed by a number from 1 through 8
bool isValidSquareStr(const std::string& squareStr);


// Gets the horizontal and vertical components of the displacement of a given move struct, 
// This is the number of rows and the number of columns that an arbitrary piece needs to be moved by in order to complete the move.
// e.g. the displacement from "a3" to "b5" would be: +2 rows, +1 column.  
//
// This is returned in the form of a 2-element int array, 
// of which the first element is the vertical displacement (i.e. difference in rows) 
// and the second is the horizontal displacement (i.e. difference in columns).
int* displacement(const Move& mv);