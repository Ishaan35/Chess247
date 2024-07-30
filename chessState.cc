#include "chessState.h"
#include "./pieces/pieceFactory.h"

using namespace std;

void ChessState::verifySetup()
{
    int whiteKingCount = 0;
    int blackKingCount = 0;
    pair<int, int> whiteKingCoords{-1, -1};
    pair<int, int> blackKingCoords{-1, -1};

    for (int i = 0; i < static_cast<int>(board.size()); i++)
    {
        for (int j = 0; j < static_cast<int>(board[i].size()); j++)
        {
            if (board[i][j])
            {
                if (board[i][j]->getColor() == Color::WHITE && board[i][j]->getType() == PieceType::King)
                {
                    whiteKingCount++;
                    whiteKingCoords = {i, j};
                }
                else if (board[i][j]->getColor() == Color::BLACK && board[i][j]->getType() == PieceType::King)
                {
                    blackKingCount++;
                    blackKingCoords = {i, j};
                }
                else if (board[i][j]->getType() == PieceType::Pawn && (i == 0 || i == static_cast<int>(board.size()) - 1))
                {
                    throw std::runtime_error("pawn is on the back rank");
                }
            }
        }
    }
    if (whiteKingCount != 1)
    {
        throw std::runtime_error("White must have exactly one king");
    }
    if (blackKingCount != 1)
    {
        throw std::runtime_error("Black must have exactly one king");
    }

    if (isTargeted(Color::WHITE, whiteKingCoords))
    {
        throw std::runtime_error("White king is in check in setup, invalid");
    }
    else if (isTargeted(Color::BLACK, blackKingCoords))
    {
        throw std::runtime_error("Black king is in check in setup, invalid");
    }
    return;
}

bool ChessState::removePiece(char file, char rank)
{
    std::pair<int, int> coords = rankFileToCoordinates(file, rank);
    if (!isCoordinateInBounds(coords))
    {
        return false;
    }
    // reset/delete piece
    board[coords.first][coords.second].reset();
    notifyObservers();
    return true;
}

void ChessState::setCurrentTurn(Color turn)
{
    currentTurn = turn;
}

void ChessState::setIsDefaultSetup(bool val)
{
    isDefaultSetup = val;
}

void ChessState::setWinner(Color winnerColor)
{
    winner = winnerColor;
    if (auto lockedPlayer = players[winnerColor].lock())
    {
        lockedPlayer->incrementWon(false);
    }
}

void ChessState::setGameRunning(bool val)
{
    gameRunning = val;
}

bool ChessState::isGameRunning()
{
    return gameRunning;
}

void ChessState::setResign(bool target)
{
    resign = target;
    notifyObservers();
}

void ChessState::setDraw(bool target)
{
    draw = target;
    if (auto lockedWhite = players[0].lock())
    {
        lockedWhite->incrementWon(true);
    }
    if (auto lockedBlack = players[1].lock())
    {
        lockedBlack->incrementWon(true);
    }
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
    notifyObservers();
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
    return true;
}

