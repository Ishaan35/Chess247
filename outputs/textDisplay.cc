#include "textDisplay.h"

TextDisplay::TextDisplay(int n) : numPlayers{n}
{
    std::unordered_map<PieceType, char> p0Mapping{
        {PieceType::King, 'K'},
        {PieceType::Queen, 'Q'},
        {PieceType::Bishop, 'B'},
        {PieceType::Knight, 'N'},
        {PieceType::Pawn, 'P'},
        {PieceType::Rook, 'R'},
    };
    std::unordered_map<PieceType, char> p1Mapping{
        {PieceType::King, 'k'},
        {PieceType::Queen, 'q'},
        {PieceType::Bishop, 'b'},
        {PieceType::Knight, 'n'},
        {PieceType::Pawn, 'p'},
        {PieceType::Rook, 'r'},
    };
    pieceMappings.push_back(std::move(p0Mapping));
    pieceMappings.push_back(std::move(p1Mapping));
}

char TextDisplay::convertPieceToChar(PieceType type, int playerId)
{
    if (playerId >= static_cast<int>(pieceMappings.size()))
        throw std::runtime_error("Invalid player id");

    return pieceMappings[playerId][type];
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
                std::cout << convertPieceToChar(board[i][j]->getType(), board[i][j]->getPlayerId());
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl
              << std::endl;
    for (size_t i = 0; i < board[0].size(); i++)
    {
        std::cout << (char)('a' + i) << std::endl;
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