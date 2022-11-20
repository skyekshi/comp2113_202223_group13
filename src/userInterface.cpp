#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>
#include "userInterface.h"
#include "boardFunction.h"
using namespace std;

vector<int> getLinuxShape () {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    vector<int> sizePair = {w.ws_col, w.ws_row};
    return sizePair;
}

void printLeftPadding (int width) {
    vector<int> sizePair = getLinuxShape();
    for(int i = 0; i < (sizePair[0]/2) - width/2; i++) cout << " ";
}

void printUpPadding (int height) {
    vector<int> sizePair = getLinuxShape();
    for(int i = 0; i < (sizePair[1]/2) - height/2; i++) cout << endl;
}

void printMenu () {
    system("clear");
    /*vector<string> logo = {
         "----------  ------------  -        --  ----------",
        "|--------|  |---------||  |        ||  |        ||",
        "        ||  |         ||  |        ||  |        ||",
        "        ||  |         ||  |        ||  |        ||",
        "---------|  |         ||  |--------||  |--------||",
        "|---------  |         ||   ---------|  |--------||",
        "||          |         ||           ||  |        ||",
        "||          |         ||           ||  |        ||",
        "|---------| |---------||           ||  |        ||",
        " ----------  -----------            ||   ---------",
    };
    printUpPadding(logo.size() + 4);

    for (int i = 0; i < logo.size(); i++) {
        printLeftPadding(logo[i].size());
        cout << logo[i] << endl;
    }*/



    //print command info
    printUpPadding(4);

    string info1 = "Welcome to 2048!";
    printLeftPadding(info1.size());
    cout << info1 << endl << endl;

    string info2 = "Commands: (N)ew game  (R)esume  (M)supermerging  (T)moretiles ";
    printLeftPadding(info2.size());
    cout << info2 << endl;

    string infomore = "(B)blockonetile  (U)changetarget  (Z)changesize (Q)uit";
    printLeftPadding(infomore.size());
    cout << infomore << endl;
    
}

void printMessage (string msg) {
    system("clear");
    printUpPadding(1);
    printLeftPadding(msg.size());
    cout << msg << endl;
}

void printGamePage (gameBoard gb, int histScore) {
    system("clear");
    
    printUpPadding(17);
    printLeftPadding(32);

    cout << "Current Score: " << gb.score << " Highest Score: " << histScore << endl;
    
    string upper;
    for (int i = 0; i <= gb.boardSize[1]; i++) {
        upper += "--------";
    }
    
    printLeftPadding(upper.size());
    cout << upper << endl;
    
    // Visualize gameboard
    for (int i = 0; i <= gb.boardSize[0]; i++) {
        printLeftPadding(upper.size());
        cout << "|";
        for (int j = 0; j <= gb.boardSize[1]; j++)
            cout << setw(8) << "|";
        cout << endl;

        printLeftPadding(upper.size());
        cout << "|";
        for (int j = 0; j <= gb.boardSize[1]; j++) {
            if (gb.board[i][j].value)
                cout << setw(4) << gb.board[i][j].value << setw(4) << "|";
            else
                cout << setw(8) << "|";
        }
        cout << endl;

        printLeftPadding(upper.size());
        cout << upper << endl;
    }

    //print command info
    string info = "Commands: (W)moveup \t(S)movedown \t(A)moveleft \t(D)moveright \t(Q)uit";
    printLeftPadding(info.size());
    cout << info << endl;
    
}

void operatorGameBoard(gameBoard& gb, char usrInput, vector<char>& nextInput) {
	if (count(nextInput.begin(), nextInput.end(), userInput)) {
		if (userInput == 'n') {
			saveScore(gb.score);
			gb.score = 0;
			gb.largestTile = 0;
			gb.tar = 2048;
			gb.superMove = false;
			gb.moreTile = false;
			gb.init = false;
			gb.boardSize = { 4,4 };
			for (int i = 0; i < gb.boardSize[0]; i++) {
				for (int j = 0; j < gb.boardSize[1]; j++) {
					gb.board[i][j].value = 0;
					gb.board[i][j].blocked = false;
				}
			}
			updateBoard(gb);
			printGamePage(gb, highScore);
			nextInput = { 'q', 'w', 'a', 's', 'd' };
		}
		else if (userInput == 'r') {
			retrieveGame(gb);
			gb.init = true;
			printGamePage(gb, highScore);
			nextInput = { 'q', 'w', 'a', 's', 'd' };
		}
		else if (userInput == 'q') {
			saveScore(gb.score);
			printMessage("See you next time!");
			break;
		}
		else if (userInput == 'm') {
			gb.superMove = true;
			nextInput = { 'n', 'r', 'q', 'm', 't', 'b', 'u', 'z' };
		}
		else if (userInput == 't') {
			gb.moreTile = true;
			nextInput = { 'n', 'r', 'q', 'm', 't', 'b', 'u', 'z' };
		}
		else if (userInput == 'b') {
			blockTile(gb);
			nextInput = { 'n', 'r', 'q', 'm', 't', 'b', 'u', 'z' };
		}
		else if (userInput == 'u') {
			printMessage("Input your desired target value:");
			int target;
			cin >> target;
			gb.tar = target;
			nextInput = { 'n', 'r', 'q', 'm', 't', 'b', 'u', 'z' };
		}
		else if (userInput == 'z') {
			printMessage("Input your desired board size (row, col):");
			int row, col;
			cin >> row >> col;
			gb.boardSize = { row, col };
			nextInput = { 'n', 'r', 'q', 'm', 't', 'b', 'u', 'z' };
		}
		else if (userInput == 'w' || userInput == 'a' || userInput == 's' || userInput == 'd') {
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
				nextInput = { 'q', 'n' };
			}
			else if (gb.won && gb.woncheck) {
				printMessage("You've won! You can either (Q)uit game or start (N)ew game. Otherwise, press wasd to continue.");
				nextInput = { 'q', 'n', 'w', 'a', 's', 'd' };
			}
			else {
				updateBoard(gb);
				printGamePage(gb, highScore);
				nextInput = { 'q', 'w', 'a', 's', 'd' };
			}

			if (gb.won && gb.woncheck) {
				gb.woncheck = false;
			}
		}
	}
}
