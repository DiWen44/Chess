#include <string>

#include "square.hpp"


Square square(int row, int col){
    Square res;
    res.row = row;
    res.col = col;
    return res;
}


Square strToSquare(const std::string& str){
    int x = str[1] - '1'; // Difference in ASCII value between 2nd char and '1' gives row no.s
    int y = str[0] - 'a'; // Difference in ASCII value between 1st char and 'a' gives column no.
    Square res = square(x, y);
    return res;
}


bool isValidSquareStr(const std::string& squareStr){
    if (squareStr.length() != 2){ return false; }

    // Check if column (letter) component is between 'a' and 'h' inclusive
    // And if row (number) component is between 1 and 8 inclusive
    // by comparing ASCII values
    if (squareStr[0] < 'a' || squareStr[0] > 'h'){ return false; }
    if (squareStr[1] < '1' || squareStr[1] > '8'){ return false; }

    return true;
}