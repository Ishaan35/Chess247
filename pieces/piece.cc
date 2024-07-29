#include "piece.h"

std::unique_ptr<Piece> createPiece(PieceType t, Color color)
{
    return std::unique_ptr<Piece>();
}

int Piece::getPlayerId()
{
    return color;
}

PieceType Piece::getType()
{
    return type;
}

vector<PossibleMove> Piece::getPossibleMoves(pair<int, int> position, int rows, int cols) {
    return m->getPossibleMoves(position, rows, cols);
}