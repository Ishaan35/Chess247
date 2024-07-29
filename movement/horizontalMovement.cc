#include "horizontalMovement.h"
#include <algorithm>

HorizontalMovement::HorizontalMovement(Movement *next, Color color) : MovementDecorator{next, color} {}
vector<PossibleMove> &HorizontalMovement::getPossibleMoves(const vector<vector<unique_ptr<Piece>>> &board, vector<PossibleMove> &allMoves, pair<int, int> position)
{

	// inside same row
	vector<PossibleMove> &res = next->getPossibleMoves(board, allMoves, position);
	for (size_t j = position.second + 1; j < board[0].size(); j++)
	{
		res.push_back(PossibleMove{position, make_pair(position.first, j)});
		if (board[position.first][j])
			break; // a piece was present. can't go further than this.
	}
	for (size_t j = position.second - 1; j >= 0; j--)
	{
		res.push_back(PossibleMove{position, make_pair(position.first, j)});
		if (board[position.first][j])
			break; // a piece was present. can't go further than this.
	}
	return res;
};