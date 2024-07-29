#ifndef CHESSSTATE_H
#define CHESSSTATE_H
#include "./players/player.h"
#include "./pieces/piece.h"
#include <vector>
#include <memory>
#include "subject.h"
#include "colorEnum.h"

class ChessState : public Subject
{
    const std::vector<std::weak_ptr<Player>> &players;
    std::vector<std::vector<std::unique_ptr<Piece>>> board; // convention: relative to white. So top left is a8 and bottom right is h1
    bool isGameRunning;
    bool resign;
    bool draw;
    bool checkmate;
    Color winner;

    std::pair<int, int> rankFileToCoordinates(char file, char rank);

public:
    ChessState(const std::vector<std::weak_ptr<Player>> &players, int rows, int columns);
    ChessState(const ChessState &other);
    const std::vector<std::vector<std::unique_ptr<Piece>>> &getBoard();
    void defaultSetup();
    bool placePieceAtPosition(PieceType t, char file, char rank, Color color);
    bool isValidMove(pair<int, int> toCoords, pair<int, int> fromCoords);
    void playMove(InputMove &inputMove);
    bool isDraw();
    bool isCheckmate();
    void setGameRunning();
    bool isCoordinateInBounds(std::pair<int, int>& coords);
    void setResign(bool target);
    void setDraw(bool target);
    void setCheckmate(bool target); 
    bool getResign();
    bool getDraw();
    bool getCheckmate();
    ~ChessState();
};

#endif