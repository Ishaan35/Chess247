#ifndef DIAGONAL_MOVEMENT_H
#define DIAGONAL_MOVEMENT_H
#include "movementDecorator.h"
#include "movement.h"

class DiagonalMovement: public MovementDecorator {
public:
	DiagonalMovement(Movement* next, Color color);
	vector<PossibleMove>& getPossibleMoves(vector<PossibleMove>& allMoves, pair<int,int> position, int rows, int cols) override;
};

#endif