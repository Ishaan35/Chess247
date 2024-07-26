#ifndef ROOK_H
#define ROOK_H
#include "piece.h"

class Rook : public Piece
{
public:
    Rook(PieceType t, int pId);
    std::unique_ptr<Piece> clone() override;
};

#endif