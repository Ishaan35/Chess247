#include "movement.h"
#include <memory>

class Piece
{
    Movement m;
    int playerId;

public:
    Piece() {}
    virtual std::unique_ptr<Piece> clone() const = 0;
    virtual ~Piece() = 0;
};