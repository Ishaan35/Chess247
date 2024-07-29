#include "singleSquareMovement.h"
#include <algorithm>

SingleSquareMovement::SingleSquareMovement(Movement* next, Color color): MovementDecorator{next, color} {}
vector<PossibleMove>& SingleSquareMovement::getPossibleMoves(vector<PossibleMove>& allMoves, pair<int,int> position, int rows, int cols) {
	
	// return 1 fwd, 2 fwd, and both diagonal capture moves

	vector<PossibleMove>& res = next->getPossibleMoves(allMoves, position, rows, cols);

	vector<int> deltas = {-1, 0, 1};

	for(int i: deltas) {
		for(int j: deltas) {
			if(i == 0 && j == 0) continue;

			int newX = position.first + i;
			int newY = position.second + j;

			if(0 <= newX && newX < rows && 0 <= newY && newY < cols) {
				res.push_back(PossibleMove{position, make_pair(newX, newY), true, true});
			}
		}
	}

	if(0 <= position.second - 2) {
		res.push_back(PossibleMove{position, make_pair(position.first, position.second - 2), false, true, true});
	}
	
	if(position.second + 2 < cols) {
		res.push_back(PossibleMove{position, make_pair(position.first, position.second + 2), false, true, true});
	}

	return res;
};