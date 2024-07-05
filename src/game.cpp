#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <cmath>

#include "game.hpp"
#include "piece.hpp"
#include "square.hpp"


Game::Game(){

    Piece whitePawn;
    whitePawn.type = PieceType::PAWN;
    whitePawn.color = PieceColor::WHITE;
    Piece whiteRook;
    whiteRook.type = PieceType::ROOK;
    whiteRook.color = PieceColor::WHITE;
    Piece whiteKnight;
    whiteKnight.type = PieceType::KNIGHT;
    whiteKnight.color = PieceColor::WHITE;
    Piece whiteBish;
    whiteBish.type = PieceType::BISHOP;
    whiteBish.color = PieceColor::WHITE;
    Piece whiteQueen;
    whiteQueen.type = PieceType::QUEEN;
    whiteQueen.color = PieceColor::WHITE;
    Piece whiteKing;
    whiteKing.type = PieceType::KING;
    whiteKing.color = PieceColor::WHITE;

    Piece blackPawn;
    blackPawn.type = PieceType::PAWN;
    blackPawn.color = PieceColor::BLACK;
    Piece blackRook;
    blackRook.type = PieceType::ROOK;
    blackRook.color = PieceColor::BLACK;
    Piece blackKnight;
    blackKnight.type = PieceType::KNIGHT;
    blackKnight.color = PieceColor::BLACK;
    Piece blackBish;
    blackBish.type = PieceType::BISHOP;
    blackBish.color = PieceColor::BLACK;
    Piece blackQueen;
    blackQueen.type = PieceType::QUEEN;
    blackQueen.color = PieceColor::BLACK;
    Piece blackKing;
    blackKing.type = PieceType::KING;
    blackKing.color = PieceColor::BLACK;

    this->board = {{
        {whiteRook, whiteKnight, whiteBish, whiteQueen, whiteKing, whiteBish, whiteKnight, whiteRook},
        {whitePawn, whitePawn, whitePawn, whitePawn, whitePawn, whitePawn, whitePawn, whitePawn},
        {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
        {blackPawn, blackPawn, blackPawn, blackPawn, blackPawn, blackPawn, blackPawn, blackPawn},
        {blackRook, blackKnight, blackBish, blackQueen, blackKing, blackBish, blackKnight, blackRook}
    }};

    this->turn = PieceColor::WHITE;
}


std::array<std::array<Piece*, 8>, 8> Game::getBoard(){
    return board;
}


void Game::printBoard(){
    std::cout << std::endl;

    // Print file letters above board 
    std::cout << "\033[38;5;2m";  // Switch text color to green to print file letters
    std::cout << "  a    b    c    d    e    f    g    h  " << std::endl;  // Print files
    std::cout << "\033[0m"; // Revert to prior text coloring

    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            char pieceChar = pieceToChar(board[i][j]);
            std::cout << "  " << pieceChar << "  ";
            toggleBackgroundColor();
        }

        // Print rank number after rank
        std::cout << "\033[0m"; // Switch background back to black
        std::cout << "\033[38;5;1m";  // Switch text color to red to print rank no.
        std::cout << "  " << i+1; // Print rank
        std::cout << "\033[0m"; // Revert to prior coloring

        std::cout << std::endl;
        toggleBackgroundColor();
        
    }
    std::cout << "(m) move  (r) resign  (od) offer draw" << std::endl;  // List valid user inputs under board
}


void Game::toggleTurn(){
    turn = (turn == PieceColor::WHITE) ? PieceColor::BLACK : PieceColor::WHITE;
}


PieceColor Game::getTurn(){
    return turn;
}


std::string Game::getTurnStr(){
    return (turn == PieceColor::WHITE) ? "WHITE" : "BLACK";
}

void Game::movePiece(const Square& start, const Square& dest){
    Piece pieceToMove = board[start.row][start.col];
    Piece pieceAtDest = board[dest.row][dest.col];

    board[dest.row][dest.col] = pieceToMove;
    board[start.row][start.col] = nonePiece(); // Vacate start square by setting it to the "none" piece

    // Check for a pawn promotion
    // Pawns can be promoted to a queen, rook, bishop or knight.
    // Provided they have reached the end of the board
    // i.e. for a white pawn, has reached row 7; for a black pawn, has reached row 0.
    if (pieceToMove.type == PieceType::PAWN){
        if ( (dest.row == 7 && pieceToMove.color == PieceColor::WHITE) || (dest.row == 0 && pieceToMove.color == PieceColor::BLACK) ) {
            std::string choice;
            do {
                std::cout << "PROMOTE TO: QUEEN (q)  ROOK (r)  BISHOP (b)  KNIGHT (n)" << std::endl;
                std::cout << "> ";
                std::cin >> choice;
                std::cout << std::endl;
            } while (choice != "q" && choice != "r" && choice != "b" && choice != "n");

            // Set move destination to selected piece
            Piece newPiece;
            newPiece.color = turn;
            if (choice == "q"){ newPiece.type = PieceType::QUEEN; }
            else if (choice == "r"){ newPiece.type = PieceType::ROOK; }
            else if (choice == "b"){ newPiece.type = PieceType::BISHOP; }
            else if (choice == "n"){ newPiece.type = PieceType::KNIGHT; }
            board[dest.row][dest.col] = newPiece;
        }
    }
}


