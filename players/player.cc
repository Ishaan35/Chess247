#include "player.h"

Player::Player(std::string name): name{name} {}


std::string Player::getName()
{
    return name;
}


void Player::incrementWon() {gamesWon++;}

int Player::getGamesWon() {
    return gamesWon;
}

void Player::setPlayerColor(Color color) {
    playerColor = color;
}