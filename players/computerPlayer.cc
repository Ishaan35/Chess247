#include "computerPlayer.h"

ComputerPlayer::ComputerPlayer(weak_ptr<InputSource> in, string name, int level): Player{in, "Computer" + to_string(level) + name}, level{level} {}

InputMove ComputerPlayer::getMove() {
	return InputMove{make_pair(0, 0), make_pair(0, 0), false};
}