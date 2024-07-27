#include "pieceType.h"
#include <stdexcept>

// Define the mappings for each player
const std::unordered_map<PieceType, PieceEnumAttributes> PieceTypeConverter::playerPieceMappings[2] = {
    {{PieceType::King, {'K', "WhiteKing.png"}},
     {PieceType::Queen, {'Q', "WhiteQueen.png"}},
     {PieceType::Bishop, {'B', "WhiteBishop.png"}},
     {PieceType::Knight, {'N', "WhiteKnight.png"}},
     {PieceType::Pawn, {'P', "WhitePawn.png"}},
     {PieceType::Rook, {'R', "WhiteRook.png"}}},
    {{PieceType::King, {'k', "BlackKing.png"}},
     {PieceType::Queen, {'q', "BlackQueen.png"}},
     {PieceType::Bishop, {'b', "BlackBishop.png"}},
     {PieceType::Knight, {'n', "BlackKnight.png"}},
     {PieceType::Pawn, {'p', "BlackPawn.png"}},
     {PieceType::Rook, {'r', "BlackRook.png"}}}};

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

const PieceEnumAttributes &PieceTypeConverter::getPieceAttributes(int playerIndex, PieceType pieceType)
{
    if (playerIndex < 0 || playerIndex >= 2)
        throw std::out_of_range("Invalid player index");
    return playerPieceMappings[playerIndex].at(pieceType);
}
const PieceType PieceTypeConverter::charToPieceType(char piece){
    return characterPieceMappings.at(piece);
}
