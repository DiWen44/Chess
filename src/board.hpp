#include <vector>

#pragma once


enum PieceType {
    NONE,
    PAWN,
    KNIGHT,
    BISHOP,
    ROOK,
    QUEEN,
    KING
};


enum Color {NONE, WHITE, BLACK};


typedef struct {
    PieceType type;
    Color color;
} Piece;

class Board{

public:
    Board();
    void printBoard();
    bool isValidMove(std::string start, std::string dest);
    void movePiece(std::string start, std::string dest);
    bool isCheckMate();
    bool isCheck();

private:
    std::vector<std::vector<Piece>> boardMat;
};
