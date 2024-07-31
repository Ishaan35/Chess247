#ifndef HORIZONTAL_MOVEMENT_H
#define HORIZONTAL_MOVEMENT_H
#include "movementDecorator.h"
#include "movement.h"

class HorizontalMovement: public MovementDecorator {
public:
	HorizontalMovement(Movement* next, Color color);
	vector<PossibleMove>& getPossibleMoves(const vector<vector<unique_ptr<Piece>>>& board, vector<PossibleMove>& allMoves, pair<int,int> position) override;
};

#endif
