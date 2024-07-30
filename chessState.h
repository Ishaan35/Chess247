#ifndef CHESSSTATE_H
#define CHESSSTATE_H
#include "./players/player.h"
#include "./pieces/piece.h"
#include <vector>
#include <memory>
#include "subject.h"
#include "colorEnum.h"
#include "./pieces/pieceType.h"

class ChessState : public Subject
{
    const std::vector<std::weak_ptr<Player>> &players;
    std::vector<std::vector<std::unique_ptr<Piece>>> board; // convention: relative to white. So top left is a8 and bottom right is h1
    bool gameRunning = false;
    bool isDefaultSetup = true;
    bool resign = false;
    bool draw = false;
    bool checkmate = false;
    Color winner;
    Color currentTurn;
    std::pair<int, int> rankFileToCoordinates(char file, char rank);
    void safelyMove(unique_ptr<Piece> &fromPiece, pair<int, int> fromCoords, pair<int, int> toCoords, Color pieceColor, char promotion = ' ');

public:
    ChessState(const std::vector<std::weak_ptr<Player>> &players, int rows, int columns);
    ChessState(const ChessState &other);
    const std::vector<std::vector<std::unique_ptr<Piece>>> &getBoard() const;
    void defaultSetup();
    bool removePiece(char file, char rank);
    bool placePieceAtPosition(PieceType t, char file, char rank, Color color, bool isSetup = false);
    bool isValidMove(PossibleMove possibleMove, char promotion = ' ');
    void playMove(InputMove &inputMove);
    bool isDraw();
    bool isCheck();
    bool calculateCheckmate();
    void setGameRunning(bool val);
    bool isGameRunning();
    bool isCoordinateInBounds(std::pair<int, int> &coords);
    void setResign(bool target);
    void setDraw(bool target);
    void setCheckmate(bool target);
    void setWinner(Color color);
    Color getPlayerTurn();
    bool getResign();
    bool getDraw();
    bool getCheckmate();
    void setIsDefaultSetup(bool val);
    void setCurrentTurn(Color turn);
    Color getWinner();
    bool isTargeted(Color color, pair<int, int> position);
    void verifySetup();
    int getChessBoardEvaluation();
    std::vector<PossibleMove> getAllPossibleMoves(Color player);
    ~ChessState();
};

#endif