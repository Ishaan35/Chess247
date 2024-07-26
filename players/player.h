#ifndef PLAYER_H
#define PLAYER_H
#include "../moveStructs/inputMove.h"
#include "../inputs/inputSource.h"
#include <string>
#include <memory>
#include <utility>
#include <stdexcept>

using namespace std;

class Player
{
    std::string name;
    std::weak_ptr<InputSource> inputSource;
    int gamesWon;
    int rating;

public:
    Player(weak_ptr<InputSource> inputSource, std::string name);
    virtual InputMove getMove() = 0;
    std::string getName();
    void incrementWon();
};

#endif