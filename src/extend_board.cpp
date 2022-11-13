#include<iostream>
#include<iomanip>
#include<string>
#include<ctime>
using namespace std;

// The function to extend the game board


//check the largest value after each move. plan: 128 and 512- add a row, 256 and 1024-add a column
// change the boardsize based on the rules
// Does gb.board'size automatically increases?
void extension(gameBoard  &gb)
{
	int lv = gb.largestTile;
	if (lv == 128 || lv == 512)
	{
		gb.boardsize[0]++;
	}

	else if (lv == 256 || lv == 1024)
	{
		gb.boardsize[1]++;
	}

}

