#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H

#include "player.h"
class HumanPlayer : public Player
{
	std::weak_ptr<InputSource> inputSource;

public:
	InputMove getMove() override;

	HumanPlayer(weak_ptr<InputSource>, string name);

};

#endif
