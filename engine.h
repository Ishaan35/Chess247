#ifndef ENGINE_H
#define ENGINE_H
#include <memory>
#include "chessState.h"
#include "./moveStructs/inputMove.h"

class Engine
{
    std::weak_ptr<const ChessState> chessState; // chess state should be a shared ptr in chessGame. it owns it, but permits engine to access state without owning it
    ChessState createChessStateCopy();

public:
    InputMove getBestMove(int player, int depth);
};

#endif