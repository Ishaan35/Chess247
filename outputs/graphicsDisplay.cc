#include "graphicsDisplay.h"
#include "../pieces/pieceType.h"

GraphicsDisplay::GraphicsDisplay(int n, int w, int h, int squarew) : numPlayers{n}, width{w}, height{h}, squareWidth{squarew}, darkSquareColor{RGBColor{184, 134, 97}}, lightSquareColor{
                                                                                                                                                                            RGBColor{238, 215, 174}}
                                                                     
{

}

void GraphicsDisplay::setSubject(std::shared_ptr<Subject> s, std::shared_ptr<Observer> o)
{
    if (!subject.lock())
    {
        
        subject = std::dynamic_pointer_cast<ChessState>(s);
        if (auto subjectWkPtr = subject.lock())
        {
            subjectWkPtr->attach(o);
        }
        window = std::make_unique<GraphicsWindow>(width, height);
        notify();
    }
}
void GraphicsDisplay::renderToScreen(const std::vector<std::vector<std::unique_ptr<Piece>>> &board)
{
    for (size_t i = 0; i < board.size(); i++)
    {
        std::cout << board.size() - i << " ";
        for (size_t j = 0; j < board[i].size(); j++)
        {
            int y = i * squareWidth;
            int x = j * squareWidth;
            if (i % 2 == 0)
            {
                if (j % 2 == 0) // light
                    window->drawRectangle(x, y, squareWidth, squareWidth, lightSquareColor.red, lightSquareColor.green, lightSquareColor.blue);
                else // dark
                    window->drawRectangle(x, y, squareWidth, squareWidth, darkSquareColor.red, darkSquareColor.green, darkSquareColor.blue);
            }
            else
            {
                if (j % 2 == 1) // light
                    window->drawRectangle(x, y, squareWidth, squareWidth, lightSquareColor.red, lightSquareColor.green, lightSquareColor.blue);
                else // dark
                    window->drawRectangle(x, y, squareWidth, squareWidth, darkSquareColor.red, darkSquareColor.green, darkSquareColor.blue);
            }
            if (board[i][j])
            {
                window->renderPNG(PieceTypeConverter::getPieceAttributes(board[i][j]->getColor(), board[i][j]->getType()).filename, squareWidth, squareWidth, x, y);
            }
        }
        std::cout << std::endl;
    }
}

void GraphicsDisplay::notify()
{
    if (auto chessState = subject.lock())
    {
        const std::vector<std::vector<std::unique_ptr<Piece>>> &board = chessState->getBoard();
        renderToScreen(board);
    }
}

GraphicsDisplay::~GraphicsDisplay() {}