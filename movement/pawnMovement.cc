#include "pawnMovement.h"
#include <algorithm>

PawnMovement::PawnMovement(Movement* next, Color color): MovementDecorator{next, color} {}
vector<PossibleMove>& PawnMovement::getPossibleMoves(vector<PossibleMove>& allMoves, pair<int,int> position, int rows, int cols) {
	
	// return 1 fwd, 2 fwd, and both diagonal capture moves

	vector<PossibleMove>& res = next->getPossibleMoves(allMoves, position, rows, cols);

	int direction = color == WHITE ? 1 : -1;
	int newX1 = position.first + direction;
	int newX2 = position.first + 2 * direction;

	if(0 <= newX1 && newX1 < rows) {
		res.push_back(PossibleMove{position, make_pair(newX1, position.second), false, true});
		if(0 <= position.second - 1) {
			res.push_back(PossibleMove{position, make_pair(newX1, position.second-1), true, false});
		}
		if(position.second + 1 < cols) {
			res.push_back(PossibleMove{position, make_pair(newX1, position.second+1), true, false});
		}
		if(0 <= newX2 && newX2 < rows) {
			res.push_back(PossibleMove{position, make_pair(newX2, position.second), false, true, true});
		}
	}

	return res;
};