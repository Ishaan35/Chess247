#include "diagonalMovement.h"
#include <algorithm>

DiagonalMovement::DiagonalMovement(Movement* next, Color color): MovementDecorator{next, color} {}
vector<PossibleMove>& DiagonalMovement::getPossibleMoves(vector<PossibleMove>& allMoves, pair<int,int> position, int rows, int cols) {
	
	// should be able to move anywhere from here diagonally (same x and y offset)
	vector<PossibleMove>& res = next->getPossibleMoves(position, rows, cols);

	for(int i = -min(rows, cols); i < min(rows, cols); i++) {
		int newX = position.first + i;
		int newY1 = position.second + i;
		int newY2 = position.second - i;
		if(0 <= newX && newX < rows) {
			if(0 <= newY1 && newY1 < cols) {
				res.push_back(PossibleMove{position, make_pair(newX, newY1), true, true});
			}
			if(0 <= newY2 && newY2 < cols) {
				res.push_back(PossibleMove{position, make_pair(newX, newY2), true, true});
			}
		}
	}
	return res;
};