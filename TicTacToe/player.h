#pragma once 
#include "board_piece/board_piece.h"
#include <string>
using namespace std;

class Player{
    private: 
    string name;
    BoardPiece* boardPiece;
    public:
    Player(string pName, BoardPiece* piece):name(pName),boardPiece(piece){}
    string getName() const{
        return name;
    }
    BoardPiece* getPlayerPiece()const{
        return boardPiece;
    }
    virtual ~Player()=default;
};