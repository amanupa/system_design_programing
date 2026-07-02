#pragma once 
#include <vector>
#include <iostream>
#include "board.h"
#include "board_piece/board_piece.h"
using namespace std;


class WinningStrategy
{
public:
    virtual bool checkWinner(
        const Board& board,
        int row,
        int col,
        BoardPiece* piece) = 0;

    virtual ~WinningStrategy() = default;
};