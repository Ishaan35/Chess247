#ifndef PAWN_MOVEMENT_H
#define PAWN_MOVEMENT_H
#include "movementDecorator.h"
#include "movement.h"

class PawnMovement: public MovementDecorator {
public:
	PawnMovement(Movement* next, Color color);
	vector<PossibleMove>& getPossibleMoves(pair<int,int> position, int rows, int cols) override;
};

#endif