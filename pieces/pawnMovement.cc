#include "pawnMovement.h"

PawnMovement::PawnMovement(Movement* movement) : MovementDecorator{movement}{}

vector<PossibleMove> PawnMovement::getPossibleMoves() const {}