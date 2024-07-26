#include "piece.h"

std::unique_ptr<Piece> createPiece(PieceType t, int playerId)
{
    return std::unique_ptr<Piece>();
}

int Piece::getPlayerId()
{
    return playerId;
}

PieceType Piece::getType()
{
    return type;
}