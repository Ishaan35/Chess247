#include "engine.h"
#include <stdexcept>

ChessState Engine::createChessStateCopy()
{
    if (auto sharedPtr = chessState.lock())
    {
        ChessState chessStateCopy(*sharedPtr);
        return chessStateCopy;
    }
    else
    {
        throw std::runtime_error("Chess state is not defined");
    }
}

InputMove Engine::getBestMove(Color playerColor, int depth)
{
    return InputMove{}; // Stub
}
