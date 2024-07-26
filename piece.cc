#include "piece.h"
void Piece::setMovement()
{
    // so children constructors can implement the configuration for the Movement decorator on their own. Don't want to add any logic for that here;
}

std::unique_ptr<Piece> createPiece(PieceType t, int playerId)
{
    return std::unique_ptr<Piece>();
}
