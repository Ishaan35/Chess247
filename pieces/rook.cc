#include "rook.h"
#include "../movement/horizontalMovement.h"
#include "../movement/verticalMovement.h"
#include "../movement/emptyMovement.h"

Rook::Rook(PieceType t, Color color) : Piece{t, color, new HorizontalMovement{new VerticalMovement{new EmptyMovement{}, color}, color}}
{
    // initialize movement here
}

std::unique_ptr<Piece> Rook::clone(){
    return std::make_unique<Rook>(*this);
}
