#include "queen.h"
#include "../movement/horizontalMovement.h"
#include "../movement/verticalMovement.h"
#include "../movement/diagonalMovement.h"
#include "../movement/emptyMovement.h"

Queen::Queen(PieceType t, Color color): 
    Piece{t, color, new DiagonalMovement{new HorizontalMovement{new VerticalMovement{new EmptyMovement{}, color}, color}, color}} {}

std::unique_ptr<Piece> Queen::clone()
{
    return std::make_unique<Queen>(*this);
}
