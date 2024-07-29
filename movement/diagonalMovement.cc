#include "diagonalMovement.h"
#include <algorithm>

DiagonalMovement::DiagonalMovement(Movement *next, Color color) : MovementDecorator{next, color} {}
vector<PossibleMove> &DiagonalMovement::getPossibleMoves(const vector<vector<unique_ptr<Piece>>> &board, vector<PossibleMove> &allMoves, pair<int, int> position)
{

	// should be able to move anywhere from here diagonally (same x and y offset)
	vector<PossibleMove> &res = next->getPossibleMoves(board, allMoves, position);

	int x = position.first;
	int y = position.second;

	// keep going along one of the four diagonals until you reach a piece
	for (size_t i = 1; y + i < board[0].size() && x + i < board.size(); i++)
	{
		res.push_back(PossibleMove{position, make_pair(x + i, y + i)});
		if (board[x + i][y + i])
			break;
	}
	for (size_t i = 1; 0 <= y - i && x + i < board.size(); i++)
	{
		res.push_back(PossibleMove{position, make_pair(x + i, y - i)});
		if (board[x + i][y - i])
			break;
	}
	for (size_t i = 1; y + i < board[0].size() && 0 <= x - i; i++)
	{
		res.push_back(PossibleMove{position, make_pair(x - i, y + i)});
		if (board[x - i][y + i])
			break;
	}
	for (int i = 1; 0 <= y - i && 0 <= x - i; i++)
	{
		res.push_back(PossibleMove{position, make_pair(x - i, y - i)});
		if (board[x - i][y - i])
			break;
	}

	return res;
};