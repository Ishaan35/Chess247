#include "verticalMovement.h"
#include <algorithm>

VerticalMovement::VerticalMovement(Movement* next, Color color): MovementDecorator{next, color} {}
vector<PossibleMove>& VerticalMovement::getPossibleMoves(vector<PossibleMove>& allMoves, pair<int,int> position, int rows, int cols) {
	
	// inside same col
	vector<PossibleMove>& res = next->getPossibleMoves(allMoves, position, rows, cols);

	for(int i = 0;i < rows; i++) {
		res.push_back(PossibleMove{position, make_pair(position.first, i), true, true});
	}
	return res;
};