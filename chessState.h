#ifndef CHESSSTATE_H
#define CHESSSTATE_H
#include "player.h"
#include "piece.h"
#include <vector>
#include <memory>

class ChessState
{
    std::vector<std::weak_ptr<Player>> players;
    std::vector<std::vector<std::unique_ptr<Piece>>> board;

public:
    ChessState(const std::vector<std::shared_ptr<Player>> &players);
    ChessState(const ChessState &other);
    const std::vector<std::vector<std::unique_ptr<Piece>>> &getBoard();
};

#endif