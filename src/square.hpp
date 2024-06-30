#include <string>

#pragma once


// Represents a square on the board.
// Like the board matrix itself, this is 0-base-indexed i.e. "a1" is [0,0], "a2" is [1,0], "b1" is [0,1].
// Note that "a" is considered the first file, and "1" is considered the first rank. 
struct Square{
    int row;
    int col;
};


// Creates an instance of square struct.
Square square(int row, int col);


// Takes a square string (e.g. "a4", "g7", "c6"), returns a corresponding instance of square struct.
Square strToSquare(const std::string& str);


// Check if a square string (e.g. "a4", "g7", "c6") is valid
bool isValidSquareStr(const std::string& squareStr);