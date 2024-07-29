#include "lshapedMovement.h"
#include <algorithm>

LShapedMovement::LShapedMovement(Movement* next, Color color): MovementDecorator{next, color} {}
vector<PossibleMove>& LShapedMovement::getPossibleMoves(const vector<vector<unique_ptr<Piece>>>& board, vector<PossibleMove>& allMoves, pair<int,int> position) {
	
	// need to go through all possible pairs of -2, -1, 1, 2 - for each 2, match against ones, and vice versa
	vector<PossibleMove>& res = next->getPossibleMoves(board, allMoves, position);
	vector<vector<int>> deltas = {{-1, -2}, {-1, 2}, {1, -2}, {1, 2}, {-2, -1}, {-2, 1}, {2, -1}, {2, 1}};
	for(auto v: deltas) {
		int newX = position.first + v[0];
		int newY = position.second + v[1];
		if(0 <= newX && newX < board.size() && 0 <= newY && newY < board[0].size()) {
			res.push_back(PossibleMove{position, make_pair(newX, newY)});
		}
	}
	return res;
};