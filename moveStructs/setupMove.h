#ifndef SETUPMOVE_H
#define SETUPMOVE_H
using namespace std;
#include <utility>
#include "../pieces/pieceType.h"
#include "../colorEnum.h"

struct SetupMove
{
    Color playerColor;
    char file;
    char rank;
    bool isPlace = false;
    bool isRemove = false;
    bool isChangeTurn = false;
    bool isDone = false;
    PieceType pieceType;
};

#endif
