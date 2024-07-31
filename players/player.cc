#include "player.h"

Player::Player(std::string name): name{name} {}


std::string Player::getName()
{
    return name;
}


void Player::incrementWon(bool draw) {
    if(!draw) gamesWon++;
    else gamesWon += 0.5;
}

double Player::getGamesWon() {
    return gamesWon;
}

void Player::setPlayerColor(Color color) {
    playerColor = color;
}
