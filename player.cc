#include "player.h"

std::string Player::getName()
{
    return name;
}

InputMove Player::getMove()
{
    return std::move(inputSource->getInput());
}
