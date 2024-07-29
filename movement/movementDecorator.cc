#include "movementDecorator.h"

MovementDecorator::MovementDecorator(Movement* next, Color color): next{next}, color{color} {}
MovementDecorator::~MovementDecorator() {}