#include "horizontalMovement.h"
#include <algorithm>

HorizontalMovement::HorizontalMovement(Movement* next, Color color): MovementDecorator{next, color} {}
vector<PossibleMove>& HorizontalMovement::getPossibleMoves(pair<int,int> position, int rows, int cols) {
	
	// inside same row
	vector<PossibleMove>& res = next->getPossibleMoves(position, rows, cols);

	for(int i = 0;i < cols; i++) {
		res.push_back(PossibleMove{position, make_pair(i, position.second), true, true});
	}
	return res;
};