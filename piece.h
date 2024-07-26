#ifndef PIECE_H
#define PIECE_H

#include "movement.h"
#include <memory>
#include "pieceType.h"

//so the d
class Piece
{
    Movement m;
    PieceType type;
    int playerId;

public:
    Piece(PieceType t, int pId) : type{t}, playerId{pId} {}
    virtual std::unique_ptr<Piece> clone() const = 0;
    virtual ~Piece() = default;

protected:
    void setMovement();
};
#endif