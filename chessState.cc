#include "chessState.h"
#include "./pieces/pieceFactory.h"

using namespace std;

void ChessState::setIsDefaultSetup(bool val){
    isDefaultSetup = val;
}  

void ChessState::setWinner(Color winnerColor)
{
    winner = winnerColor;
}

void ChessState::setGameRunning(bool val)
{
    isGameRunning = val;
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
    return true;
}

bool ChessState::isTargeted(Color color, pair<int, int> position){
    Color oppositeColor = (color == Color::BLACK) ? Color::WHITE : Color::BLACK;
    int row = position.first;
    int col = position.second;
    for (int i=0; i<board.size(); i++){
        for (int j=0; j<board[i].size(); j++){
            if (board[i][j] && board[i][j]->getColor() == oppositeColor){
                if(i == row && j == col) return true; // opponent's piece is right on top of the given position, our convention is that it's targetted
                pair<int, int> opponent{i,j};
                vector<PossibleMove> possibleMoves = board[i][j]->getPossibleMoves(opponent, board);
                for (size_t k=0; k < possibleMoves.size(); k++){
                    if(possibleMoves[k].to.first == row && possibleMoves[k].to.second == col && isValidMove(possibleMoves[k])){ // the opponent's piece can reach the given target
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

bool ChessState::isDraw() {
    int rows = board.size();
    int cols = board[0].size();
    for (size_t i=0; i < board.size(); i++){
        for (size_t j=0; j < board[i].size(); j++){
            if (board[i][j] && currentTurn == board[i][j]->getColor()){
                pair<int, int> position{i,j};
                if(board[i][j]->getType() == PieceType::King && isTargeted(currentTurn, position)){
                    return false;
                }
                vector<PossibleMove> possibleMoves = board[i][j]->getPossibleMoves(position, board);
                for (size_t k=0; k < possibleMoves.size(); k++){
                    if (isValidMove(possibleMoves[0])){
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

bool ChessState::isCheckmate() {
    // check if other king is in checkmate
    Color other = (currentTurn == Color::WHITE) ? Color::BLACK : Color::WHITE;
    for(size_t i=0; i<board.size(); i++){
        for (size_t j=0; j<board[i].size(); j++){
            if (board[i][j]->getType() == PieceType::King && board[i][j]->getColor() == other){
                pair<int, int> kingPos{i,j};
                if (!isTargeted(other, kingPos)) return false; // not checkmate if not in check
                vector<PossibleMove> possibleMoves = board[i][j]->getPossibleMoves(kingPos, board);
                for (size_t k=0; k<possibleMoves.size(); k++){
                    if(isValidMove(possibleMoves[k])){
                        return false;
                    }
                }
                return true;
            }
        }
    }
};

bool ChessState::isValidMove(PossibleMove move)
{
    // coordinates in bound
    pair<int, int> from = move.from;
    pair<int, int> to = move.to;
    if (!isCoordinateInBounds(move.from) || !isCoordinateInBounds(move.to)){
        return false;
    }

    unique_ptr<Piece>& fromPiece = board[from.first][from.second];
    unique_ptr<Piece>& toPiece = board[to.first][to.second];

    // make sure correct color moved:
    if(!currentTurn == fromPiece->getColor()) {
        return false;
    }

    // check if the current colors king is in check
    for(int i = 0;i < board.size(); i++) {
        for(int j = 0;j < board[0].size(); j++) {
            if(board[i][j]->getColor() == currentTurn && board[i][j]->getType() == PieceType::King && isTargeted(currentTurn, make_pair(i, j))) {
                
                // if king is in check, check if the move get's it out of check

                // first perform the move
                unique_ptr<Piece> oldToPiece = toPiece->clone();
                toPiece = nullptr;
                board[to.first][to.second] = fromPiece->clone();
                fromPiece = nullptr;

                // check if king is still in check
                bool result = true;
                if(isTargeted(currentTurn, make_pair(i, j))) {
                    result = false;
                }

                // revert changes and return result
                board[from.first][from.second] = fromPiece->clone();
                board[to.first][to.second] = oldToPiece->clone();
            }
        }
    }

    vector<PossibleMove> allMoves = fromPiece->getPossibleMoves(from, board);
    
    // check if one of the from pieces possible moves - if not, return false
    bool isPossibleMove = false;
    for(int i = 0; i < allMoves.size(); i++) {
        if(allMoves[i] == move) {
            isPossibleMove = true;
            break;
        }
    }
    if(!isPossibleMove) return false;

    // categorize as capture, move, or castle
    // if normal move (no capture) - could still be en passant
    if(!toPiece) {
        // if King is being moved, make sure not moving into check
        if(fromPiece->getType() == PieceType::King && isTargeted(fromPiece->getColor(), to)) {
            return false;
        }
    }
    else if(toPiece->getColor() != fromPiece->getColor()) { // if capture (both pieces are of different colors)
        if(toPiece->getType() == PieceType::King) {
            return false;
        }
        return true;
    }
    else if(move.isCastling) {
        Color c = fromPiece->getColor();
        // check if there king should not be in check during castle, rook can be targeted, both cannot be targeted after
        return !isTargeted(c, from) && !isTargeted(c, to) && !isTargeted(c, make_pair(from.first, (from.second + to.second)/2));
    }

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
    
    PossibleMove possibleMove{fromCoords, toCoords};
    if (!isValidMove(possibleMove)){
        throw std::runtime_error("invalid move!!");
    }

    if(!board[fromCoords.first][fromCoords.second]->hasMoved()){
        board[fromCoords.first][fromCoords.second]->setHasMoved(true);
    }

    std::unique_ptr<Piece> fromPiece = std::move(board[fromCoords.first][fromCoords.second]);

    board[toCoords.first][toCoords.second].reset();

    if(inputMove.promotion != ' '){
        PieceType type = PieceTypeConverter::charToPieceType(inputMove.promotion);
        if (type != PieceType::King && type != PieceType::Pawn){
            std::unique_ptr<Piece> newPiece = createPiece(type, inputMove.pieceColor);
            board[toCoords.first][toCoords.second] = std::move(newPiece);
        }
    }
    else{
        board[toCoords.first][toCoords.second] = std::move(fromPiece);
    }
    board[fromCoords.first][fromCoords.second].reset();
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

ChessState::ChessState(const ChessState &other) : players{other.players}, isGameRunning{other.isGameRunning}, resign{other.resign}, draw{other.draw}, checkmate{other.checkmate}, winner{other.winner}
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