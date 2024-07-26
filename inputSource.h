#ifndef INPUTSOURCE_H
#define INPUTSOURCE_H
#include "InputMove.h"

class InputSource
{
public:
    virtual InputMove getInput() = 0; // not implemented. will receive undefined reference error on make
};

#endif