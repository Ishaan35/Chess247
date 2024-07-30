#include "engine.h"
#include <stdexcept>
#include <random>

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

pair<char, char> Engine::convertToChars(pair<int, int> position) {
    // we're getting rowIndex, colIndex
    // convert to a-h (cols), 8-1 (rows)
    if(auto lockedState = chessState.lock()) {
        return make_pair(position.second + 'a', lockedState->getBoard().size() - position.first);
    }
    else {
        throw std::runtime_error("no state exists");
    }
}

InputMove Engine::getLevel1Move(Color playerColor) {

    // get all possible moves for this player color
    vector<PossibleMove> allMoves;

    if(auto lockedPtr = chessState.lock()) {
        const vector<vector<unique_ptr<Piece>>>& board = lockedPtr->getBoard();
        for(int i = 0; i < board.size(); i++) {
            for(int j = 0; j < board[0].size(); j++) {
                if(board[i][j] && board[i][j]->getColor() == playerColor) {
                    vector<PossibleMove> currMoves = board[i][j]->getPossibleMoves(make_pair(i, j), board);
                    allMoves.insert(allMoves.end(), currMoves.begin(), currMoves.end());
                }
            }
        }

        // choose a random move from this until find one that is completely legal
        // get a random number from hardware, seed the generator, and define the range
        random_device rd;
        mt19937 gen(rd()); 
        uniform_int_distribution<> distr(0, allMoves.size()-1);
        int randIndex = distr(gen);

        // figure out if the move is a promotion and select random between "Q", "R", "K", "B";
        const unique_ptr<Piece>& fromPiece = board[allMoves[randIndex].from.first][allMoves[randIndex].from.second];
        int nextRow = allMoves[randIndex].to.first;
        char randPromo = ' ';
        if(fromPiece->getType() == PieceType::Pawn && nextRow == 0 || nextRow == board.size() - 1) {
            int randPromoInd = distr(gen) % 4;
            vector<char> promos = {'Q', 'R', 'N', 'R'};
            randPromo = promos[randPromoInd];
        }

        return InputMove{convertToChars(allMoves[randIndex].from), convertToChars(allMoves[randIndex].to), false, randPromo, fromPiece->getColor()};
    }
}

InputMove Engine::getLevel2Move(Color playerColor) {}
InputMove Engine::getLevel3Move(Color playerColor) {}
InputMove Engine::getLevel4Move(Color playerColor) {}

InputMove Engine::getBestMove(Color playerColor, int depth)
{
    switch(depth) {
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

void Engine::setChessState(shared_ptr<const ChessState> state) {
    chessState = state;
}
