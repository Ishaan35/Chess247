#ifndef PAWNMOVEMENT_H
#define PAWNMOVEMENT_H
#include "movement.h"
#include "movementDecorator.h"
#include "../moveStructs/possibleMove.h"
#include <vector>

class PawnMovement: public MovementDecorator{
public:
    PawnMovement(Movement* movement);
    vector<PossibleMove> getPossibleMoves() const override;
};

#endif