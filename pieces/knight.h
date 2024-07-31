#ifndef KNIGHT_H
#define KNIGHT_H
#include "piece.h"

class Knight : public Piece
{
public:
    Knight(PieceType t, Color color);
    std::unique_ptr<Piece> clone() override;
};

#endif
