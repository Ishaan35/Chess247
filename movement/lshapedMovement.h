#ifndef LSHAPED_MOVEMENT_H
#define LSHAPED_MOVEMENT_H
#include "movementDecorator.h"
#include "movement.h"

class LShapedMovement: public MovementDecorator {
public:
	LShapedMovement(Movement* next, Color color);
	vector<PossibleMove>& getPossibleMoves(pair<int,int> position, int rows, int cols) override;
};

#endif