#ifndef PIECE_H
#define PIECE_H

#include "movement.h"
#include <memory>
#include "pieceType.h"

// so the d
class Piece
{

    PieceType type;
    int playerId;

protected:
    Movement *m;

public:
    Piece(PieceType t, int pId) : type{t}, playerId{pId} {}
    virtual std::unique_ptr<Piece> clone() = 0;
    virtual ~Piece() = default;
    PieceType getType();
    int getPlayerId();
};
#endif