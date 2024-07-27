#include "player.h"

Player::Player(std::string name): name{name} {}


std::string Player::getName()
{
    return name;
}


void Player::incrementWon() {gamesWon++;}