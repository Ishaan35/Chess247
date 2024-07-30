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
    int gamesWon;
    int rating;
protected:
    Color playerColor;

public:
    Player(std::string name);
    virtual InputMove getMove() = 0;
    std::string getName();
    void incrementWon();
    int getGamesWon();
    void setPlayerColor(Color color);
};

#endif