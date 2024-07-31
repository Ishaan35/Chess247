#ifndef INPUTSOURCE_H
#define INPUTSOURCE_H
#include "../moveStructs/inputMove.h"
#include "../moveStructs/setupMove.h"
#include <utility>
#include "../pieces/pieceType.h"

class InputSource
{
public:
    virtual InputMove getInput() = 0; // not implemented. will receive undefined reference error on make
    virtual SetupMove getSetup() = 0;
    virtual pair<int, int> getDimensions() = 0;
};

#endif
