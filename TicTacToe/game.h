#pragma once

#include <iostream>
#include <queue>
#include <vector>

#include "board.h"
#include "player.h"
#include "winning_strategy.h"

using namespace std;

class Game{
private:
    Board* board;
    WinningStrategy* winningStrategy;
    queue<Player*> playerQueue;

public:
    vector<Player*> players;

    Game(Board* b, WinningStrategy* strategy)
        : board(b), winningStrategy(strategy)
    {
    }

    void addPlayer(Player* player)
    {
        players.push_back(player);
        playerQueue.push(player);
    }

    void startGame()
    {
        while (true)
        {
            Player* currentPlayer = playerQueue.front();
            playerQueue.pop();

            int row, col;

            cout << "\n---------------------------------\n";
            cout << currentPlayer->getName() << "'s Turn\n";
            cout << "Enter Row space Column : ";

            cin >> row >> col;

            if (!board->placePiece(row, col, currentPlayer->getPlayerPiece()))
            {
                cout << "Invalid Move! Try Again.\n";

                playerQueue.push(currentPlayer);
                continue;
            }

            board->printBoard();

            if (winningStrategy->checkWinner(
                    *board,
                    row,
                    col,
                    currentPlayer->getPlayerPiece()))
            {
                cout << "\n";
                cout << currentPlayer->getName() << " Wins!!\n";
                return;
            }

            if (board->isBoardFull())
            {
                cout << "\nMatch Tied!\n";
                return;
            }

            playerQueue.push(currentPlayer);
        }
    }

    virtual ~Game() = default;
};