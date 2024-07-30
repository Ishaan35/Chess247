#ifndef APPLICATION_H
#define APPLICATION_H

#include <memory>
#include <vector>
#include <unordered_map>
#include "./players/player.h"
#include "./inputs/inputSource.h"
#include "engine.h"

class Application {

private:
	unordered_map<string, shared_ptr<Player>> players;
	shared_ptr<InputSource> in;
	void printHighScores();

public:
	
	Application();
	void run();

};

#endif