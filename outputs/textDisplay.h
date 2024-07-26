#ifndef GRAPHICSOBSERVER_H
#define GRAPHICSOBSERVER_H
#include "observer.h"
#include <memory>
#include "../chessState.h"
#include <iostream>
#include "../pieces/pieceType.h"

class TextDisplay : public Observer
{
    std::weak_ptr<ChessState> subject;

    char convertPieceToChar(PieceType p, int playerId);

public:
    TextDisplay();
    void renderToTerminal(const std::vector<std::vector<std::unique_ptr<Piece>>> &board);
    void notify() override;
    ~TextDisplay();
};

#endif
