#include "game.h"
#include "board.h"
#include "winning_strategy.h"
#include "board_piece/x_board_piece.h"
#include "board_piece/o_board_piece.h"
#include "tic_tac_toe_winning_strategy.h"
using namespace std;
#include <string>
#include <iostream>
int main(){
    int n;
    string player1;
    string player2;
    cout<<"Enter the size of board: "<<endl;
    cin>>n;
    int count =0;
    while(n<3||n>9){
        count++;
        if(count>=3){
            cout<<"You reach the limit of input, restart the game."<<endl;
            return 0;
        }
        cout<<"Enter the valid size between 3 to 9"<<endl;
        cin>>n;
    }
    Board board(n);
    cout<<"Enter the first player name: "<<endl;
    cin>>player1;
    cout<<"Enter the second player name: "<<endl;
    cin>>player2;

    WinningStrategy* strategy = new TicTacToeWinningStrategy();

    Game game(&board, strategy);

    game.addPlayer(new Player(player1, new XboardPiece()));
    game.addPlayer(new Player(player2, new OboardPiece()));

    game.startGame();
    return 0;
}