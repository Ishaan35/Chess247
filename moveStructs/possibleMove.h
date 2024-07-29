#ifndef POSSIBLEMOVE_H
#define POSSIBLEMOVE_H
using namespace std;
#include <utility>

struct PossibleMove
{
    pair<int, int> location;
    bool isCapturing = false;
};

#endif