#ifndef PAWN_H
#define PAWN_H
#include "piece.h"

class Pawn: public Piece{
public:
    Pawn(PieceType t, Color color);
    std::unique_ptr<Piece> clone() override;
};

#endif
