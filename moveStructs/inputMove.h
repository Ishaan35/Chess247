#ifndef INPUTMOVE_H
#define INPUTMOVE_H
using namespace std;
#include <utility>

struct InputMove
{
    pair<char, char> from;
    pair<char, char> to;
    bool isResign;
};

#endif