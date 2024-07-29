#ifndef MOVEMENT_H
#define MOVEMENT_H
#include "../moveStructs/possibleMove.h"
#include "../pieces/piece.h"
#include <vector>
using namespace std;

class Movement {
public:
	virtual vector<PossibleMove>& getPossibleMoves(const vector<vector<unique_ptr<Piece>>>& board, vector<PossibleMove>& allMoves, pair<int,int> position)=0;
};

#endif