#pragma once 
#include "cell.h"
#include <vector>
#include<iostream>
using namespace std;

class Board{
    private:
    vector<vector<Cell>>cells;
    int size;
    public:
    Board(int size) : size(size)
{
    cells.resize(size);

    for (auto &row : cells)
        row.resize(size);
}
    Cell& getCell(int row, int col){
        return cells[row][col];
    }
    int getSize()const{
        return size;
    }

    virtual ~Board()=default;
};