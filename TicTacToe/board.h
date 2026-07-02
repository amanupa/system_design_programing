#pragma once 
#include <vector>
#include <iostream>
#include "board_piece/board_piece.h"
using namespace std;

class Board{
    private:
    int boardSize;
    vector<vector<BoardPiece*>>boardPieces;
    int pieceCount=0;
    public:
    Board(int size):boardSize(size),boardPieces(size,vector<BoardPiece*>(size,nullptr)){}

    bool isOccupied(int row, int col) const {
        if(boardPieces[row][col]==nullptr)return false;
        return true;
    }
    bool isBoardFull() const {
        if(pieceCount==boardSize*boardSize)return true;
        return false;
    }
    bool isValidCell(int row,int col) const{
        return row>=0 &&
           row<boardSize &&
           col>=0 &&
           col<boardSize;
    }
    bool placePiece(int row, int col, BoardPiece* piece) {
        if(isOccupied( row,  col)){
            return false;
        }
        if(!isValidCell(row,col)) return false;
        boardPieces[row][col]=piece;
        pieceCount++;
        return true;
    }
    BoardPiece* getPiece(int row,int col) const{
        return boardPieces[row][col];
    }

    int getSize() const{
        return boardSize;
    }

    void printBoard() const{
        for (int i = 0; i < boardSize; i++){
            for (int j = 0; j < boardSize; j++){
                if (boardPieces[i][j] == nullptr)cout << "- ";
                else
                    cout << boardPieces[i][j]->symbol() << " ";

            // getPieceType() should return 'X' or 'O'
            }

            cout << endl;
        }
    }
    virtual ~Board()=default;
};