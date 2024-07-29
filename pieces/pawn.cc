#include "pawn.h"
#include "../movement/pawnMovement.h"
#include "../movement/emptyMovement.h"

Pawn::Pawn(PieceType t, Color color) : Piece{t, color, new PawnMovement{new EmptyMovement{}, color}}
{
    // initialize movement here
}

std::unique_ptr<Piece> Pawn::clone()
{
    return std::make_unique<Pawn>(*this);
}