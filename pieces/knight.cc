#include "knight.h"

Knight::Knight(PieceType t, int pId) : Piece{t, pId}
{
    // initialize movement here
}

std::unique_ptr<Piece> Knight::clone()
{
    return std::make_unique<Knight>(*this);
}