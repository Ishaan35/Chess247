#ifndef QUEEN_H
#define QUEEN_H
#include "piece.h"

class Queen : public Piece
{
public:
    Queen(PieceType t, int pId);
    std::unique_ptr<Piece> clone() override;
};

#endif