#ifndef SINGLE_SQUARE_MOVEMENT_H
#define SINGLE_SQUARE_MOVEMENT_H
#include "movementDecorator.h"
#include "movement.h"

class SingleSquareMovement: public MovementDecorator {
public:
	SingleSquareMovement(Movement* next, Color color);
	vector<PossibleMove>& getPossibleMoves(pair<int,int> position, int rows, int cols) override;
};

#endif