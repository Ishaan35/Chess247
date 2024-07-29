#ifndef MOVEMENT_H
#define MOVEMENT_H
#include "../moveStructs/possibleMove.h"
#include <vector>
using namespace std;

class Movement {
public:
	virtual vector<PossibleMove>& getPossibleMoves(vector<PossibleMove>& allMoves, pair<int,int> position, int rows, int cols)=0;
};

#endif