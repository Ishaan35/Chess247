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
#include "../colorEnum.h"
#include <iostream>

inline std::unique_ptr<Piece> createPiece(PieceType type, Color color)
{
    switch (type)
    {
    case PieceType::Pawn:
        return std::make_unique<Pawn>(type,color);
    case PieceType::Rook:
        return std::make_unique<Rook>(type, color);
    case PieceType::Knight:
        return std::make_unique<Knight>(type, color);
    case PieceType::Bishop:
        return std::make_unique<Bishop>(type, color);
    case PieceType::Queen:
        return std::make_unique<Queen>(type, color);
    case PieceType::King:
        return std::make_unique<King>(type, color);
    default:
        std::cout <<"default nullptr piece" << std::endl;
        return nullptr;
    }
}

#endif
