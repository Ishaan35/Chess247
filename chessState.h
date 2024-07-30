#ifndef CHESSSTATE_H
#define CHESSSTATE_H
#include "./players/player.h"
#include "./pieces/piece.h"
#include <vector>
#include <memory>
#include "subject.h"
#include "colorEnum.h"
#include "inputs/inputSource.h"

class ChessState : public Subject
{
    const std::vector<std::weak_ptr<Player>> &players;
    std::vector<std::vector<std::unique_ptr<Piece>>> board; // convention: relative to white. So top left is a8 and bottom right is h1
    bool isGameRunning = false;
    bool isDefaultSetup = true;
    bool resign;
    bool draw;
    bool checkmate;
    Color winner;
    Color currentTurn;
    weak_ptr<InputSource> inputSource;
    std::pair<int, int> rankFileToCoordinates(char file, char rank);

public:
    ChessState(const std::vector<std::weak_ptr<Player>> &players, weak_ptr<InputSource> input, int rows, int columns);
    ChessState(const ChessState &other);
    const std::vector<std::vector<std::unique_ptr<Piece>>> &getBoard();
    void defaultSetup();
    bool placePieceAtPosition(PieceType t, char file, char rank, Color color);
    bool isValidMove(PossibleMove possibleMove);
    void playMove(InputMove &inputMove);
    bool isDraw();
    bool isCheck();
    bool isCheckmate();
    void setGameRunning(bool val);
    bool isCoordinateInBounds(std::pair<int, int> &coords);
    void setResign(bool target);
    void setDraw(bool target);
    void setCheckmate(bool target);
    void setWinner(Color color);
    bool getResign();
    bool getDraw();
    bool getCheckmate();
    void setIsDefaultSetup(bool val);
    Color getWinner();
    bool isTargeted(Color color, pair<int, int> position);
    ~ChessState();
};

#endif