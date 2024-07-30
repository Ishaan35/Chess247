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
    // if(isTargeted(currentTurn, )){
    //     return false;
    // }

    // check if King is in check aboves

    int rows = board.size();
    int cols = board[0].size();
    for (size_t i=0; i < board.size(); i++){
        for (size_t j=0; j < board[i].size(); j++){
            if (board[i][j] && currentTurn == board[i][j]->getColor()){
                pair<int, int> position{i,j};
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

};

bool ChessState::isValidMove(PossibleMove possibleMove)
{
    // get from and to pairs from possible moves
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

    std::unique_ptr<Piece> fromPiece = std::move(board[fromCoords.first][fromCoords.second]);

    board[toCoords.first][toCoords.second].reset();

    // rework below code to do promotions from terminal input, which will return an inputMove which has an isPromotion field
    if(fromPiece->getType() == PieceType::Pawn && (toCoords.first == 0) || (toCoords.first == board.size() - 1)){
        if (auto lockedPtr = inputSource.lock())
        {
            PieceType type = lockedPtr->getPromotion();
            std::unique_ptr<Piece> newPiece = createPiece(type, inputMove.pieceColor);
            board[toCoords.first][toCoords.second] = std::move(newPiece);
        }
    }

    else{
        board[toCoords.first][toCoords.second] = std::move(fromPiece);
    }
    board[fromCoords.first][fromCoords.second].reset();
};

ChessState::ChessState(const std::vector<std::weak_ptr<Player>> &players, weak_ptr<InputSource> input, int rows, int columns) : inputSource{input}, players{players}, board(rows) // r x c grid all nullptr by default
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