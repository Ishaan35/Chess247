#include "king.h"
#include "../movement/singleSquareMovement.h"
#include "../movement/emptyMovement.h"

King::King(PieceType t, Color color) : Piece{t, color, new SingleSquareMovement{new EmptyMovement{}, color}}
{
    // initialize movement here
}

std::unique_ptr<Piece> King::clone()
{
    return std::make_unique<King>(*this);
}