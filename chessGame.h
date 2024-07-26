#include "chessState.h"
#include "moveStructs/inputMove.h"
#include "players/player.h"
#include "inputs/inputSource.h"
#include "chessState.h"
using namespace std;

class InputMove;

class ChessState;

class ChessGame{
    weak_ptr<InputSource> input;
    vector<Player*> players; // players must be a vector of weak pointers
    int numActive;
    // shared pointer to chessState owned

public:
    ChessGame(weak_ptr<InputSource> input);

    void runGame(); // calls play move in loop, prompts each player for a move, and if there is no remaining pieces, then game is done. nested loop
    // checks if move is resign, sets player pointer to null 

    void setup();
};
