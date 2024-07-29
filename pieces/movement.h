#ifndef MOVEMENT_H
#define MOVEMENT_H
#include "../moveStructs/possibleMove.h"
#include <vector>

class Movement
{
public:
    virtual vector<PossibleMove> getPossibleMoves() const = 0;
};

#endif
