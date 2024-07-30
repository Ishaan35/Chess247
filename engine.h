#ifndef ENGINE_H
#define ENGINE_H
#include <memory>
#include "chessState.h"
#include "./moveStructs/inputMove.h"
#include "colorEnum.h"

class Engine
{
    std::weak_ptr<const ChessState> chessState; // chess state should be a shared ptr in chessGame. it owns it, but permits engine to access state without owning it
    ChessState createChessStateCopy();
    pair<char, char> convertToChars(pair<int, int> position);

    InputMove getLevel1Move(Color playerColor);
    InputMove getLevel2Move(Color playerColor);
    InputMove getLevel3Move(Color playerColor);
    InputMove getLevel4Move(Color playerColor);
    InputMove maximize(ChessState chessStateCopy, int depth);
    InputMove minimize(ChessState chessStateCopy, int depth);
    int minimax(ChessState chessStateCopy, int depth, Color player);

public:
    InputMove getBestMove(Color playerColor, int depth);
    void setChessState(shared_ptr<const ChessState>);
};

#endif