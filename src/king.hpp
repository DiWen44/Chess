#include <array>
#include <vector>

#include "piece.hpp"
#include "square.hpp"


#pragma once


class King : public Piece {

    public:

        King(PieceColor color);
        
        King();

        char toChar() override;

        bool isLegalMove(const Square& start, const Square& dest, const std::array<std::array<Piece*, 8>, 8>& board) override;

        std::vector<Square> legalDests(const Square& start, const std::array<std::array<Piece*, 8>, 8>& board) override;

        // Determines if the king is able to castle short (kingside) 
        // (the game board is passed as a param)
        bool canCastleShort(const std::array<std::array<Piece*, 8>, 8>& board);

        // Determines if the king is able to castle long (queenside) 
        // (the game board is passed as a param)
        bool canCastleLong(const std::array<std::array<Piece*, 8>, 8>& board);
};
