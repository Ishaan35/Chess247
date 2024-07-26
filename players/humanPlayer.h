#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H

#include "player.h"
class HumanPlayer : public Player
{
public:
	InputMove getMove() override;

	HumanPlayer(weak_ptr<InputSource>, string name);

};

#endif