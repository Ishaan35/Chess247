#include "chessGame.h"
#include <vector>
using namespace std;

ChessGame::ChessGame(weak_ptr<InputSource> input) : input{input}, players{}, numActive{0} {};
// set isGameRunning to true in chess state
// runGame takes in a vector of players
// im getting white then black in player vector
// white is 0 black is 1

weak_ptr<Player> ChessGame::getWinner(vector<weak_ptr<Player>> remainingPlayers){
    for (size_t i=0; i < remainingPlayers.size(); i++){
        if (!remainingPlayers[i].expired()){
            return remainingPlayers[i];
        }
    }
}

void ChessGame::runGame(vector<weak_ptr<Player>> allPlayers){
    players = allPlayers;
    numActive = players.size();
    while (true){
        for (size_t i=0; i < players.size(); i++){
            if(auto lockedPlayer = players[i].lock()){
                InputMove currentMove = lockedPlayer->getMove();
                if(currentMove.isResign){
                    players[i].reset();
                    numActive--;
                }
                else{
                    chessState->playMove(currentMove);
                    if(chessState->isDraw()); // figure out how to output
                    if(chessState->isCheckmate()); // figure out how to output
                }
                if(numActive == 1){
                    weak_ptr<Player> winner = getWinner(players);
                    if (auto winnerLocked = winner.lock()){
                        winnerLocked->incrementWon();
                    }
                    return;
                }
            }
            else{
                throw std::runtime_error("input source no longer exists"); 
            }
        }
    }   
}
// setup get the dimensions
void ChessGame::setup(int numPlayers){
    int rows = 0;
    int cols = 0;
    if (auto inputLocked = input.lock()) {
        pair<int, int> dimensions = inputLocked->getDimensions();
        rows = dimensions.first;
        cols = dimensions.second;
    }
    ChessState chessState = ChessState{players, rows, cols};

    while(true){
        if (auto inputLocked = input.lock()){
            SetupMove setupMove = inputLocked->getSetup();
            if (setupMove.isDone) break;
            
        }
        else{
            throw std::runtime_error("input source no longer exists"); 
        }
    }
}