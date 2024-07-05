#include <array>
#include <vector>

#include "piece.hpp"
#include "square.hpp"


class Knight : public Piece {

    public:

        Knight(PieceColor color);

        char toChar() override;

        bool isLegalMove(const Square& start, const Square& dest, const std::array<std::array<int, 8>, 8>& board) override;

        std::vector<Square> legalDests(const Square& start, const std::array<std::array<int, 8>, 8>& board) override;

};
