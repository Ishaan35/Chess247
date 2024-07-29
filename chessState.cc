#include "chessState.h"
#include "./pieces/pieceFactory.h"

void ChessState::setGameRunning()
{
    isGameRunning = true;
}

void ChessState::setResign(bool target)
{
    resign = target;
    notifyObservers();
}

void ChessState::setDraw(bool target)
{
    draw = target;
    notifyObservers();
}

void ChessState::setCheckmate(bool target)
{
    checkmate = target;
    notifyObservers();
}

bool ChessState::getDraw()
{
    return draw;
}

bool ChessState::getResign()
{
    return resign;
}

bool ChessState::getCheckmate()
{
    return checkmate;
}

bool ChessState::isCoordinateInBounds(std::pair<int, int> &coords)
{
    if (coords.first >= static_cast<int>(board.size()) || coords.second >= static_cast<int>(board[0].size()) || coords.first < 0 || coords.second < 0)
    {
        return false;
    }
}

bool ChessState::isDraw() { return false; };

bool ChessState::isCheckmate() { return false; };

bool ChessState::isValidMove(pair<int, int> toCoords, pair<int, int> fromCoords)
{
    return false;
};

void ChessState::playMove(InputMove &inputMove)
{
    std::pair<int, int> fromCoords = rankFileToCoordinates(inputMove.from.first, inputMove.from.second);
    std::pair<int, int> toCoords = rankFileToCoordinates(inputMove.to.first, inputMove.to.second);

    if (!isCoordinateInBounds(fromCoords) || !isCoordinateInBounds(toCoords))
    {
        throw std::runtime_error("provided coordinates are not in bounds");
    }
};

ChessState::ChessState(const std::vector<std::weak_ptr<Player>> &players, int rows, int columns) : players{players}, board(rows) // r x c grid all nullptr by default
{
    for (int i = 0; i < rows; i++)
    {
        board[i] = std::vector<std::unique_ptr<Piece>>(columns);
    }
}

std::pair<int, int> ChessState::rankFileToCoordinates(char file, char rank)
{
    int i = board.size() - (int)(file - '0');
    int j = (int)(file - 'a');
    return std::pair<int, int>{i, j};
}

bool ChessState::placePieceAtPosition(PieceType t, char file, char rank, Color color)
{
    std::pair<int, int> coords = rankFileToCoordinates(file, rank);
    if (!isCoordinateInBounds(coords))
    {
        return false;
    }
    // add piece to state here
    board[coords.first][coords.second] = createPiece(t, color);

    return true;
}

ChessState::ChessState(const ChessState &other) : players{other.players}
{
    // Deep copy of the board
    for (size_t i = 0; i < other.board.size(); i++)
    {
        board[i].reserve(other.board[i].size());
        for (const auto &piece : other.board[i])
        {
            board[i].push_back(piece ? piece->clone() : nullptr);
        }
    }
}

ChessState::~ChessState() {}

const std::vector<std::vector<std::unique_ptr<Piece>>> &ChessState::getBoard()
{
    return board;
}

void ChessState::defaultSetup()
{
}