#ifndef PIECEFACTORY_H
#define PIECEFACTORY_H

#include "rook.h"
#include "bishop.h"
#include "pawn.h"
#include "king.h"
#include "knight.h"
#include "queen.h"
#include "pieceType.h"
#include <memory>

inline std::unique_ptr<Piece> createPiece(PieceType type, int playerId)
{
    switch (type)
    {
    case PieceType::Pawn:
        return std::make_unique<Pawn>(type,playerId);
    case PieceType::Rook:
        return std::make_unique<Rook>(type, playerId);
    case PieceType::Knight:
        return std::make_unique<Knight>(type, playerId);
    case PieceType::Bishop:
        return std::make_unique<Bishop>(type, playerId);
    case PieceType::Queen:
        return std::make_unique<Queen>(type, playerId);
    case PieceType::King:
        return std::make_unique<King>(type, playerId);
    default:
        return nullptr;
    }
}

#endif