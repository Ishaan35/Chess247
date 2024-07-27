#include "humanPlayer.h"

HumanPlayer::HumanPlayer(weak_ptr<InputSource> in, string name): Player{name}, inputSource{in} {}

InputMove HumanPlayer::getMove() {
	if(auto lockedPtr = inputSource.lock()) {
		return lockedPtr->getInput();
	} else
    {
        throw std::runtime_error("Input source is no longer available.");
    }
}
