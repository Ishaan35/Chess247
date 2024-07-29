#ifndef PIECE_H
#define PIECE_H

#include "../movement/movement.h"
#include <memory>
#include "pieceType.h"
#include "../colorEnum.h"

// so the d
class Piece
{
    PieceType type;
    Color color;
    bool hasMoved;

protected:
    shared_ptr<Movement> m;

public:
    Piece(PieceType t, Color color, Movement *m) : type{t}, color{color}, m{m} {}
    virtual std::unique_ptr<Piece> clone() = 0;
    virtual ~Piece() = default;
    vector<PossibleMove> getPossibleMoves(pair<int, int> position, int rows, int cols);
    PieceType getType();
    Color getColor();
    bool hasMoved() const;
};
#endif