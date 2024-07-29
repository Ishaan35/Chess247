#include "computerPlayer.h"

ComputerPlayer::ComputerPlayer(int level, string name): Player{"Computer" + to_string(level) + name}, level{level} {}

InputMove ComputerPlayer::getMove() {
	if(auto lockedPtr = engine.lock()) {
		return lockedPtr->getBestMove(playerColor, level);
	} else
    {
        throw std::runtime_error("Engine source is no longer available.");
    }
}

void ComputerPlayer::setEngine(weak_ptr<Engine> eng, Color playerCol) {
	engine = eng;
	playerColor = playerCol;
}