#include "graphicsDisplay.h"

GraphicsDisplay::GraphicsDisplay(int n, int w, int h, int squarew) : numPlayers{n}, width{w}, height{h}, squareWidth{squarew}, darkSquareColor{Color{184, 134, 97}}, lightSquareColor{
                                                                                                                                                                         Color{238, 215, 174}},
                                                                     window{std::make_unique<GraphicsWindow>(w, h)}
{
    // Assuming chesspiece.png is in the current directory
    // win1.renderPNG("assets/chesspiece.png", 50, 50);

    // // Draw rectangles and text
    // win1.drawRectangle(100, 100, 50, 50, 186, 104, 37);
    // win1.drawRectangle(200, 100, 50, 50, 186, 104, 37);
    // win1.drawRectangle(300, 100, 50, 50, 186, 104, 37);
    // win1.drawRectangle(50, 150, 50, 50, 186, 104, 37);
    // win1.drawRectangle(150, 150, 50, 50, 186, 104, 37);
    // win1.drawRectangle(250, 150, 50, 50, 186, 104, 37);
    // win1.drawRectangle(350, 150, 50, 50, 186, 104, 37);
    // win1.drawText("Guess the elo", 50, 50, 20.0, 0, 0, 0);

    // // Handle events (including mouse clicks)
    // win1.handleEvents();

    // // Control reaches here after handling events
    // std::cout << "Exiting..." << std::endl;

    std::unordered_map<PieceType, std::string> p0FileMapping{
        {PieceType::King, "WhiteKing.png"},
        {PieceType::Queen, "WhiteQueen.png"},
        {PieceType::Bishop, "WhiteBishop.png"},
        {PieceType::Knight, "WhiteKnight.png"},
        {PieceType::Pawn, "WhitePawn.png"},
        {PieceType::Rook, "WhiteRook.png"},
    };
    std::unordered_map<PieceType, std::string> p1FileMapping{
        {PieceType::King, "BlackKing.png"},
        {PieceType::Queen, "BlackQueen.png"},
        {PieceType::Bishop, "BlackBishop.png"},
        {PieceType::Knight, "BlackKnight.png"},
        {PieceType::Pawn, "BlackPawn.png"},
        {PieceType::Rook, "BlackRook.png"},
    };
    pieceFileMappings.push_back(std::move(p0FileMapping));
    pieceFileMappings.push_back(std::move(p1FileMapping));
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

                window->renderPNG(pieceFileMappings[board[i][j]->getPlayerId()][board[i][j]->getType()], squareWidth, squareWidth);
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