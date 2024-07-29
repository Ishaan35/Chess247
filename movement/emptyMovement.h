#ifndef EMPTY_MOVEMENT_H
#define EMPTY_MOVEMENT_H
#include "movement.h"

class EmptyMovement : public Movement
{
public:
	vector<PossibleMove>& getPossibleMoves(const vector<vector<unique_ptr<Piece>>>& board, vector<PossibleMove>& allMoves, pair<int,int> position) override;
};

#endif