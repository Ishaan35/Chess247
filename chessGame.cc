#include "chessGame.h"
#include <vector>

ChessGame::ChessGame(weak_ptr<InputSource> input) : input{input}, players{}, numActive{0} {};

void ChessGame::runGame(){
    numActive = players.size();
    while (true){
        for (int i=0; i < players.size(); i++){
            if(!players[i]) continue;
            InputMove currentMove = players[i]->getMove();
            if (currentMove.isResign){
                players[i] = nullptr;
            }
            else{
                // call play move on chess state
                int lol;
            }
        }
    }   
}
