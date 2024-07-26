#ifndef COMPUTERPLAYER_H
#define COMPUTERPLAYER_H
#include "player.h"

class ComputerPlayer : public Player
{

	int level;
public: 
	InputMove getMove() override;

	ComputerPlayer(weak_ptr<InputSource>, string name, int level);

};

#endif