bool Game::isLegalMove(const Square& start, const Square& dest){

    Piece pieceToMove = board[start.row][start.col];
    Piece pieceAtDest = board[dest.row][dest.col];
    std::array<int, 2> disp = displacement(start, dest);

    // Return false here if:
    // - Empty square was selected as start
    // - Attempting to move opponent's piece
    // - Destination square has one of the mover's pieces on it already
    if (isNone(pieceToMove) || pieceToMove.color != turn || pieceAtDest.color == pieceToMove.color){ 
        return false;
    }

    switch (pieceToMove.type){

        case PieceType::PAWN:
            // PAWN MOVE CONDITIONS:
            // - Can move 1 row forward on same col if no piece at dest square
            // - Can move diagonally by 1 and take piece if opposition piece is on that square
            // - Can move 2 rows forward on same col if at starting position (row 1 for white, row 6 for black)
            //   and if no piece is in it's path to or at the destination square.
            // - Can take en passant by moving 1 square diagonally behind a pawn that has advanced by 2 squares, which captures that pawn.
            //   Only possible if the opposing pawn advanced 2 squares on the previous turn, and if the destination square is vacant.
            //
            // Note that for black pawns, a move "forward" will have negative vertical displacement,
            // as black pieces start on the last 2 rows and advance towards the first 2

            // White pawns
            if (disp[0] > 0 && pieceToMove.color == PieceColor::WHITE){
                // Moving 1 square forward
                if  (disp[0] == 1 && disp[1] == 0 && isNone(pieceAtDest)) {
                    return true;
                }
                // Attacking diagonally 1 space
                else if ( (disp[0] == 1 && abs(disp[1]) == 1) && (pieceAtDest.color == PieceColor::BLACK) ) {
                    return true;
                }
                // Moving 2 squares forward
                if ( (disp[0] == 2 && disp[1] == 0) && (start.row == 1) && (isNone(board[dest.row-1][dest.col])) && isNone(pieceAtDest) ){
                    return true;
                }
            }

            // Black pawns
            else if (disp[0] < 0 && pieceToMove.color == PieceColor::BLACK){
                // Moving 1 square forward
                if  ( (disp[0] == -1 && disp[1]) == 0 && isNone(pieceAtDest) ) {
                    return true;
                }
                // Attacking diagonally forward
                else if ( (disp[0] == -1 && abs(disp[1]) == 1) && (pieceAtDest.color == PieceColor::WHITE) ) {
                    return true;
                }
                // Moving 2 squares forward
                if ( (disp[0] == -2 && disp[1] == 0) && (start.row == 1) && (isNone(board[dest.row+1][dest.col])) && isNone(pieceAtDest) ){
                    return true;
                }
            }
            break;
        
        case PieceType::KNIGHT:
            // KNIGHT MOVE CONDITIONS: Can move either 2 rows and 1 column, or by 1 row and 2 columns, in any direction
            // Unlike other pieces, the knight can do this even if another piece is in it's path (jumping).
            return ( (abs(disp[0]) == 1 && abs(disp[1]) == 2) || (abs(disp[0]) == 2 && abs(disp[1])  == 1) );
            break;

        case PieceType::BISHOP:
            // BISHOP MOVE CONDITIONS: Can move by the same number of rows as columns e.g. (1,1), (3,3), if it's path is not blocked by another piece.
            if (abs(disp[0]) == abs(disp[1])){
                return isPathClear(start, dest);
            }
            break;
        
        case PieceType::ROOK:
            // ROOK MOVE CONDITIONS: Can move by any number of columns on the same row (horizontally), 
            // or by any number of rows on the same column (vertically), 
            // provided it's path isn't blocked by another piece.
            if (disp[0] == 0 || disp[1] == 0){
                return isPathClear(start, dest);
            }
            break;

        case PieceType::QUEEN:
            // QUEEN MOVE CONDITIONS: 
            // - Can move by any number of columns on the same row (horizontally).
            // - Can move by any number of rows on the same column (vertically).
            // - Can move by the same number of rows as columns (diagonally).
            // Provided it's path isn't blocked by another piece.
            if (disp[0] == 0 || disp[1] == 0 || abs(disp[0]) == abs(disp[1])){
                return isPathClear(start, dest);
            }
            break;

        case PieceType::KING:
            // KING MOVE CONDITIONS:
            // - Can move by 1 row (horizontally 1 space) in any direction
            // - Can move by 1 column (vertically 1 space) in any direction
            // - Can move by 1 row and 1 column (diagonally 1 space) in any direction.
            // - Can castle if neither king nor rook has moved, and if no pieces are between the rook and king
            return ( (abs(disp[0]) == 1 && disp[1] == 0) || (disp[0] == 0 && abs(disp[1]) == 1) || (abs(disp[0]) == 1 && abs(disp[1]) == 1) );
            break;
        
        return false; // Return false if method has not returned yet
    }
}


