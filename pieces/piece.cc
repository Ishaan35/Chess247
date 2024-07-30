#include "piece.h"

Color Piece::getColor()
{
    return color;
}

PieceType Piece::getType()
{
    return type;
}

vector<PossibleMove> Piece::getPossibleMoves(pair<int, int> position, std::vector<std::vector<std::unique_ptr<Piece>>> &board)
{
    std::vector<PossibleMove> possibleMoves;
    return m->getPossibleMoves(board, possibleMoves, position);
}

bool Piece::hasMoved() const
{
    return has_moved;
}