#include "boardFunction.h"
#include "userInterface.h"
#include "scoreStorage.h"
#include <stdio.h>
#include <curses.h>
#include <iostream>
using namespace std;


int main () {
    printMenu();
    gameBoard gb;
    int highScore = retrieveScore();

    char userInput;
    vector<char> nextInput = {'n', 'r', 'q', 'm', 't', 'b', 'u', 'z'};
    initscr();

    while (true) {
        userInput = getch();
        tolower(userInput);
        if (count(nextInput.begin(), nextInput.end(), userInput)) {
            if (userInput == 'n') {
                saveScore(gb.score);
                gb.score = 0;
                gb.largestTile = 0;
                gb.tar = 2048;
                gb.superMove = false;
                gb.moreTile = false;
                gb.init = false;
                gb.boardSize = {4,4};
                for (int i = 0; i < gb.boardSize[0]; i++) {
                    for (int j = 0; j < gb.boardSize[1]; j++) {
                        gb.board[i][j].value = 0;
                        gb.board[i][j].blocked = false;
                    }
                }
                updateBoard(gb);
                printGamePage(gb, highScore);
                nextInput = {'q', 'w', 'a', 's', 'd'};
            } else if (userInput == 'r') {
                retrieveGame(gb);
                gb.init = true;
                printGamePage(gb, highScore);
                nextInput = {'q', 'w', 'a', 's', 'd'};
            } else if (userInput == 'q') {
                saveScore(gb.score);
                printMessage("See you next time!");
                break;
            } else if (userInput == 'm') {
                gb.superMove = true;
                nextInput = {'n', 'r', 'q', 'm', 't', 'b', 'u', 'z'};
            } else if (userInput == 't') {
                gb.moreTile = true;
                nextInput = {'n', 'r', 'q', 'm', 't', 'b', 'u', 'z'};
            } else if (userInput == 'b') {
                blockTile(gb);
                nextInput = {'n', 'r', 'q', 'm', 't', 'b', 'u', 'z'};
            } else if (userInput == 'u') {
                printMessage("Input your desired target value:");
                int target;
                cin >> target;
                gb.tar = target;
                nextInput = {'n', 'r', 'q', 'm', 't', 'b', 'u', 'z'};
            } else if (userInput == 'z') {
                printMessage("Input your desired board size (row, col):");
                int row, col;
                cin >> row >> col;
                gb.boardSize = {row, col};
                nextInput = {'n', 'r', 'q', 'm', 't', 'b', 'u', 'z'};
            } else if (userInput == 'w' || userInput == 'a' || userInput == 's' || userInput == 'd') {
                gb.init = true;
                switch (userInput) {
                    case 'w':
                        if (canMove(gb, UP)) {
                            moveTile(gb, UP);
                        }
                        break;
                    case 's':
                        if (canMove(gb, DOWN)) {
                            moveTile(gb, DOWN);
                        }
                        break;
                    case 'a':
                        if (canMove(gb, LEFT)) {
                            moveTile(gb, LEFT);
                        }
                        break;
                    case 'd':
                        if (canMove(gb, RIGHT)) {
                            moveTile(gb, RIGHT);
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
                } else if (gb.won && gb.woncheck) {
                    printMessage("You've won! You can either (Q)uit game or start (N)ew game. Otherwise, press wasd to continue.");
                    nextInput = {'q', 'n', 'w', 'a', 's', 'd'};
                } else {
                    updateBoard(gb);
                    printGamePage(gb, highScore);
                    nextInput = {'q', 'w', 'a', 's', 'd'};
                }

                if (gb.won && gb.woncheck) {
                    gb.woncheck = false;
                }
            }
        }
    }
    return 0;
}


    