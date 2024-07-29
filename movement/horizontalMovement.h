#ifndef HORIZONTAL_MOVEMENT_H
#define HORIZONTAL_MOVEMENT_H
#include "movementDecorator.h"
#include "movement.h"

class HorizontalMovement: public MovementDecorator {
public:
	HorizontalMovement(Movement* next, Color color);
	vector<PossibleMove>& getPossibleMoves(vector<PossibleMove>& allMoves, pair<int,int> position, int rows, int cols) override;
};

#endif