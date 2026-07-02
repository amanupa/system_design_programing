#pragma once
#include "winning_strategy.h"
#include "board.h"
#include "board_piece/board_piece.h"

class TicTacToeWinningStrategy : public WinningStrategy{
public:
    bool checkWinner(const Board& board,int row,int col,BoardPiece* piece) override{
         int n = board.getSize();

        bool win = true;
        
        //row check
         for(int j = 0; j < n; j++){
            if(board.getPiece(row, j) != piece){
               win = false;
               break;
            }
        }

        if(win)return true;

        win = true;

        for(int i = 0; i < n; i++){
            if(board.getPiece(i, col) != piece){
                win = false;
                break;
            }
        }

        if(win)return true;

        if(row == col){
            win = true;

        for(int i = 0; i < n; i++)
        {
            if(board.getPiece(i, i) != piece)
            {
                win = false;
                break;
            }
        }

        if(win)
            return true;
    }

   

    if(row + col == n - 1)
    {
        win = true;

        for(int i = 0; i < n; i++)
        {
            if(board.getPiece(i, n - i - 1) != piece)
            {
                win = false;
                break;
            }
        }

        if(win)
            return true;
    }

    return false;


    }
};