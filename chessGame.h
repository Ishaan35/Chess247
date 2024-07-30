#include "chessState.h"
#include "moveStructs/inputMove.h"
#include "moveStructs/setupMove.h"
#include "players/player.h"
#include "inputs/inputSource.h"
#include "chessState.h"
#include "./colorEnum.h"

using namespace std;

class InputMove;

class ChessState;

class ChessGame{
    weak_ptr<InputSource> input;
    vector<weak_ptr<Player>> players; // players must be a vector of weak pointers
    int numActive;
    shared_ptr<ChessState> chessState;
    // shared pointer to chessState owned

public:
    ChessGame(weak_ptr<InputSource> input);

    void runGame(weak_ptr<Player> whitePlayer, weak_ptr<Player> blackPlayer, std::vector<std::shared_ptr<Observer>> observers); // calls play move in loop, prompts each player for a move, and if there is no remaining pieces, then game is done. nested loop
    // checks if move is resign, sets player pointer to null

    weak_ptr<Player> getWinner(vector<weak_ptr<Player>> remainingPlayers);

    void setup(std::vector<std::shared_ptr<Observer>> observers);
};
