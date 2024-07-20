#include "chessState.h"

ChessState::ChessState(const std::vector<std::shared_ptr<Player>> &players)
{
    for (const auto &player : players)
    {
        this->players.push_back(player); // insert weak pointers to our player vector
    }
}

ChessState::ChessState(const ChessState &other)
{
    for (size_t i = 0; i < other.board.size(); i++)
    {
        board.push_back(std::vector<std::unique_ptr<Piece>>{});
        for (const auto &piece : other.board[i])
        {
            // Review with Awab:
            //  causes a compile error if we just try to do make_unique<Piece>(*piece)
            //  because Piece is an abstract class and we can't copy it. we need a clone method. It won't know which piece subclass constructor to call
            //  We can't give it an explicit dynamic type since this could be any type of piece.
            //  so clone method returns an instance of itself
            board[i].push_back(piece ? piece->clone() : nullptr);
        }
    }
}