#include "verticalMovement.h"
#include <algorithm>
#include <iostream>

VerticalMovement::VerticalMovement(Movement *next, Color color) : MovementDecorator{next, color} {}
vector<PossibleMove> &VerticalMovement::getPossibleMoves(const vector<vector<unique_ptr<Piece>>> &board, vector<PossibleMove> &allMoves, pair<int, int> position)
{
	// inside same col
	// position.first is i, and position.second is j. (row/col)
	vector<PossibleMove> &res = next->getPossibleMoves(board, allMoves, position);
	
	for (size_t i = position.first + 1; i < board.size(); i++)
	{
		res.push_back(PossibleMove{position, make_pair(i, position.second)});
		if (board[i][position.second])
			break; // break since we cannpt move through this piece.
	}
	for (int i = position.first - 1; i >= 0; i--)
	{
		res.push_back(PossibleMove{position, make_pair(i, position.second)});
		if (board[i][position.second])
			break;
	}
	return res;
};