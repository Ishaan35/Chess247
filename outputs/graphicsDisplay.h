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
#include "graphicswindow.h"

struct Color
{
    int red;
    int green;
    int blue;
    Color(int r, int g, int b) : red{r}, green{g}, blue{b} {}
};

class GraphicsDisplay : public Observer
{
    std::weak_ptr<ChessState> subject;
    int numPlayers;
    int width;
    int height;
    int squareWidth;
    Color darkSquareColor;
    Color lightSquareColor;
    std::unique_ptr<GraphicsWindow> window;
    std::vector<std::unordered_map<PieceType, std::string>> pieceFileMappings;

public:
    GraphicsDisplay(int numPlayers, int w, int h, int squarew);
    void renderToScreen(const std::vector<std::vector<std::unique_ptr<Piece>>> &board);
    void notify() override;
    ~GraphicsDisplay();
};

#endif
