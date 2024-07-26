#ifndef GRAPHICSDISPLAY_H
#define GRAPHICSDISPLAY_H
#include "observer.h"
#include <memory>
#include "../chessState.h"
#include <iostream>
#include "../pieces/pieceType.h"
#include <vector>
#include <unordered_map>
#include <stdexcept>

class GraphicsDisplay : public Observer
{
    std::weak_ptr<ChessState> subject;
    int numPlayers;

public:
    GraphicsDisplay(int numPlayers);
    void renderToScreen(const std::vector<std::vector<std::unique_ptr<Piece>>> &board);
    void notify() override;
    ~GraphicsDisplay();
};

#endif
