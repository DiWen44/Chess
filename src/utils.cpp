#include <vector>
#include <string>
#include <iostream>

#include "utils.hpp"


/*
 * Determines if a user-inputted square string (given as part of a move command) is valid, as in:
 *      - has exactly 2 chars
 *      - 1st char is alphabetically between a and h inclusive
 *      - 2nd char is numerically between 1 and 8 inclusive

*/
bool isValidSquareStr(const std::string& squareStr){
    if (squareStr.length() != 2){ return false; }

    // Check if column (letter) component is between 'a' and 'h' inclusive
    // And if row (number) component is between 1 and 8 inclusive
    // by comparing ASCII values
    if (squareStr[0] < 'a' || squareStr[0] > 'h'){ return false; }
    if (squareStr[1] < '1' || squareStr[1] > '8'){ return false; }

    return true;
}


int* squareStrToSquareArr(const std::string& squareStr){
    // Subtract '0' ASCII value to convert char to single-digit int
    // Subtract 1 since indexing should being at 0
    int x = (squareStr[1] - '0') - 1; 

    int y = squareStr[0] - 'a'; // Difference in ASCII value between 

    int* res = new int[2] {x, y};
    return res;
}