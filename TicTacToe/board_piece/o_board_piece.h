#pragma once 
#include "board_piece.h"
#include "board_piece_type.h"
#include <string>
using namespace std;


class OboardPiece : public BoardPiece{
    public:
    OboardPiece():BoardPiece(BoarPieceType::O){}
    string symbol() const override{
        return "O";
    }
    virtual ~OboardPiece()=default;
};