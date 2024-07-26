#include "chessState.h"
#include "./pieces/pieceFactory.h"

ChessState::ChessState(const std::vector<std::shared_ptr<Player>> &players, int rows, int columns) : board(rows) //r x c grid all nullptr by default
{
    for (const auto &player : players)
    {
        this->players.push_back(player); // insert weak pointers to our player vector
    }
    for(int i = 0; i < rows; i++){
        board[i] = std::vector<std::unique_ptr<Piece>>(columns);
    }
}

std::pair<int, int>  ChessState::rankFileToCoordinates(char file, char rank)
{
    int i = board.size() - (int)(file - '0');
    int j = (int)(file - 'a');
    return std::pair<int, int>{i, j};
}

bool ChessState::placePieceAtPosition(PieceType t, char file, char rank, int playerId){
    std::pair<int, int> coords = rankFileToCoordinates(file, rank);
    if (coords.first >= static_cast<int>(board.size()) || coords.second >= static_cast<int>(board[0].size()) || coords.first < 0 || coords.second < 0)
    {
        return false;
    }

    //add piece to state here
    board[coords.first][coords.second] = createPiece(t, playerId);
    

    return true;
}

ChessState::ChessState(const ChessState &other)
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

const std::vector<std::vector<std::unique_ptr<Piece>>> &ChessState::getBoard()
{
    return board;
}