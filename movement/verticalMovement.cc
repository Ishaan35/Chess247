#include "verticalMovement.h"
#include <algorithm>
#include <iostream>
#include "../pieces/piece.h"

VerticalMovement::VerticalMovement(Movement *next, Color color) : MovementDecorator{next, color} {}
vector<PossibleMove> &VerticalMovement::getPossibleMoves(const vector<vector<unique_ptr<Piece>>> &board, vector<PossibleMove> &allMoves, pair<int, int> position)
{
	// inside same col
	// position.first is i, and position.second is j. (row/col)
	vector<PossibleMove> &res = next->getPossibleMoves(board, allMoves, position);

	for (size_t i = position.first + 1; i < board.size(); i++)
	{
		if (board[i][position.second])
		{
			// a piece was present. can't go further than this. If it is the opposite color, we can capture it. otherwise if it is our own color, cant capture it.
			if (board[i][position.second]->getColor() != color)
			{
				res.push_back(PossibleMove{position, make_pair(i, position.second)});
			}
			break;
		}
		else
		{
			res.push_back(PossibleMove{position, make_pair(i, position.second)});
		}
	}
	for (int i = position.first - 1; i >= 0; i--)
	{
		if (board[i][position.second])
		{
			// a piece was present. can't go further than this. If it is the opposite color, we can capture it. otherwise if it is our own color, cant capture it.
			if (board[i][position.second]->getColor() != color)
			{
				res.push_back(PossibleMove{position, make_pair(i, position.second)});
			}
			break;
		}
		else
		{
			res.push_back(PossibleMove{position, make_pair(i, position.second)});
		}
	}
	return res;
};