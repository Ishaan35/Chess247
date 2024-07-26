#ifndef KNIGHT_H
#define KNIGHT_H
#include "piece.h"

class Knight : public Piece
{
public:
    Knight(PieceType t, int pId);
    std::unique_ptr<Piece> clone() override;
};

#endif