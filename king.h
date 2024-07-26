#ifndef KING_H
#define KING_H

#include "piece.h"

class King: public Piece{
public:
    King(PieceType t, int pId);
    std::unique_ptr<Piece> clone() override;
};

#endif