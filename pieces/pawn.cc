#include "pawn.h"

Pawn::Pawn(PieceType t, int pId) : Piece{t, pId}
{
    // initialize movement here
}

std::unique_ptr<Piece> Pawn::clone()
{
    return std::make_unique<Pawn>(*this);
}