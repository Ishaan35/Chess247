#ifndef POSSIBLE_MOVE_H
#define POSSIBLE_MOVE_H
using namespace std;
#include <utility>

struct PossibleMove
{
    pair<int, int> from;
    pair<int, int> to;
    bool isCastling;

    PossibleMove(pair<int, int> from, pair<int, int> to, bool isCastling = false):
        from{from}, to{to}, isCastling{isCastling} {}

    bool operator==(const PossibleMove& other) const {
        return from == other.from && to == other.to;
    }
};

#endif