bool ChessState::isTargeted(Color color, pair<int, int> position)
{
    Color oppositeColor = (color == Color::BLACK) ? Color::WHITE : Color::BLACK;
    int row = position.first;
    int col = position.second;
    for (int i = 0; i < board.size(); i++)
    {
        for (int j = 0; j < board[i].size(); j++)
        {
            if (board[i][j] && board[i][j]->getColor() == oppositeColor)
            {
                pair<int, int> opponent{i, j};
                vector<PossibleMove> possibleMoves = board[i][j]->getPossibleMoves(opponent, board);
                for (size_t k = 0; k < possibleMoves.size(); k++)
                {
                    if (possibleMoves[k].to.first == row && possibleMoves[k].to.second == col)
                    { // the opponent's piece can reach the given target
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

bool ChessState::isDraw()
{
    int rows = board.size();
    int cols = board[0].size();
    for (size_t i = 0; i < board.size(); i++)
    {
        for (size_t j = 0; j < board[i].size(); j++)
        {
            if (board[i][j] && currentTurn == board[i][j]->getColor())
            {
                pair<int, int> position{i, j};
                if (board[i][j]->getType() == PieceType::King && isTargeted(currentTurn, position))
                {
                    return false;
                }
                if (board[3][0])
                {
                    int i;
                }
                cout << "not king" << endl;
                vector<PossibleMove> possibleMoves = board[i][j]->getPossibleMoves(position, board);
                cout << "poss moves gotten" << endl;
                for (size_t k = 0; k < possibleMoves.size(); k++)
                {
                    if (isValidMove(possibleMoves[k]))
                    {
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

bool ChessState::calculateCheckmate()
{
    for (size_t i = 0; i < board.size(); i++)
    {
        for (size_t j = 0; j < board[i].size(); j++)
        {
            if (board[i][j] && board[i][j]->getType() == PieceType::King && board[i][j]->getColor() == currentTurn)
            {
                pair<int, int> kingPos{i, j};
                if (!isTargeted(currentTurn, kingPos))
                    return false; // not checkmate if not in check
                vector<PossibleMove> allMoves;
                cout << "King pos found" << endl;
                for (int i = 0; i < board.size(); i++)
                {
                    for (int j = 0; j < board[0].size(); j++)
                    {
                        if (board[i][j] && board[i][j]->getColor() == currentTurn)
                        {
                            vector<PossibleMove> currMoves = board[i][j]->getPossibleMoves(make_pair(i, j), board);
                            allMoves.insert(allMoves.end(), currMoves.begin(), currMoves.end());
                        }
                    }
                }
                cout << "all possible moves for the black pieces accumulated" << endl;
                for (int k = 0; k < allMoves.size(); k++)
                {
                    cout << k;
                    if (allMoves[k].isCastling)
                        continue;
                    cout << "1";
                    unique_ptr<Piece> toPiece = board[allMoves[k].to.first][allMoves[k].to.second] ? board[allMoves[k].to.first][allMoves[k].to.second]->clone() : nullptr;
                    cout << "2";

                    unique_ptr<Piece> fromPiece = board[allMoves[k].from.first][allMoves[k].from.second]->clone();
                    cout << "3";

                    board[allMoves[k].to.first][allMoves[k].to.second] = fromPiece->clone();
                    cout << "4";

                    board[allMoves[k].from.first][allMoves[k].from.second] = nullptr;
                    cout << "5";

                    // check if king is still in check
                    bool result = true;
                    if (isTargeted(currentTurn, make_pair(allMoves[k].to.first, allMoves[k].to.second)))
                    {
                        result = false;
                    }
                    cout << "6";

                    // revert changes and return result
                    board[allMoves[k].from.first][allMoves[k].from.second] = fromPiece->clone();
                    cout << "7";

                    board[allMoves[k].to.first][allMoves[k].to.second] = toPiece ? toPiece->clone() : nullptr;
                    cout << "8" << endl;

                    if (result)
                        return false;
                }
                cout << "checkmate function no error" << endl;
                // vector<PossibleMove> possibleMoves = board[i][j]->getPossibleMoves(kingPos, board);
                // for (size_t k=0; k<possibleMoves.size(); k++){
                //     if(isValidMove(possibleMoves[k])){
                //         return false;
                //     }
                // }
                return true;
            }
        }
    }
};

bool ChessState::isValidMove(PossibleMove move, char promotion)
{
    // coordinates in bound
    pair<int, int> from = move.from;
    pair<int, int> to = move.to;
    if (!isCoordinateInBounds(move.from) || !isCoordinateInBounds(move.to))
    {
        return false;
    }

    if (!board[move.from.first][move.from.second])
        return false;

    unique_ptr<Piece> &fromPiece = board[from.first][from.second];
    unique_ptr<Piece> &toPiece = board[to.first][to.second];

    // make sure correct color moved:
    if (currentTurn != fromPiece->getColor())
    {
        return false;
    }

    if (fromPiece->getType() == PieceType::Pawn && (move.to.first == 0 || move.to.first == board.size() - 1) && promotion == ' ')
    {
        return false;
    }

    // check if the current colors king is in check
    for (int i = 0; i < board.size(); i++)
    {
        for (int j = 0; j < board[0].size(); j++)
        {
            if (board[i][j] && board[i][j]->getColor() == currentTurn && board[i][j]->getType() == PieceType::King && isTargeted(currentTurn, make_pair(i, j)))
            {   

                // if king is in check, check if the move get's it out of check
                // first perform the move
                unique_ptr<Piece> oldToPiece = toPiece ? toPiece->clone() : nullptr;
                toPiece = nullptr;
                board[to.first][to.second] = fromPiece->clone();
                fromPiece = nullptr;

                // check if king is still in check
                bool result = true;

                // if the piece that moved was a king, check to position
                // if the piece that moved wasn't a king, check i,j
                if(board[to.first][to.second]->getType() == PieceType::King) {
                    if (isTargeted(currentTurn, make_pair(to.first, to.second)))
                    {
                        result = false;
                    }
                }
                else {
                    if (isTargeted(currentTurn, make_pair(i, j)))
                    {
                        result = false;
                    }
                }
                

                // revert changes and return result
                board[from.first][from.second] = board[to.first][to.second]->clone();
                board[to.first][to.second] = oldToPiece ? oldToPiece->clone() : nullptr;
                return result;
            }
        }
    }

    vector<PossibleMove> allMoves = fromPiece->getPossibleMoves(from, board);

    // check if one of the from pieces possible moves - if not, return false
    bool isPossibleMove = false;
    for (int i = 0; i < allMoves.size(); i++)
    {
        if (allMoves[i] == move)
        {
            isPossibleMove = true;
            break;
        }
    }
    if (!isPossibleMove)
        return false;

    // make sure if king is being moved, it is not moving into a check (regardless of whether its capturing a piece or not)
    if (fromPiece->getType() == PieceType::King && isTargeted(fromPiece->getColor(), to))
    {
        return false;
    }

    // categorize as capture, move, or castle
    // if normal move (no capture) - could still be en passant
    if (!toPiece)
    {
        return true;
    }
    else if (toPiece && toPiece->getColor() != fromPiece->getColor())
    { // if capture (both pieces are of different colors)
        if (toPiece && toPiece->getType() == PieceType::King)
        {
            return false;
        }
        return true;
    }
    else if (move.isCastling)
    {
        Color c = fromPiece->getColor();
        // check if there king should not be in check during castle, rook can be targeted, both cannot be targeted after
        return !isTargeted(c, from) && !isTargeted(c, to) && !isTargeted(c, make_pair(from.first, (from.second + to.second) / 2));
    }

    return false;
};

void ChessState::safelyMove(unique_ptr<Piece> &fromPiece, pair<int, int> fromCoords, pair<int, int> toCoords, Color pieceColor, char promotion)
{
    fromPiece->setHasMoved(true);
    board[toCoords.first][toCoords.second].reset();
    if (promotion != ' ')
    {
        PieceType type = PieceTypeConverter::charToPieceType(promotion);
        if (type != PieceType::King && type != PieceType::Pawn)
        {
            board[toCoords.first][toCoords.second] = createPiece(type, pieceColor);
        }
    }
    else
    {
        board[toCoords.first][toCoords.second] = fromPiece->clone();
    }
    board[fromCoords.first][fromCoords.second].reset();
}

Color ChessState::getPlayerTurn()
{
    return currentTurn;
}

void ChessState::playMove(InputMove &inputMove)
{
    std::pair<int, int> fromCoords = rankFileToCoordinates(inputMove.from.first, inputMove.from.second);
    std::pair<int, int> toCoords = rankFileToCoordinates(inputMove.to.first, inputMove.to.second);

    if (!isCoordinateInBounds(fromCoords) || !isCoordinateInBounds(toCoords))
    {
        throw std::runtime_error("provided coordinates are not in bounds");
    }

    PossibleMove possibleMove{fromCoords, toCoords};
    if (!isValidMove(possibleMove, inputMove.promotion))
    {
        throw std::runtime_error("invalid move!!");
    }

    std::unique_ptr<Piece> fromPiece = std::move(board[fromCoords.first][fromCoords.second]);
    safelyMove(fromPiece, fromCoords, toCoords, currentTurn, inputMove.promotion);

    if (fromPiece->getType() == PieceType::King && (fromCoords.first - toCoords.first == 0) && abs(fromCoords.second - toCoords.second) == 2)
    {
        if (fromCoords.second - toCoords.second == 2)
        {
            std::unique_ptr<Piece> rook = std::move(board[toCoords.first][0]);
            pair<int, int> rookFrom{toCoords.first, 0}; // move the rook at bottom left of board, toCoords is the destination of the king, which is also the back rank for white or black
            pair<int, int> rookTo{toCoords.first, toCoords.second + 1};
            safelyMove(rook, rookFrom, rookTo, currentTurn, ' ');
        }
        else if (toCoords.second - fromCoords.second == 2)
        {
            std::unique_ptr<Piece> rook = std::move(board[toCoords.first][board.size() - 1]);
            pair<int, int> rookFrom{toCoords.first, board.size() - 1};
            pair<int, int> rookTo{toCoords.first, toCoords.second - 1};
            safelyMove(rook, rookFrom, rookTo, currentTurn, ' ');
        }
    }

    currentTurn = (currentTurn == Color::WHITE) ? Color::BLACK : Color::WHITE;

    notifyObservers();
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
    int i = board.size() - (int)(rank - '0');
    int j = (int)(file - 'a');
    return std::pair<int, int>{i, j};
}

bool ChessState::placePieceAtPosition(PieceType t, char file, char rank, Color color, bool isSetup)
{
    std::pair<int, int> coords = rankFileToCoordinates(file, rank);
    if (!isCoordinateInBounds(coords))
    {
        return false;
    }
    // add piece to state here
    board[coords.first][coords.second] = createPiece(t, color);

    if (isSetup)
    {
        int rows = board.size();
        if (t == PieceType::Pawn)
        {
            if (color == Color::WHITE)
            {
                if (coords.first == rows - 2)
                    board[coords.first][coords.second]->setHasMoved(false);
                else
                    board[coords.first][coords.second]->setHasMoved(true);
            }
            if (color == Color::BLACK)
            {
                if (coords.first == 1)
                    board[coords.first][coords.second]->setHasMoved(false);
                else
                    board[coords.first][coords.second]->setHasMoved(true);
            }
        }
        else
        {
            // board[coords.first][coords.second]->setHasMoved(true);
        }
    }

    notifyObservers();
    return true;
}

ChessState::ChessState(const ChessState &other)
    : players{other.players}, gameRunning{other.gameRunning}, resign{other.resign}, 
      draw{other.draw}, checkmate{other.checkmate}, winner{other.winner}, currentTurn{currentTurn}
{
    board.resize(other.board.size());

    for (size_t i = 0; i < other.board.size(); i++)
    {
        board[i].resize(other.board[i].size());  // Using resize instead of reserve
        for (size_t j = 0; j < other.board[i].size(); j++)
        {
            board[i][j] = other.board[i][j] ? other.board[i][j]->clone() : nullptr;
        }
    }
}

ChessState::~ChessState() {}

const std::vector<std::vector<std::unique_ptr<Piece>>> &ChessState::getBoard() const
{
    return board;
}

Color ChessState::getWinner()
{
    return winner;
}

int ChessState::getChessBoardEvaluation()
{
    if (checkmate)
    {
        if (winner == Color::BLACK)
        {
            return -99999;
        }
        else
        {
            return 99999;
        }
    }
    int sum = 0;
    for (int i = 0; i < board.size(); i++)
    {
        for (int j = 0; j < board[0].size(); j++)
        {
            if (board[i][j])
            {
                int value = PieceTypeConverter::getPieceAttributes(board[i][j]->getColor(), board[i][j]->getType()).value;
                if (board[i][j]->getColor() == Color::BLACK)
                    sum -= value;
                else
                    sum += value;
            }
        }
    }
    return sum;
}

std::vector<PossibleMove> ChessState::getAllPossibleMoves(Color player)
{
    std::vector<PossibleMove> allMoves;

    for (int i = 0; i < board.size(); i++)
    {
        for (int j = 0; j < board[0].size(); j++)
        {
            if (board[i][j] && board[i][j]->getColor() == player)
            {
                vector<PossibleMove> currMoves = board[i][j]->getPossibleMoves(make_pair(i, j), board);

                vector<PossibleMove> validMoves;
                for (PossibleMove p : currMoves)
                {
                    if (isValidMove(p))
                    {
                        validMoves.push_back(p);
                    }
                }
                allMoves.insert(allMoves.end(), validMoves.begin(), validMoves.end());
            }
        }
    }
    return allMoves;
}

void ChessState::defaultSetup()
{
    for (size_t i = 0; i < board.size(); i++)
    {
        for (size_t j = 0; j < board[0].size(); j++)
        {
            board[i][j] = std::unique_ptr<Piece>(nullptr);
        }
    }
    placePieceAtPosition(PieceType::Rook, 'a', '1', Color::WHITE);
    placePieceAtPosition(PieceType::Knight, 'b', '1', Color::WHITE);
    placePieceAtPosition(PieceType::Bishop, 'c', '1', Color::WHITE);
    placePieceAtPosition(PieceType::Queen, 'd', '1', Color::WHITE);
    placePieceAtPosition(PieceType::King, 'e', '1', Color::WHITE);
    placePieceAtPosition(PieceType::Bishop, 'f', '1', Color::WHITE);
    placePieceAtPosition(PieceType::Knight, 'g', '1', Color::WHITE);
    placePieceAtPosition(PieceType::Rook, 'h', '1', Color::WHITE);
    for (size_t i = 0; i < board[0].size(); i++)
    {
        placePieceAtPosition(PieceType::Pawn, (char)('a' + i), '2', Color::WHITE);
    }

    placePieceAtPosition(PieceType::Rook, 'a', '8', Color::BLACK);
    placePieceAtPosition(PieceType::Knight, 'b', '8', Color::BLACK);
    placePieceAtPosition(PieceType::Bishop, 'c', '8', Color::BLACK);
    placePieceAtPosition(PieceType::Queen, 'd', '8', Color::BLACK);
    placePieceAtPosition(PieceType::King, 'e', '8', Color::BLACK);
    placePieceAtPosition(PieceType::Bishop, 'f', '8', Color::BLACK);
    placePieceAtPosition(PieceType::Knight, 'g', '8', Color::BLACK);
    placePieceAtPosition(PieceType::Rook, 'h', '8', Color::BLACK);
    for (size_t i = 0; i < board[0].size(); i++)
    {
        placePieceAtPosition(PieceType::Pawn, (char)('a' + i), '7', Color::BLACK);
    }
}
