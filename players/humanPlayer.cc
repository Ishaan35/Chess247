#include "humanPlayer.h"

HumanPlayer::HumanPlayer(weak_ptr<InputSource> in, string name): Player{in, name} {}

InputMove HumanPlayer::getMove() {
	return InputMove{make_pair(0, 0), make_pair(0, 0), false};
}