#ifndef VERTICAL_MOVEMENT_H
#define VERTICAL_MOVEMENT_H
#include "movementDecorator.h"
#include "movement.h"

class VerticalMovement: public MovementDecorator {
public:
	VerticalMovement(Movement* next, Color color);
	vector<PossibleMove>& getPossibleMoves(const vector<vector<unique_ptr<Piece>>>& board, vector<PossibleMove>& allMoves, pair<int,int> position) override;
};

#endif