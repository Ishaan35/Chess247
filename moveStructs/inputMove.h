#ifndef INPUTMOVE_H
#define INPUTMOVE_H
using namespace std;
#include <utility>
#include "../colorEnum.h"

struct InputMove
{
    pair<char, char> from;
    pair<char, char> to;
    bool isResign;
    char promotion = ' ';
    Color pieceColor;
};

#endif