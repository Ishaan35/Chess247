#include "singleSquareMovement.h"
#include <algorithm>

SingleSquareMovement::SingleSquareMovement(Movement *next, Color color) : MovementDecorator{next, color} {}
vector<PossibleMove> &SingleSquareMovement::getPossibleMoves(const vector<vector<unique_ptr<Piece>>> &board, vector<PossibleMove> &allMoves, pair<int, int> position)
{

	// return 1 fwd, 2 fwd, and both diagonal capture moves
	int rows = static_cast<int>(board.size());
	int cols = static_cast<int>(board[0].size());

	vector<PossibleMove> &res = next->getPossibleMoves(board, allMoves, position);

	vector<int> deltas = {-1, 0, 1};

	for (int i : deltas)
	{
		for (int j : deltas)
		{
			if (i == 0 && j == 0)
				continue;

			int newX = position.first + i;
			int newY = position.second + j;

			if (0 <= newX && newX < rows && 0 <= newY && newY < cols)
			{
				res.push_back(PossibleMove{position, make_pair(newX, newY)});
			}
		}
	}

	if (board[position.first][position.second]->getType() == PieceType::King && !board[position.first][position.second]->hasMoved())
	{
		// kingside castle check
		if (0 <= position.second - 2)
		{
			// check if rook is present on the same rank, on the left corner of the board, and and has not moved, and king also has not moved
			if (board[position.first][position.second]->getType() == PieceType::King && !board[position.first][position.second]->hasMoved())
			{
				if (board[position.first][0] && board[position.first][0]->getType() == PieceType::Rook && !board[position.first][0]->hasMoved())
				{
					res.push_back(PossibleMove{position, make_pair(position.first, position.second - 2)});
				}
			}
		}
		if (position.second + 2 < cols)
		{
			// queenside castle check
			//  check if rook is present on the same rank, on the right corner of the board, and and has not moved, and king also has not moved
			{
				if (board[position.first][cols - 1] && board[position.first][cols - 1]->getType() == PieceType::Rook && !board[position.first][cols - 1]->hasMoved())
				{
					res.push_back(PossibleMove{position, make_pair(position.first, position.second - 2)});
				}
			}
		}
	}

	return res;
};