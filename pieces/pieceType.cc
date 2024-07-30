#include "pieceType.h"
#include <stdexcept>

// Define the mappings for each player
const std::unordered_map<PieceType, PieceEnumAttributes> PieceTypeConverter::playerPieceMappings[2] = {
    {{PieceType::King, {'K', "./assets/WhiteKing.png", 10000}},
     {PieceType::Queen, {'Q', "./assets/WhiteQueen.png", 9}},
     {PieceType::Bishop, {'B', "./assets/WhiteBishop.png", 3}},
     {PieceType::Knight, {'N', "./assets/WhiteKnight.png", 3}},
     {PieceType::Pawn, {'P', "./assets/WhitePawn.png", 1}},
     {PieceType::Rook, {'R', "./assets/WhiteRook.png", 5}}},
    {{PieceType::King, {'k', "./assets/BlackKing.png", 10000}}, // all of the pieces together cannot sum to 10000, so it is a good value for the king (for computer evaluation)
     {PieceType::Queen, {'q', "./assets/BlackQueen.png", 9}},
     {PieceType::Bishop, {'b', "./assets/BlackBishop.png", 3}},
     {PieceType::Knight, {'n', "./assets/BlackKnight.png", 3}},
     {PieceType::Pawn, {'p', "./assets/BlackPawn.png", 1}},
     {PieceType::Rook, {'r', "./assets/BlackRook.png", 5}}}};

const std::unordered_map<char, PieceType> PieceTypeConverter::characterPieceMappings = {
    {'K', PieceType::King},
    {'Q', PieceType::Queen},
    {'B', PieceType::Bishop},
    {'N', PieceType::Knight},
    {'P', PieceType::Pawn},
    {'R', PieceType::Rook},
    {'k', PieceType::King},
    {'q', PieceType::Queen},
    {'b', PieceType::Bishop},
    {'n', PieceType::Knight},
    {'p', PieceType::Pawn},
    {'r', PieceType::Rook}};

const PieceEnumAttributes &PieceTypeConverter::getPieceAttributes(Color playerColor, PieceType pieceType)
{
    return playerPieceMappings[playerColor].at(pieceType);
}
const PieceType PieceTypeConverter::charToPieceType(char piece)
{
    return characterPieceMappings.at(piece);
}

bool PieceTypeConverter::isValidPiece(PieceType p)
{
    return playerPieceMappings[0].count(p) > 0;
}