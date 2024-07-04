#include <string>
#include <array>

#pragma once


// A type that represents the square at board[row][col].
// Like the board matrix itself, the row and column numbers are 0-base-indexed.
// e.g. 
// "a1" -> row 0 col 0, 
// "b1" -> row 0 col 1
// "a2" -> row 1 col 0
// Note that "a" is considered the first file (col 0), and "1" is considered the first rank (row 0). 
struct Square{
    int row;
    int col;
};


// Creates an instance of square struct.
Square square(int row, int col);


// Takes a square string (e.g. "a4", "g7", "c6"), and
// returns a corresponding instance of the square struct.
Square squareFromStr(const std::string& str);


// Check if a square string (e.g. "a4", "g7", "c6") is valid. Valid square strings
// have 2 chars, a letter from 'a' through 'h' followed by a number from 1 through 8
bool isValidSquareStr(const std::string& str);


// Gets the horizontal and vertical components of the displacement of a given move struct, 
// This is the number of rows and the number of columns that an arbitrary piece needs to be moved by in order to complete the move.
// e.g. the displacement from "a3" to "b5" would be: +2 rows, +1 column.  
//
// This is returned in the form of a 2-element int array, 
// of which the first element is the vertical displacement (i.e. difference in rows) 
// and the second is the horizontal displacement (i.e. difference in columns).
std::array<int, 2> displacement(const Square& start, const Square& dest);