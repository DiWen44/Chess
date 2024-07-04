#include <string>

#include "move.hpp"


Square square(int row, int col){
    Square res;
    res.row = row;
    res.col = col;
    return res;
}


Square squareFromStr(const std::string& str){
    int row = str[1] - '1'; // Difference in ASCII value between 2nd char and '1' gives row no.
    int col = str[0] - 'a'; // Difference in ASCII value between 1st char and 'a' gives column no.
    Square res = square(row, col);
    return res;
}


bool isValidSquareStr(const std::string& str){
    if (str.length() != 2){ return false; }

    // Check if column (letter) component is between 'a' and 'h' inclusive
    // And if row (number) component is between 1 and 8 inclusive
    // by comparing ASCII values
    if (str[0] < 'a' || str[0] > 'h'){ return false; }
    if (str[1] < '1' || str[1] > '8'){ return false; }

    return true;
}


std::array<int, 2> displacement(const Square& start, const Square& dest){
    int rowDisp = dest.row - start.row;
    int colDisp = dest.col - start.col;
    return std::array<int, 2>{ {rowDisp, colDisp} };
}