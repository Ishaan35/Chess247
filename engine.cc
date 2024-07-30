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
        return make_pair((char)(position.second + 'a'), (char)(lockedState->getBoard().size() - position.first + '0'));
    }
    else
    {
        throw std::runtime_error("no state exists");
    }
}

InputMove Engine::convertPossibleMoveToInputMove(PossibleMove pm, Color c)
{

    return InputMove{convertToChars(pm.from), convertToChars(pm.to), false, pm.promotion, c};
}

InputMove Engine::getLevel1Move(Color playerColor)
{
    // get all possible moves for this player color
    vector<PossibleMove> allMoves;

    if (auto lockedPtr = chessState.lock())
    {   
        ChessState tempState = *lockedPtr;
        allMoves = tempState.getAllPossibleMoves(playerColor);

        // choose a random move from this until find one that is completely legal
        // get a random number from hardware, seed the generator, and define the range
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> distr(0, allMoves.size() - 1);
        int randIndex = distr(gen);
        return convertPossibleMoveToInputMove(allMoves[randIndex], playerColor);
    }
    else {
        throw std::runtime_error("no state exists");
    }
}

InputMove Engine::getLevel2Move(Color playerColor) {
    // get all possible moves for this player color
    vector<PossibleMove> capturingCheckMoves;

    if(auto lockedPtr = chessState.lock()) {    
        pair<int, int> otherKingPos;
        Color opposite = (playerColor == Color::WHITE) ? Color::BLACK : Color::WHITE;
        ChessState copiedState = *lockedPtr;
        // unique_ptr<ChessState> copiedState = make_unique<ChessState>(ChessState{*lockedPtr});

        for(int i = 0; i < copiedState.getBoard().size(); i++) {
            for(int j = 0; j < copiedState.getBoard()[0].size(); j++) {
                if(copiedState.getBoard()[i][j] && copiedState.getBoard()[i][j]->getColor() == opposite && copiedState.getBoard()[i][j]->getType() == PieceType::King){
                    otherKingPos = {i,j};
                    break;
                }
            }
        }

        vector<PossibleMove> allMoves = copiedState.getAllPossibleMoves(playerColor);
        for (int k=0; k < allMoves.size(); k++){
            int fromRow = allMoves[k].from.first;
            int fromCol = allMoves[k].from.second;
            int toRow = allMoves[k].to.first;
            int toCol = allMoves[k].to.second;

            if(copiedState.getBoard()[toRow][toCol] && copiedState.getBoard()[toRow][toCol]->getColor() == opposite){
                capturingCheckMoves.push_back(allMoves[k]);
                continue;
            }

            InputMove inputMove = convertPossibleMoveToInputMove(allMoves[k], playerColor);

            ChessState temp = copiedState;
            temp.playMove(inputMove);
            if(temp.isTargeted(opposite, otherKingPos)){
                capturingCheckMoves.push_back(allMoves[k]);
            }
        }

        random_device rd;
        mt19937 gen(rd()); 
        if(capturingCheckMoves.size() > 0){
            uniform_int_distribution<> distr(0, capturingCheckMoves.size()-1);
            int randIndex = distr(gen);

            return convertPossibleMoveToInputMove(capturingCheckMoves[randIndex], playerColor);
        }
        else{
            uniform_int_distribution<> distr(0, allMoves.size()-1);
            int randIndex = distr(gen);

            return convertPossibleMoveToInputMove(allMoves[randIndex], playerColor);
        }
    }
}

InputMove Engine::getLevel3Move(Color playerColor) {}
InputMove Engine::getLevel4Move(Color playerColor) {}

int Engine::minimax(ChessState state, int depth, Color player)
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
            ChessState copyState = state;
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
            ChessState copyState = state;
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
