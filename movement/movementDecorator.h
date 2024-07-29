#ifndef MOVEMENT_DECORATOR_H
#define MOVEMENT_DECORATOR_H
#include "movement.h"
#include "../colorEnum.h"
#include <memory>

class MovementDecorator: public Movement {
protected:
	unique_ptr<Movement> next;
	Color color;
public:
	MovementDecorator(Movement* next, Color color);
	virtual ~MovementDecorator();
};

#endif