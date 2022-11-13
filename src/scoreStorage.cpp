#include <iostream>
#include <fstream>
#include <vector>
#include "scoreStorage.h"
using namespace std;


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

void saveGame (gameBoard gb) {
    ofstream file;
    file.open("boarddata.txt");

    file << gb.boardSize[0] << endl << gb.boardSize[1] << endl;

    if (file.fail()) {
        cout << "Error in accessing historical gameboard status." << endl;
        exit(1);
    } else {
        for (const auto &e : gb.board) {
            for (const auto &f : e) {
                file << f.value << endl;
            }   
        }
        file.close();
    }
}

void retrieveGame (gameBoard &gb) {
    ifstream file;
    file.open("boarddata.txt");

    int value;
    int rowSize, colSize;
    file >> rowSize >> colSize;
    gb.boardSize[0] = rowSize;
    gb.boardSize[1] = colSize;
    for (int i; i < rowSize; i++) {
        for (int j; j < colSize; j++) {
            file >> gb.board[i][j].value;
        }
    }
    file.close();
}