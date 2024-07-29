#ifndef SETUPMOVE_H
#define SETUPMOVE_H
using namespace std;
#include <utility>
#include "../pieces/pieceType.h"

struct SetupMove
{
    int playerIndex = 0;
    char file;
    char rank;
    bool isPlace = false;
    bool isRemove = false;
    bool isChangeTurn = false;
    bool isDone = false;
    PieceType pieceType;
};

#endif