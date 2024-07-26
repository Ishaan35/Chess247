#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H
#include "observer.h"
#include <memory>
#include "../chessState.h"
#include <iostream>
#include "../pieces/pieceType.h"
#include <vector>
#include <unordered_map>
#include <stdexcept>

class TextDisplay : public Observer
{
    std::weak_ptr<ChessState> subject;
    int numPlayers;
    std::vector<std::unordered_map<PieceType, char>> pieceMappings;

    char convertPieceToChar(PieceType p, int playerId);

public:
    TextDisplay(int numPlayers);
    void renderToTerminal(const std::vector<std::vector<std::unique_ptr<Piece>>> &board);
    void notify() override;
    ~TextDisplay();
};

#endif