std::vector<std::array<int, 2>> Game::legalMoves(const Square& sq){
    Piece piece = board[sq.row][sq.col];
    std::vector<std::vector<int>> moves;

    switch (piece.type){
        case PieceType::PAWN:
            // White pawns
            if(piece.color == PieceColor::WHITE){

                // Moving 1 square forward
                if (isNone(board[sq.row+1][sq.col]) ){
                    moves.push_back( std::vector<int>{row+1, col} );

                    // Moving 2 squares forward from starting square
                    if (isNone(board[sq.row+2][sq.col]) && row==1){
                        moves.push_back( std::vector<int>{row+2, col} );
                    }                
                } 
                
                // Attacking diagonally by 1 square.
                Piece diagUpRight =  board[sq.row+1][sq.col+1]; // Piece diagonally right and upwards 1 square
                Piece diagUpLeft =  board[sq.row+1][sq.col-1]; // Piece diagonally left and upwards 1 square
                if ( diagUpRight.color == PieceColor::BLACK) { moves.push_back( std::vector<int>{sq.row+1, sq.col+1} );}
                if ( diagUpLeft.color == PieceColor::BLACK) { moves.push_back( std::vector<int>{sq.row+1, sq.col-1} ); }
            }

            // Black pawns, for which a move "forward" involves moving to a "lower" row. 
            // e.g. black pawn moving from e7 (row 6) to e5 (row 4) is a "forward" move.
            else if(piece.color == PieceColor::BLACK){

                // Moving 1 square forward.
                if (isNone(board[sq.row-1][sq.col]) ){
                    moves.push_back( std::vector<int>{row-1, col} );

                    // Moving 2 squares forward from starting square.
                    if (isNone(board[sq.row-2][sq.col]) && row==1){
                        moves.push_back( std::vector<int>{row-2, col} );
                    }                
                } 
                
                // Attacking diagonally by 1 square.
                Piece diagUpRight =  board[sq.row-1][sq.col+1]; // Piece diagonally right and upwards 1 square.
                Piece diagUpLeft =  board[sq.row-1][sq.col-1]; // Piece diagonally left and upwards 1 square.
                if ( diagUpRight.color == PieceColor::BLACK) { moves.push_back( std::vector<int>{sq.row-1, sq.col+1} );}
                if ( diagUpLeft.color == PieceColor::BLACK) { moves.push_back( std::vector<int>{sq.row-1, sq.col-1} ); }
            }

        case PieceType::KNIGHT:     
            std::array<std::array<int, 2>, 8> knightMoves = { { {2,1}, {2,-1}, {1,2}, {1, -2}, {-1,2}, {-1,-2}, {-2,1}, {-2,-1} } };
            for (int i = 0; i < 8; i++){
                Piece &pieceAtDest = board[sq.row+knightMoves[i][0]][sq.col+knightMoves[i][1]];
                // If destination square is either empty or has opposition piece
                if (pieceAtDest.color != turn){ 
                    moves.push_back( std::vector<int>{sq.row+knightMoves[i][0], sq.col+knightMoves[i][1]}); 
                }
            }

        case PieceType::BISHOP:
            
            int i = row;
            int j = col;
            while (i < 8 && j < 8){

                // If non-empty square encountered, we need to stop traversing
                if (!isNone(board[i][j])){ 
                    // If opponent's piece encountered, add that square to valid moves,
                    // as taking opposition piece is valid move
                    if (board[i][j].color != turn){
                        moves.push_back( std::vector<int>{i, j} );
                    }
                    break;
                }

                moves.push_back( std::vector<int>{i, j} );
                i++;
                j++;
            }

            i = row;
            j = col;

            while (i >= 0 && j < 8){
                // If non-empty square encountered, we need to stop traversing
                if (!isNone(board[i][j])){ 
                    // If opponent's piece encountered, add that square to valid moves,
                    // as taking opposition piece is valid move
                    if (board[i][j].color != turn){
                        moves.push_back( std::vector<int>{i, j} );
                    }
                    break;
                }

                moves.push_back( std::vector<int>{i, j} );
                i++;
                j++;
            }

            while (i < 8 && j >= 0){

            }
            while (i >= 0 && j >= 0){

            }
    




        case PieceType::ROOK :
        case PieceType::QUEEN :
        case PieceType::KING :         
    }

    return moves;
}


