#include "./movement.h"
#include "../moveStructs/possibleMove.h"
#include <vector>

class EmptyMovement : public Movement{
public:
    vector<PossibleMove> getPossibleMoves() const override;
};