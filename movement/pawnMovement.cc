#include "pawnMovement.h"
#include <algorithm>

PawnMovement::PawnMovement(Movement* next, Color color): MovementDecorator{next, color} {}
vector<PossibleMove>& PawnMovement::getPossibleMoves(const vector<vector<unique_ptr<Piece>>>& board, vector<PossibleMove>& allMoves, pair<int,int> position) {
	
	// return 1 fwd, 2 fwd, and both diagonal capture moves

	vector<PossibleMove>& res = next->getPossibleMoves(board, allMoves, position);

	int direction = color == WHITE ? 1 : -1;
	int y = position.second;
	int x = position.first;
	int newX1 = x + direction;
	int newX2 = x + 2 * direction;

	// make sure pawn hasn't moved
	if(0 <= newX1 && newX1 < board.size()) {
		if(!board[newX1][y]) {
			res.push_back(PossibleMove{position, make_pair(newX1, y)});
		}
		if(0 <= y - 1 && board[newX1][y - 1]) {
			res.push_back(PossibleMove{position, make_pair(newX1, y-1)});
		}
		if(y + 1 < board[0].size() && board[newX1][y + 1]) {
			res.push_back(PossibleMove{position, make_pair(newX1, y+1)});
		}
		if(0 <= newX2 && newX2 < board.size() && !board[x][y]->hasMoved()) {
			res.push_back(PossibleMove{position, make_pair(newX2, y)});
		}
	}

	return res;
};