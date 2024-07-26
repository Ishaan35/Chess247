#include "king.h"

King::King(PieceType t, int pId) : Piece{t, pId}
{
    // initialize movement here
}

std::unique_ptr<Piece> King::clone()
{
    return std::make_unique<King>(*this);
}