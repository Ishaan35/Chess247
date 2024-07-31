#ifndef LSHAPED_MOVEMENT_H
#define LSHAPED_MOVEMENT_H
#include "movementDecorator.h"
#include "movement.h"
#include "../pieces/piece.h"

class LShapedMovement : public MovementDecorator
{
public:
	LShapedMovement(Movement *next, Color color);
	vector<PossibleMove> &getPossibleMoves(const vector<vector<unique_ptr<Piece>>> &board, vector<PossibleMove> &allMoves, pair<int, int> position) override;
};

#endif
