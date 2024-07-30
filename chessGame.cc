#include "chessGame.h"
#include <vector>
#include <iostream>
using namespace std;

ChessGame::ChessGame(weak_ptr<InputSource> input) : input{input}, players{}, numActive{0} {};
// set isGameRunning to true in chess state
// im getting white then black in player vector
// white is 0 black is 1

// need to play move and place piece during setup right now

void ChessGame::runGame(weak_ptr<Player> whitePlayer, weak_ptr<Player> blackPlayer, std::vector<std::shared_ptr<Observer>> observers)
{
    players = {whitePlayer, blackPlayer};
    numActive = players.size();
    // if we did not initialize the chess state in setup, do it here
    if (!chessState)
    {
        chessState = std::make_shared<ChessState>(players, 8, 8);
        chessState->setGameRunning(true);
        chessState->defaultSetup();
        for (auto &obs : observers)
        {
            obs->setSubject(chessState, obs);
        }
    }
    while (true)
    {
        for (size_t i = 0; i < players.size(); i++)
        {
            if (auto lockedPlayer = players[i].lock())
            {
                InputMove currentMove = lockedPlayer->getMove();
                currentMove.pieceColor = static_cast<Color>(i);
                if (currentMove.isResign)
                {
                    int winner = (i + 1) % 2;
                    Color winnerColor = static_cast<Color>(winner);
                    chessState->setResign(true);
                    chessState->setWinner(winnerColor);
                    return;
                }
                else
                {
                    chessState->playMove(currentMove);
                    if (chessState->isCheckmate())
                    {
                        Color winnerColor = static_cast<Color>(i);
                        chessState->setCheckmate(true);
                        chessState->setWinner(winnerColor);
                        return;
                    }
                    if (chessState->isDraw())
                    {
                        chessState->setDraw(true);
                        return;
                    }
                }
            }
            else
            {
                continue;
            }
        }
    }
}
// setup get the dimensions
void ChessGame::setup(std::vector<std::shared_ptr<Observer>> observers)
{
    int rows = 0;
    int cols = 0;
    if (auto inputLocked = input.lock())
    {
        pair<int, int> dimensions = inputLocked->getDimensions();
        rows = dimensions.first;
        cols = dimensions.second;
    }
    chessState = std::make_shared<ChessState>(players, rows, cols);
    for (auto &obs : observers)
    {
        obs->setSubject(chessState, obs);
    }

    while (true)
    {
        if (auto inputLocked = input.lock())
        {
            SetupMove setupMove = inputLocked->getSetup();
            PieceType type = setupMove.pieceType;
            chessState->placePieceAtPosition(type, setupMove.file, setupMove.rank, setupMove.playerColor);
            chessState->notifyObservers();
        }
        else
        {
            throw std::runtime_error("input source no longer exists");
        }
    }
}