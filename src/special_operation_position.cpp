#include<iostream>
#include<ctime>
#include<string>
#include<tuple>
#include<vector>
#include<cstdlib>
#include<cmath>
#include boardFunction.h
using namespace std;

srand(time(0))

void special_operation_position(gameBoard &gb)
{
	//Decide when to get a random negative sign
	if (rand()%5 == 0)
	{
		int i,j;
		int num = 0;
		//use a constraint to avoid no 2 in the board.
		while (num < 10)
		{
			int i = rand() % gb.boardsize[0];
			int j = rand() % gb.boardsize[1];
			//only generate -2 in the board(can be harder)
			if (gb.board[i][j] == 2){
				gb.board[i][j] = -1 * gb.board[i][j];}
			num ++;
		}
	}

}
