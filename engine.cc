#include "engine.h"
#include <stdexcept>
#include <random>
#include <limits>

ChessState Engine::createChessStateCopy()
{
    if (auto sharedPtr = chessState.lock())
    {
        ChessState chessStateCopy(*sharedPtr);
        return chessStateCopy;
    }
    else
    {
        throw std::runtime_error("Chess state is not defined");
    }
}

pair<char, char> Engine::convertToChars(pair<int, int> position)
{
    // we're getting rowIndex, colIndex
    // convert to a-h (cols), 8-1 (rows)
    if (auto lockedState = chessState.lock())
    {
        return make_pair((char)(position.second + 'a'), (char)(lockedState->getBoard().size() - position.first));
    }
    else
    {
        throw std::runtime_error("no state exists");
    }
}

InputMove Engine::getLevel1Move(Color playerColor)
{

    // get all possible moves for this player color
    vector<PossibleMove> allMoves;

    if (auto lockedPtr = chessState.lock())
    {
        const vector<vector<unique_ptr<Piece>>> &board = lockedPtr->getBoard();
        for (int i = 0; i < board.size(); i++)
        {
            for (int j = 0; j < board[0].size(); j++)
            {
                if (board[i][j] && board[i][j]->getColor() == playerColor)
                {
                    vector<PossibleMove> currMoves = board[i][j]->getPossibleMoves(make_pair(i, j), board);
                    allMoves.insert(allMoves.end(), currMoves.begin(), currMoves.end());
                }
            }
        }

        // choose a random move from this until find one that is completely legal
        // get a random number from hardware, seed the generator, and define the range
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> distr(0, allMoves.size() - 1);
        int randIndex = distr(gen);

        // figure out if the move is a promotion and select random between "Q", "R", "K", "B";
        const unique_ptr<Piece> &fromPiece = board[allMoves[randIndex].from.first][allMoves[randIndex].from.second];
        int nextRow = allMoves[randIndex].to.first;
        char randPromo = ' ';
        if (fromPiece->getType() == PieceType::Pawn && nextRow == 0 || nextRow == board.size() - 1)
        {
            int randPromoInd = distr(gen) % 4;
            vector<char> promos = {'Q', 'R', 'N', 'R'};
            randPromo = promos[randPromoInd];
        }

        return InputMove{convertToChars(allMoves[randIndex].from), convertToChars(allMoves[randIndex].to), false, randPromo, fromPiece->getColor()};
    }
}

InputMove Engine::getLevel2Move(Color playerColor) {}
InputMove Engine::getLevel3Move(Color playerColor) {}
InputMove Engine::getLevel4Move(Color playerColor)
{
    // get all possible valid moves for current player
    if (auto lockedstate = chessState.lock())
    {
        ChessState tempState = *lockedstate;
        vector<PossibleMove> validMoves = tempState.getAllPossibleMoves(playerColor);

        if (playerColor == Color::WHITE)
        {
            int maxMove = std::numeric_limits<int>::min();
            InputMove bestMove;
            for (PossibleMove pm : validMoves)
            {
                ChessState copy = tempState;
                InputMove move = convertPossibleMoveToInputMove(pm, playerColor);
                copy.playMove(move);
                int bestEval = minimax(copy, 3, Color::BLACK);
                if (bestEval > maxMove)
                {
                    maxMove = bestEval;
                    bestMove = move;
                }
            }
            return bestMove;
        }
        else
        {
            int minMove = std::numeric_limits<int>::max();
            InputMove bestMove;
            for (PossibleMove pm : validMoves)
            {
                ChessState copy = tempState;
                InputMove move = convertPossibleMoveToInputMove(pm, playerColor);
                copy.playMove(move);
                int worstEval = minimax(copy, 3, Color::WHITE);
                if (worstEval < minMove)
                {
                    minMove = worstEval;
                    bestMove = move;
                }
            }
            return bestMove;
        }
    }
}

InputMove Engine::convertPossibleMoveToInputMove(PossibleMove pm, Color c)
{

    return InputMove{convertToChars(pm.from), convertToChars(pm.to), false, pm.promotion, c};
}

int Engine::minimax(ChessState &state, int depth, Color player)
{
    if (depth == 0 || state.getCheckmate() || state.isDraw() || state.getResign())
    {
        return state.getChessBoardEvaluation();
    }

    if (player == Color::WHITE)
    {
        int maxEval = std::numeric_limits<int>::min();

        std::vector<PossibleMove> possibleMoves = state.getAllPossibleMoves(player);
        for (PossibleMove move : possibleMoves)
        {
            ChessState copyState{state};
            InputMove convertedMove = convertPossibleMoveToInputMove(move, player);
            copyState.playMove(convertedMove);
            int eval = minimax(copyState, depth - 1, Color::BLACK);
            maxEval = std::max(maxEval, eval);
        }
        return maxEval;
    }
    else
    {
        int minEval = std::numeric_limits<int>::max();
        std::vector<PossibleMove> possibleMoves = state.getAllPossibleMoves(player);
        for (PossibleMove move : possibleMoves)
        {
            ChessState copyState{state};
            InputMove convertedMove = convertPossibleMoveToInputMove(move, player);
            copyState.playMove(convertedMove);
            int eval = minimax(copyState, depth - 1, Color::WHITE);
            minEval = std::min(minEval, eval);
        }
        return minEval;
    }
}

// get best move for white
// get all moves for white
// play each one on a state
// ge tthe evaluation using minimax
// choose the move that resulted in the max eval

InputMove Engine::getBestMove(Color playerColor, int depth)
{
    switch (depth)
    {
    case 1:
        return getLevel1Move(playerColor);
    case 2:
        return getLevel2Move(playerColor);
    case 3:
        return getLevel3Move(playerColor);
    case 4:
        return getLevel4Move(playerColor);
    default:
        throw std::runtime_error("invalid depth provided");
    }
}

void Engine::setChessState(shared_ptr<const ChessState> state)
{
    chessState = state;
}
