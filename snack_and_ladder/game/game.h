#pragma once 
#include "../player.h"
#include "../board.h"
#include "../dice.h"
#include <queue>
#include <iostream>
#include <memory>
using namespace std;

class Game{
    private:
    queue<unique_ptr<Player>>playerQueue;
    Board& board;
    Dice& dice;
    public:
    Game(Board& board, Dice& dice):board(board),dice(dice){}

    void addPlayer(unique_ptr<Player> player){
        playerQueue.push(std::move(player));

    }

    bool addJump(int start, int end)
{
    int size=board.getSize();
    int row = start / size;
    int col = start % size;
    Cell& cells=board.getCell(row,col);

    if (cells.getJump() != nullptr)
        return false;

    cells.setJump(
        std::make_unique<Jump>(start, end)
    );

    return true;
}

void addSnake(int start, int end)
{
    if (start <= end)
    {
        std::cout << "Invalid snake.\n";
        return;
    }

    if (!addJump(start, end))
        std::cout << "A jump already exists at cell " << start << '\n';
}

void addLadder(int start, int end)
{
    if (start >= end)
    {
        std::cout << "Invalid ladder.\n";
        return;
    }

    if (!addJump(start, end))
        std::cout << "A jump already exists at cell " << start << '\n';
}
    void startGame(){
        bool noWin=true;
        while(noWin){
    auto player = std::move(playerQueue.front());
    playerQueue.pop();

cout << "\n---------------------------------\n";
cout << player->getPlayerName() << "'s Turn\n";

int diceValue = dice.rollDice();

cout << "Dice Rolled : " << diceValue << endl;

int currPos = player->getPosition() + diceValue;

cout << "Current Position : " << player->getPosition() << endl;

    if(currPos >= board.getSize() * board.getSize())
    {
        currPos = player->getPosition();
    }
    else
    {
        int row = currPos / board.getSize();
        int col = currPos % board.getSize();

        Cell& cell = board.getCell(row, col);

        if(cell.getJump()){
    if(cell.getJump()->getStart() < cell.getJump()->getEnd())
        cout << "Ladder Found! ";
    else
        cout << "Snake Bite! ";

    cout << cell.getJump()->getStart()
         << " -> "
         << cell.getJump()->getEnd()
         << endl;

    currPos = cell.getJump()->getEnd();
}

cout << "New Position : " << currPos << endl;

        player->setPosition(currPos);

        if(currPos == board.getSize() * board.getSize() - 1)
        {
            std::cout << player->getPlayerName() << " wins!\n";
            noWin = false;
        }
    }

    playerQueue.push(std::move(player));
}
    }

};