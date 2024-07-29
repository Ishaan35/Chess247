#ifndef SETUPMOVE_H
#define SETUPMOVE_H
using namespace std;
#include <utility>

struct SetupMove
{
    int playerIndex = 0;
    int file = 0;
    char rank;
    bool isPlace = false;
    bool isRemove = false;
    bool isChangeTurn = false;
    bool isDone = false;
};

#endif