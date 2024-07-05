#include <array>
#include <vector>

#include "piece.hpp"
#include "square.hpp"


class Rook : public Piece {

    public:

        Rook(PieceColor color);

        char toChar() override;

        bool isLegalMove(const Square& start, const Square& dest, const std::array<std::array<int, 8>, 8>& board) override;

        std::vector<Square> legalDests(const Square& start, const std::array<std::array<int, 8>, 8>& board) override;
    
    private:

        // Given a move, determines if the path along that move is clear i.e. there are no pieces in the way.
        // Since this is the rook class, THIS IMPLEMENTATION ASSUMES THAT THE MOVE PROVIDED IS EITHER COMPLETELY HORIZONTAL OR VERTICAL.
        // Used by isLegalMove(), which will determine if the move meets the above condition in advance of calling this.
        bool isPathClear(const Square& start, const Square& dest, const std::array<std::array<int, 8>, 8>& board);
};
