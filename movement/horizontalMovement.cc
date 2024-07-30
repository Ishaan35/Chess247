#include "horizontalMovement.h"
#include <algorithm>
#include <iostream>
#include "../pieces/piece.h"

HorizontalMovement::HorizontalMovement(Movement *next, Color color) : MovementDecorator{next, color} {}
vector<PossibleMove> &HorizontalMovement::getPossibleMoves(const vector<vector<unique_ptr<Piece>>> &board, vector<PossibleMove> &allMoves, pair<int, int> position)
{

	// inside same row
	vector<PossibleMove> &res = next->getPossibleMoves(board, allMoves, position);
	for (int j = position.second + 1; j < board[0].size(); j++)
	{
		if (board[position.first][j])
		{
			// a piece was present. can't go further than this. If it is the opposite color, we can capture it. otherwise if it is our own color, cant capture it.
			if (board[position.first][j]->getColor() != color)
			{
				res.push_back(PossibleMove{position, make_pair(position.first, j)});
			}
			break;
		}
		else
		{
			res.push_back(PossibleMove{position, make_pair(position.first, j)});
		}
	}
	for (int j = position.second - 1; j >= 0; j--)
	{
		if (board[position.first][j])
		{
			// a piece was present. can't go further than this. If it is the opposite color, we can capture it. otherwise if it is our own color, cant capture it.
			if (board[position.first][j]->getColor() != color)
			{
				res.push_back(PossibleMove{position, make_pair(position.first, j)});
			}
			break;
		}
		else
		{
			res.push_back(PossibleMove{position, make_pair(position.first, j)});
		}
	}
	return res;
};