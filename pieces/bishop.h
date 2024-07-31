#ifndef BISHOP_H
#define BISHOP_H
#include "piece.h"

class Bishop : public Piece
{
public:
    Bishop(PieceType t, Color color);
    std::unique_ptr<Piece> clone() override;
};

#endif
