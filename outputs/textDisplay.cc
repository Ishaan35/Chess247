#include "textDisplay.h"
#include "../pieces/pieceType.h"
TextDisplay::TextDisplay(int n) : numPlayers{n}
{
}

void TextDisplay::renderToTerminal(const std::vector<std::vector<std::unique_ptr<Piece>>> &board)
{
    // highest row is rank 8
    // lowest row is 1
    // leftmost file is a
    // rightmost file is h
    for (size_t i = 0; i < board.size(); i++)
    {
        std::cout << board.size() - i << " ";
        for (size_t j = 0; j < board[i].size(); j++)
        {
            if (board[i][j])
            {
                std::cout << PieceTypeConverter::getPieceAttributes(board[i][j]->getColor(), board[i][j]->getType()).character;
            }
            else
            {
                std::cout << ' ';
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    std::cout << ' ' << ' ';
    for (size_t i = 0; i < board[0].size(); i++)
        std::cout << (char)('a' + i);
    std::cout << std::endl;
}

void TextDisplay::setSubject(std::shared_ptr<Subject> s, std::shared_ptr<Observer> o)
{
    // if we did not initialize subject yet (i.e if it was not done in the setup), attach it now.
    if (!subject.lock())
    {
        subject = std::dynamic_pointer_cast<ChessState>(s);
        if (auto subjectWkPtr = subject.lock())
        {
            subjectWkPtr->attach(o);
        }
        notify();
    }
}

void TextDisplay::notify()
{
    if (auto chessState = subject.lock())
    {
        const std::vector<std::vector<std::unique_ptr<Piece>>> &board = chessState->getBoard();
        renderToTerminal(board);
        if (chessState->isGameRunning())
        {
            if (chessState->getCheckmate())
            {
                std::cout << "Game Over By Checkmate..." << ((chessState->getWinner() == Color::BLACK) ? " Black wins" : " White wins") << std::endl;
            }
            else if (chessState->isDraw())
            {
                std::cout << "Game Over By Stalemate..." << std::endl;
            }
        }
    }
}

TextDisplay::~TextDisplay() {}
