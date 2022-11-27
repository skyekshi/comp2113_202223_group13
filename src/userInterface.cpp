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
#include "scoreStorage.h"
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
   
    //print command info
    printUpPadding(7);

    string info1 = "Welcome to 2048!";
    printLeftPadding(info1.size());
    cout << info1;
	printLeftPadding(info1.size());

    string info2 = "Commands: (N)ew game  (R)esume  (Q)uit ";
    printLeftPadding(info2.size());
    cout << info2;
	printLeftPadding(info2.size());

    string infomore = "(M)supermerging  (T)moretiles (U)changetarget  (Z)changesize ";
    printLeftPadding(infomore.size());
    cout << infomore;
	printLeftPadding(infomore.size());
	
	printUpPadding(7);

}

void printMessage (string msg) {
    system("clear");
    printUpPadding(2);
    printLeftPadding(msg.size());
    cout << msg << endl;
	printUpPadding(2);
}

void printMenuAfter () {
    system("clear");
   
    //print command info
    printUpPadding(7);

    string info1 = "Settings successfully changed!";
    printLeftPadding(info1.size());
    cout << info1;
	printLeftPadding(info1.size());

    string info2 = "Commands: (N)ew game  (R)esume  (Q)uit";
    printLeftPadding(info2.size());
    cout << info2;
	printLeftPadding(info2.size());

    string infomore = "(M)supermerging  (T)moretiles  (U)changetarget  (Z)changesize";
    printLeftPadding(infomore.size());
    cout << infomore;
	printLeftPadding(infomore.size());
	
	printUpPadding(7);

}

void printGamePage (gameBoard gb, int histScore) {
    system("clear");
    
    printUpPadding(17);
    printLeftPadding(32);

    cout << "Current Score: " << gb.score << " Highest Score: " << histScore << endl;
    
    string upper;
    for (int i = 0; i < gb.boardSize[1]; i++) {
        upper += "--------";
    }
    
    printLeftPadding(upper.size());
    cout << upper << endl;
    
    // Visualize gameboard
    for (int i = 0; i < gb.boardSize[0]; i++) {
        printLeftPadding(upper.size());
        cout << "|";
        for (int j = 0; j < gb.boardSize[1]; j++)
            cout << setw(8) << "|";
        cout << endl;

        printLeftPadding(upper.size());
        cout << "|";
        for (int j = 0; j < gb.boardSize[1]; j++) {
            if (gb.board[i][j].value > 0)
                cout << setw(4) << gb.board[i][j].value << setw(4) << "|";
            else
                cout << setw(8) << "|";
        }
        cout << endl;

        printLeftPadding(upper.size());
        cout << upper << endl;
    }

    //print command info
    string info = "Commands: (W)moveup  (S)movedown  (A)moveleft  (D)moveright  (Q)uit";
    printLeftPadding(info.size());
    cout << info << endl;
    
}