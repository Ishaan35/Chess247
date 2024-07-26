#include "chessGame.h"
#include <vector>

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
                    // chessState->playMove(currentMove);
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
        }
    }   
}
// setup get the dimensions
void ChessGame::setup(int numPlayers){
    int rows, columns;
    // input << rows << columns;
    // ChessState chessState = ChessState{players, rows, columns};
}