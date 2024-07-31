#ifndef POSSIBLE_MOVE_H
#define POSSIBLE_MOVE_H
using namespace std;
#include <utility>

struct PossibleMove
{
    pair<int, int> from;
    pair<int, int> to;
    bool isCastling;
    char promotion;

    PossibleMove(pair<int, int> from, pair<int, int> to, bool isCastling = false, char promotion = ' '):
        from{from}, to{to}, isCastling{isCastling}, promotion{promotion} {}

    bool operator==(const PossibleMove& other) const {
        return from == other.from && to == other.to;
    }
};

#endif
