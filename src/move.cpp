#include <string>

#include "move.hpp"


Move move(int startRow, int startCol, int destRow, int destCol){
    Move res;
    res.startRow = startRow;
    res.startCol = startCol;
    res.destRow = destRow;
    res.destCol = destCol;
    return res;
}


Move moveFromSquareStrs(const std::string& startStr, const std::string& destStr){
    int startRow = startStr[1] - '1'; // Difference in ASCII value between 2nd char and '1' gives row no.
    int startCol = startStr[0] - 'a'; // Difference in ASCII value between 1st char and 'a' gives column no.
    int destRow = destStr[1] - '1'; 
    int destCol = destStr[0] - 'a';
    Move res = move(startRow, startCol, destRow, destCol);
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


int* displacement(const Move& mv){
    int rowDisp = mv.destRow - mv.startRow;
    int colDisp = mv.destCol - mv.startCol;
    return new int[2]{rowDisp, colDisp};
}