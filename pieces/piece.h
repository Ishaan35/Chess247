#ifndef PIECE_H
#define PIECE_H

#include <memory>
#include "pieceType.h"
#include "../colorEnum.h"
#include <vector>
#include "../movement/movement.h"
// so the d
class Piece
{
    PieceType type;
    Color color;
    bool has_moved;

protected:
    shared_ptr<Movement> m;

public:
    Piece(PieceType t, Color color, Movement *m) : type{t}, color{color}, m{m} {}
    virtual std::unique_ptr<Piece> clone() = 0;
    virtual ~Piece() = default;
    vector<PossibleMove> getPossibleMoves(pair<int, int> position, const std::vector<std::vector<std::unique_ptr<Piece>>> &board);
    PieceType getType();
    Color getColor();
    bool hasMoved() const;
    void setHasMoved(bool val);
};
#endif