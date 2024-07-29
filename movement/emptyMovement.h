#ifndef EMPTY_MOVEMENT_H
#define EMPTY_MOVEMENT_H
#include "movement.h"

class EmptyMovement : public Movement
{
public:
	vector<PossibleMove>& getPossibleMoves(vector<PossibleMove>& allMoves, pair<int,int> position, int rows, int cols) override;
};

#endif