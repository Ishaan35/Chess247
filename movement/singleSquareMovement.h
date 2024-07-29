#ifndef SINGLE_SQUARE_MOVEMENT_H
#define SINGLE_SQUARE_MOVEMENT_H
#include "movementDecorator.h"
#include "movement.h"
#include "../pieces/piece.h"

class SingleSquareMovement : public MovementDecorator
{
public:
	SingleSquareMovement(Movement *next, Color color);
	vector<PossibleMove> &getPossibleMoves(const vector<vector<unique_ptr<Piece>>> &board, vector<PossibleMove> &allMoves, pair<int, int> position) override;
};

#endif