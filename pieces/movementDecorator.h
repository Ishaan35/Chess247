#include "movement.h"

class MovementDecorator : public Movement{
protected:
    Movement* next;
public:
    MovementDecorator(Movement *movement): next{movement} {}
    virtual ~MovementDecorator() {delete next;}
};