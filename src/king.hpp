#include <array>
#include <vector>

#include "piece.hpp"
#include "square.hpp"


class King : public Piece {

    public:

        King(PieceColor color);
        
        King();

        char toChar() override;

        bool isLegalMove(const Square& start, const Square& dest, const std::array<std::array<Piece*, 8>, 8>& board) override;

        std::vector<Square> legalDests(const Square& start, const std::array<std::array<Piece*, 8>, 8>& board) override;

};
