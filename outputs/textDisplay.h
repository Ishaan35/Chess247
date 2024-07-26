#ifndef GRAPHICSOBSERVER_H
#define GRAPHICSOBSERVER_H
#include "observer.h"
#include <memory>
#include "../chessState.h"

class TextDisplay : public Observer
{
    std::weak_ptr<ChessState> subject;

public:
    TextDisplay();
    void renderToTerminal(std::vector<std::vector<std::unique_ptr<Piece>>> &board);
    void notify() override;
    ~TextDisplay();
};

#endif
