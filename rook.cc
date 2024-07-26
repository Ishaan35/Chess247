#include "rook.h"

Rook::Rook(PieceType t, int pId) : Piece{t, pId}
{
    // initialize movement here
}

std::unique_ptr<Piece> Rook::clone(){
    return std::make_unique<Rook>(*this);
}