#include "queen.h"

Queen::Queen(PieceType t, int pId): Piece{t, pId} {
    //initialize movement here
}

std::unique_ptr<Piece> Queen::clone()
{
    return std::make_unique<Queen>(*this);
}