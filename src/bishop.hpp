#include <array>
#include <vector>

#include "piece.hpp"
#include "square.hpp"


class Bishop : public Piece {

    public:

        Bishop(PieceColor color);

        Bishop();

        char toChar() override;

        bool isLegalMove(const Square& start, const Square& dest, const std::array<std::array<Piece*, 8>, 8>& board) override;

        std::vector<Square> legalDests(const Square& start, const std::array<std::array<Piece*, 8>, 8>& board) override;
    
    private:

        // Given a move, determines if the path along that move is clear i.e. there are no pieces in the way.
        // Since this is the bishop class, THIS IMPLEMENTATION ASSUMES THAT THE MOVE PROVIDED IS DIAGONAL.
        // Used by isLegalMove(), which will determine if the move is diagonal in advance of calling this.
        bool isPathClear(const Square& start, const Square& dest, const std::array<std::array<Piece*, 8>, 8>& board);
};
