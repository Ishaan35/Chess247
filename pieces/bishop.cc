#include "bishop.h"

Bishop::Bishop(PieceType t, int pId) : Piece{t, pId}
{
    // initialize movement here
}

std::unique_ptr<Piece> Bishop::clone()
{
    return std::make_unique<Bishop>(*this);
}