#include "textDisplay.h"

TextDisplay::TextDisplay() {}

char TextDisplay::convertPieceToChar(PieceType type, int playerId)
{
    if (type == PieceType::King)
    {
    }
    return ' ';
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
                // std::cout << convertPieceToChar(board[i][j])
            }
        }
    }
}

void TextDisplay::notify()
{
    if (auto chessState = subject.lock())
    {
        const std::vector<std::vector<std::unique_ptr<Piece>>> &board = chessState->getBoard();
        renderToTerminal(board);
    }
}

TextDisplay::~TextDisplay() {}