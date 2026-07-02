#pragma once 
#include "board_piece.h"
#include "board_piece_type.h"
#include <string>
using namespace std;

class XboardPiece : public BoardPiece{
    public:
    XboardPiece():BoardPiece(BoarPieceType::X){}
    string symbol() const override{
        return "X";
    }
    virtual ~XboardPiece()=default;
};