#include "computerPlayer.h"

ComputerPlayer::ComputerPlayer(int level, string name, weak_ptr<Engine> engine): Player{"Computer" + to_string(level) + name}, level{level}, engine{engine} {}

InputMove ComputerPlayer::getMove() {
	if(auto lockedPtr = engine.lock()) {
		return lockedPtr->getBestMove(playerColor, level);
	} else
    {
        throw std::runtime_error("Engine source is no longer available.");
    }
}