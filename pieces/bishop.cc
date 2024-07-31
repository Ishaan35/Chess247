#include "bishop.h"
#include "../movement/diagonalMovement.h"
#include "../movement/emptyMovement.h"

Bishop::Bishop(PieceType t, Color color) : Piece{t, color, new DiagonalMovement{new EmptyMovement{}, color}} {}

std::unique_ptr<Piece> Bishop::clone()
{
    return std::make_unique<Bishop>(*this);
}
