#ifndef PLAYER_H
#define PLAYER_H
#include "../moveStructs/inputMove.h"
#include "../inputs/inputSource.h"
#include <string>
#include <memory>
#include <utility>

class Player
{
    std::string name;
    std::shared_ptr<InputSource> inputSource;

public:
    virtual InputMove getMove() = 0;
    std::string getName();
};

#endif