bool Game::isCheck(){
    // Find the player's king on the board
    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){

            if (board[i][j].type == PieceType::KING && board[i][j].color == turn){
                Square sq = square(i,j);
                return isAttacked(sq); // If the king is on an attacked square, then is in check
            }
        }
    }
}


bool Game::isCheckMate(){
    // Player must be in check to be checkmated
    if (!isCheck()){
        return false;
    }

    // Player is in checkmate if they are currently in check, and there is no legal move that allows 
    // them to escape it.


    
}


void Game::resign(){
    std::cout << getTurnStr() << " RESIGNS" << std::endl;
    std::cout << "-------------------------------------------------------------------------------------------------" << std::endl;
}


bool Game::offerDraw(){
    std::string playerOffering = getTurnStr();
    std::string playerRecieving = (turn == PieceColor::WHITE) ? "BLACK" : "WHITE";

    std::cout << playerOffering << " OFFERS A DRAW" << std::endl;
    std::cout << playerRecieving<< ", TYPE (y) TO ACCEPT AND (n) TO DECLINE: "; 
    std::string resp;
    std::cin >> resp;

    while(resp != "y" && resp != "n"){
        std::cout << "INVALID INPUT" << std::endl;
        std::cout << playerRecieving << ", TYPE (y) TO ACCEPT AND (n) TO DECLINE: "; 
        std::cin >> resp;
    }

    if (resp == "y"){
        std::cout << "DRAW" << std::endl;
        std::cout << "-------------------------------------------------------------------------------------------------" << std::endl;
        return true;
    } else {
        std::cout << "DRAW DECLINED, GAME CONTINUES." << std::endl;
        return false;
    }
}


bool Game::isPathClear(const Square& start, const Square& dest){

    std::array<int, 2> disp = displacement(start, dest);

    // Diagonal move
    if (abs(disp[0]) == abs(disp[1])){
        bool incI = start.row < dest.row;
        bool incJ = start.col < dest.col;
        int i = (incI) ? start.row+1 : start.row-1;
        int j = (incJ) ? start.col+1 : start.col-1;

        while(i != dest.row && j != dest.col){
            if ( !isNone(board[i][j]) ){ // If piece encountered
                return false;
            }

            // Traverse by 1 square diagonally to get closer to dest
            if (incI) { i++; } else { i--; }; 
            if (incJ) { j++; } else { j--; };
        }
        return true; // Return true if no pieces encountered in the way
    }

    // Horizontal move
    else if (disp[0] == 0){
        bool incJ = start.col < dest.col;
        int j = (incJ) ? start.col+1 : start.col-1;

        while(j != dest.col){
            if ( !isNone(board[start.col][j]) ){  // If piece encountered
                return false; 
            }
            if (incJ) { j++; } else { j--; }; // Bring j 1 square closer to dest
        }
        return true; // Return true if no pieces encountered in the way
    } 

    // Vertical move
    else if (disp[1] == 0){
        bool incI = start.row < dest.row;
        int i = (incI) ? start.row+1 : start.row-1;

        while(i != dest.row){
            if ( !isNone(board[i][start.col]) ){  // If piece encountered
                return false; 
            }
            if (incI) { i++; } else { i--; }; // Bring i 1 square closer to dest
        }
        return true; // Return true if no pieces encountered in the way
    }
}


bool Game::isAttacked(const Square& sq){
    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            if ( !isNone(board[i][j]) && board[i][j].color != turn ){
                Square sqAtIJ = square(i,j);
                // If move from sqAtIJ to sq is legal, sq is attacked
                if (isLegalMove(sqAtIJ, sq)){
                    return true;
                } 
            }
        }
    }
    return false;
}


void Game::toggleBackgroundColor(){
    static bool isBlack = true; // Tracks whether square background painter is currently black 
    if (isBlack){
        std::cout << "\033[48;5;231m"; // Turn painter white
    } else { 
        std::cout << "\033[0m"; // Turn painter back to black
    }
    isBlack = !isBlack;
}