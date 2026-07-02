#pragma once
#include "board_piece_type.h"
#include <string>
using namespace std;
class BoardPiece{
    public:
    BoarPieceType pieceType;
    BoardPiece(BoarPieceType type):pieceType(type){}

    BoarPieceType getPieceType() const{
        return pieceType;
    }
    virtual string symbol() const = 0;
    virtual ~BoardPiece()=default;
};