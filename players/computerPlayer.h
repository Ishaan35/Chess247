#ifndef COMPUTERPLAYER_H
#define COMPUTERPLAYER_H
#include "player.h"
#include "../engine.h"

class ComputerPlayer : public Player
{
	weak_ptr<Engine> engine;
	int level;
public: 
	InputMove getMove() override;

	ComputerPlayer(int level, string name, weak_ptr<Engine> eng);
};

#endif