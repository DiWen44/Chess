#include <array>
#include <vector>

#include "piece.hpp"
#include "square.hpp"


class Pawn : public Piece {

    public:

        Pawn(PieceColor color);

        Pawn();

        char toChar() override;

        bool isLegalMove(const Square& start, const Square& dest, const std::array<std::array<Piece*, 8>, 8>& board) override;

        std::vector<Square> legalDests(const Square& start, const std::array<std::array<Piece*, 8>, 8>& board) override;

        // Returns canBeCapturedEnPassant
        bool canBeCapturedEP();

        // If canBeCapturedEnPassant is true, sets it to false, and vice versa
        bool toggleEP();
    
    private:

        // If the pawn can be captured en passant, is true.
        // Otherwise, false.
        bool canBeCapturedEnPassant; 
};
