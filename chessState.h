#ifndef CHESSSTATE_H
#define CHESSSTATE_H
#include "player.h"
#include "piece.h"
#include <vector>
#include <memory>

class ChessState
{
    std::vector<std::weak_ptr<Player>> players;
    std::vector<std::vector<std::unique_ptr<Piece>>> board; //convention: relative to white. So top left is a8 and bottom right is h1
    bool isGameRunning;

    std::pair<int, int> rankFileToCoordinates(char file, char rank);

public:
    ChessState(const std::vector<std::shared_ptr<Player>> &players, int rows, int columns);
    ChessState(const ChessState &other);
    const std::vector<std::vector<std::unique_ptr<Piece>>> &getBoard();
    void defaultSetup();
    bool placePieceAtPosition(PieceType t, char file, char rank, int playerId);
};

#endif