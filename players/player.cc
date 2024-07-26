#include "player.h"

std::string Player::getName()
{
    return name;
}

InputMove Player::getMove()
{
    if (auto lockedPtr = inputSource.lock())
    {
        return lockedPtr->getInput();
    }
    else
    {
        throw std::runtime_error("Input source is no longer available.");
    }
}
