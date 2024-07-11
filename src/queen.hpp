#include <array>
#include <vector>

#include "piece.hpp"
#include "square.hpp"

#pragma once


class Queen : public Piece {

    public:

        Queen(PieceColor color);

        Queen();

        char toChar() override;

        bool isLegalMove(const Square& start, const Square& dest, const std::array<std::array<Piece*, 8>, 8>& board) override;

        std::vector<Square> legalDests(const Square& start, const std::array<std::array<Piece*, 8>, 8>& board) override;
    
    private:

        // Given a move, determines if the path along that move is clear i.e. there are no pieces in the way.
        // Since this is the queen class, THIS IMPLEMENTATION ASSUMES THAT THE MOVE PROVIDED IS PURELY DIAGONAL, PURELY HORIZONTAL OR PURELY VERTICAL.
        // Used by isLegalMove(), which will determine if the move is diagonal in advance of calling this.
        bool isPathClear(const Square& start, const Square& dest, const std::array<std::array<Piece*, 8>, 8>& board);
};