#include <iostream>
#include <fstream>
#include <vector>
#include "scoreStorage.h"
using namespace std;

/*
Save the current score to a text file
Input: current score
Output: append the integer to the text file
*/
void saveScore(int score)
{
    ofstream file;
    file.open("score.txt", ios::app);

    if (file.fail()) {
        cout << "Error in accessing historical score." << endl;
        exit(1);
    } else {
        file << score << endl;
        file.close();
    }
}

/*
Retrieve the highest historical score
Input: reading the text file
Output: return the highest historical score (int)
*/
int retrieveScore () {
    ifstream file;
    file.open("score.txt");
    int highest_score = 0;
    int history_score = 0;
    while (file >> history_score) {
        if (history_score > highest_score) {
            highest_score = history_score;
        }
    }
    file.close();
    return highest_score;
}

/*
Save the current game statistics to a text file
Input: current gameboard
Output: rewrite the text file
*/
void saveGame (gameBoard gb) {
    ofstream file;
    file.open("boarddata.txt");

    file << gb.boardSize[0] << " " << gb.boardSize[1] << " ";

    if (file.fail()) {
        cout << "Error in accessing historical gameboard status." << endl;
        exit(1);
    } else {
        for (int i = 0; i < gb.boardSize[0]; i++) {
            for (int j = 0; j < gb.boardSize[0]; j++) {
                file << gb.board[i][j].value << " ";
            }
        }
        file.close();
    }
}

/*
Retrieve the latest game status
Input: reading the text file
Output: update the gameboard settings to the last time
*/
void retrieveGame (gameBoard &gb) {
    ifstream file;
    file.open("boarddata.txt");

    int val;
    int rowSize, colSize;
    file >> rowSize >> colSize;
    gb.boardSize[0] = rowSize;
    gb.boardSize[1] = colSize;
    for (int i = 0; i < rowSize; i++) {
        for (int j = 0; j < colSize; j++) {
            file >> val;
            gb.board[i][j].value = val;
        }
    }
    file.close();
}