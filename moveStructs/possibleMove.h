#ifndef POSSIBLE_MOVE_H
#define POSSIBLE_MOVE_H
using namespace std;
#include <utility>

struct PossibleMove
{
    pair<int, int> from;
    pair<int, int> to;
    bool isCapture;
	bool isNormalMove;
    bool needFirstMove;
    bool canJump;

    PossibleMove(pair<int, int> from, pair<int, int> to, bool isCapture, bool isNormalMove, bool needFirstMove = false, bool canJump = false):
        from{from}, to{to}, isCapture{isCapture}, isNormalMove{isNormalMove}, needFirstMove{needFirstMove} {}
};

#endif