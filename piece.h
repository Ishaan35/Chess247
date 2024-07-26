#include "movement.h"
#include <memory>
#include "pieceType.h"

class Piece
{
    Movement m;
    PieceType type;
    int playerId;

public:
    Piece(PieceType t, int pId) : type{t}, playerId{pId} {}
    virtual std::unique_ptr<Piece> clone() const = 0;
    virtual ~Piece() = 0;
};