#include <iostream>
#include <memory>
#include "board.h"
#include "dice.h"
#include "game/game.h"
#include "player.h"

using namespace std;

int main()
{

    Board board(10);

    Dice dice(1);

    Game game(board, dice);

    game.addPlayer(make_unique<Player>(1,0,"Aman"));
    game.addPlayer(make_unique<Player>(2,0,"Badal"));

    game.addSnake(98, 20);
    game.addSnake(92, 48);
    game.addSnake(75, 30);
    game.addSnake(66, 12);
    game.addSnake(54, 18);

    game.addLadder(3, 38);
    game.addLadder(8, 26);
    game.addLadder(21, 82);
    game.addLadder(28, 56);
    game.addLadder(71, 91);

    cout << "=====================================\n";
    cout << "      Snake and Ladder Game\n";
    cout << "=====================================\n";

    game.startGame();

    return 0;
}