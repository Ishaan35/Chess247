#ifndef PIECE_TYPE_H
#define PIECE_TYPE_H

#include <unordered_map>
#include <string>
#include "../colorEnum.h"

// Define the enum for chess pieces
enum class PieceType
{
    King,
    Queen,
    Bishop,
    Knight,
    Pawn,
    Rook
};

struct PieceEnumAttributes
{
    char character;
    std::string filename;
};

class PieceTypeConverter
{
public:
    static const PieceEnumAttributes &getPieceAttributes(Color color, PieceType pieceType);
    static const PieceType charToPieceType(char piece);
    static const bool PieceTypeConverter::isValidPiece(PieceType p);

private:
    static const std::unordered_map<PieceType, PieceEnumAttributes> playerPieceMappings[2];
    static const std::unordered_map<char, PieceType> characterPieceMappings;
};

#endif
