#include "pawnMovement.h"
#include <algorithm>

PawnMovement::PawnMovement(Movement *next, Color color) : MovementDecorator{next, color} {}
vector<PossibleMove> &PawnMovement::getPossibleMoves(const vector<vector<unique_ptr<Piece>>> &board, vector<PossibleMove> &allMoves, pair<int, int> position)
{

	// return 1 fwd, 2 fwd, and both diagonal capture moves

	vector<PossibleMove> &res = next->getPossibleMoves(board, allMoves, position);

	int direction = color == WHITE ? -1 : 1;
	int y = position.second;
	int x = position.first;
	int newX1 = x + direction;
	int newX2 = x + 2 * direction;

	// make sure pawn hasn't moved
	if (0 <= newX1 && static_cast<size_t>(newX1) < board.size())
	{
		if (!board[newX1][y])
		{
			if(newX1 == 0 || newX1 == board.size() -1) {
				vector<char> promos = {'Q', 'N', 'R', 'B'};
				for(int i = 0; i < promos.size(); i++) {
					res.push_back(PossibleMove{position, make_pair(newX1, y), false, promos[i]});
				}
			}
			else {
				res.push_back(PossibleMove{position, make_pair(newX1, y)});
			}
		}
		if (0 <= y - 1 && board[newX1][y - 1])
		{
			res.push_back(PossibleMove{position, make_pair(newX1, y - 1)});
		}
		if (static_cast<size_t>(y + 1) < board[0].size() && board[newX1][y + 1])
		{
			res.push_back(PossibleMove{position, make_pair(newX1, y + 1)});
		}
		if(0 <= newX2 && static_cast<size_t>(newX2) < board.size() && !board[newX2][y] && !board[x][y]->hasMoved()) {
			res.push_back(PossibleMove{position, make_pair(newX2, y)});
		}
	}

	return res;
};
