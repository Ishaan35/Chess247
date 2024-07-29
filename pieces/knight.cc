#include "knight.h"
#include "../movement/lshapedMovement.h"
#include "../movement/emptyMovement.h"

Knight::Knight(PieceType t, Color color) : Piece{t, color, new LShapedMovement{new EmptyMovement{}, color}}
{
    // initialize movement here
}

std::unique_ptr<Piece> Knight::clone()
{
    return std::make_unique<Knight>(*this);
}