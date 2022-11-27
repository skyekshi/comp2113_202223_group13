#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <cstdlib>
#include <vector>
#include <termios.h>
#include <stdio.h>
#include "boardFunction.h"
#include "userInterface.h"
#include "scoreStorage.h"
using namespace std;

//getch linux equivalent, codes from stackoverflow
static struct termios old, current;

/* Initialize new terminal i/o settings */
void initTermios(int echo) 
{
  tcgetattr(0, &old); /* grab old terminal i/o settings */
  current = old; /* make new settings same as old settings */
  current.c_lflag &= ~ICANON; /* disable buffered i/o */
  if (echo) {
      current.c_lflag |= ECHO; /* set echo mode */
  } else {
      current.c_lflag &= ~ECHO; /* set no echo mode */
  }
  tcsetattr(0, TCSANOW, &current); /* use these new terminal i/o settings now */
}

/* Restore old terminal i/o settings */
void resetTermios(void) 
{
  tcsetattr(0, TCSANOW, &old);
}

/* Read 1 character - echo defines echo mode */
char getch_(int echo) 
{
  char ch;
  initTermios(echo);
  ch = getchar();
  resetTermios();
  return ch;
}

/* Read 1 character without echo */
char getch(void) 
{
  return getch_(0);
}

int main () {
    printMenu();
    gameBoard gb;
    for (int i = 0; i < gb.boardSize[0]; i++) {
        vector<Tile> boardArray;
        for (int j = 0; j < gb.boardSize[1]; j++) {
            Tile *newtile = new Tile;
            newtile->value = 0;
            newtile->blocked = false;
            boardArray.push_back(*newtile);
        }
        gb.board.push_back(boardArray);
    }


    int highScore = retrieveScore();

    char userInput;
    vector<char> nextInput = {'n', 'r', 'q', 'm', 't', 'b', 'u', 'z'};

    while (true) {
        userInput = getch();
        tolower(userInput);
        if (count(nextInput.begin(), nextInput.end(), userInput)) {
            if (userInput == 'n') {
                gb.score = 0;
                gb.largestTile = 0;
                //gb.tar = 2048;
                //gb.superMove = false;
                //gb.moreTile = false;
                //gb.init = false;
                //gb.boardSize[0] = 4;
                //gb.boardSize[1] = 4;
                //updateBoard(gb);
                if (gb.lost == true) {
                    gb.board.clear();
                    for (int i = 0; i < gb.boardSize[0]; i++) {
                        vector<Tile> boardArray;
                        for (int j = 0; j < gb.boardSize[1]; j++) {
                            Tile *newtile = new Tile;
                            newtile->value = 0;
                            newtile->blocked = false;
                            boardArray.push_back(*newtile);
                        }
                    gb.board.push_back(boardArray);
                }
                }

                int i, j, num;
                i = rand() % gb.boardSize[0];
                j = rand() % gb.boardSize[1];
                num = rand() % 100 > 75 ? 4 : 2;
                gb.board[i][j].value = num;
                addTile(gb);
                
                printGamePage(gb, highScore);
                gb.won = false;
                gb.woncheck = false;
                gb.lost = false;
                nextInput = {'q', 'w', 'a', 's', 'd'};
            } else if (userInput == 'r') {
                retrieveGame(gb);
                //gb.init = true;
                printGamePage(gb, highScore);
                nextInput = {'q', 'w', 'a', 's', 'd'};
            } else if (userInput == 'q') {
                saveScore(gb.score);
                saveGame(gb);
                printMessage("See you next time!");
                break;
            } else if (userInput == 'm') {
                gb.superMove = true;
                printMenuAfter();
                nextInput = {'n', 'r', 'q', 'm', 't', 'b', 'u', 'z'};
            } else if (userInput == 't') {
                gb.moreTile = true;
                printMenuAfter();
                nextInput = {'n', 'r', 'q', 'm', 't', 'b', 'u', 'z'};
            } /*else if (userInput == 'b') {
                blockTile(gb);
                printMenuAfter();
                nextInput = {'n', 'r', 'q', 'm', 't', 'b', 'u', 'z'};
            }*/ else if (userInput == 'u') {
                printMessage("Input your desired target value:");
                int target;
                cin >> target;
                gb.tar = target;
                printMenuAfter();
                nextInput = {'n', 'r', 'q', 'm', 't', 'b', 'u', 'z'};
            } else if (userInput == 'z') {
                printMessage("Input your desired board size (row, col, 4-6):");
                int row, col;
                cin >> row >> col;
                gb.boardSize[0] = row;
                gb.boardSize[1] = col;
                gb.board.clear();
                for (int i = 0; i < gb.boardSize[0]; i++) {
                    vector<Tile> boardArray;
                    for (int j = 0; j < gb.boardSize[1]; j++) {
                        Tile *newtile = new Tile;
                        newtile->value = 0;
                        newtile->blocked = false;
                        boardArray.push_back(*newtile);
                    }
                    gb.board.push_back(boardArray);
                }
                printMenuAfter();
                nextInput = {'n', 'r', 'q', 'm', 't', 'b', 'u', 'z'};
            } else if (userInput == 'w' || userInput == 'a' || userInput == 's' || userInput == 'd') {
                //gb.init = true;
                switch (userInput) {
                    case 'w':
                        if (canMove(gb, UP)) {
                            moveTile(gb, UP);
                            addTile(gb);
                        }
                        break;
                    case 's':
                        if (canMove(gb, DOWN)) {
                            moveTile(gb, DOWN);
                            addTile(gb);
                        }
                        break;
                    case 'a':
                        if (canMove(gb, LEFT)) {
                            moveTile(gb, LEFT);
                            addTile(gb);
                        }
                        break;
                    case 'd':
                        if (canMove(gb, RIGHT)) {
                            moveTile(gb, RIGHT);
                            addTile(gb);
                        }
                        break;
                    default:
                        break;
                }
                hasWon(gb);
                hasLost(gb);
                if (gb.lost) {
                    printMessage("You've lost! You can either (Q)uit game or start (N)ew game.");
                    nextInput = {'q', 'n'};
                    saveScore(gb.score);
                } else if (gb.won && !gb.woncheck) {
                    gb.woncheck = true;
                    printMessage("You've won! You can either (Q)uit game or start (N)ew game. Otherwise, press wasd to continue.");
                    nextInput = {'q', 'n', 'w', 'a', 's', 'd'};
                    saveScore(gb.score);
                } else {
                    printGamePage(gb, highScore);
                    nextInput = {'q', 'w', 'a', 's', 'd'};
                }
            }
        }
    }
    return 0;
}


    