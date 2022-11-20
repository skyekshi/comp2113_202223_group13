#include <random>
#include <vector>
#include <algorithm>
//#include <bits/stdc++.h>
#include "boardFunction.h"
using namespace std;

void updateBoard (gameBoard &gb) {
    srand(time(0));

    if (!gb.init) {
        for (int i = 0; i < gb.boardSize[0]; i++) {
            vector<Tile> boardArray;
            for (int j = 0; j < gb.boardSize[1]; j++) {
                Tile newTile;
                boardArray.push_back(newTile);
            }
            gb.board.push_back(boardArray);
        }
        int i, j, num;
        i = rand() % gb.boardSize[0];
        j = rand() % gb.boardSize[1];
        num = rand() % 100 > 75 ? 4 : 2;
        gb.board[i][j].value = num;
        addTile(gb);
        gb.init = true;
    } else {
        addTile(gb);
    }  
}

void addTile (gameBoard &gb) {

    vector<vector<int>> freeTiles;
    for (int i = 0; i < gb.boardSize[0]; i++) {
        for (int j = 0; j < gb.boardSize[1]; j++) {
            if (!gb.board[i][j].value) {
                vector<int> empty{i,j};
                freeTiles.push_back(empty);
            }
        }
    }

    srand(time(0));
    
    if (freeTiles.size()) {
        vector<int> freeTileRand = freeTiles[rand() % freeTiles.size()];
        int i = freeTileRand[0];
        int j = freeTileRand[1];
        if (gb.moreTile) {
            if (rand() % 100 > 50) {
                gb.board[i][j].value = rand() % 100 > 75 ? 4 : 2;
            } else {
                gb.board[i][j].value = rand() % 100 > 75 ? 9 : 3;
            }
        } else {
            gb.board[i][j].value = rand() % 100 > 75 ? 4 : 2;
        }   
    } 
    
}

bool canMove (gameBoard gb, Directions d) {

    switch (d) {
        case UP:
            for (int j = 0; j < gb.boardSize[1]; j++) {
                for (int i = 0; i < gb.boardSize[0]; i++) {
                    if (!gb.board[i][j].value && gb.board[i + 1][j].value) {
                        return true;
                    }
                }
            }
            break;
        case DOWN:
            for (int j = 0; j < gb.boardSize[1]; j++) {
                for (int i = 0; i < gb.boardSize[0]; i++) {
                    if (gb.board[i][j].value && !gb.board[i + 1][j].value) {
                        return true;
                    }
                }
            }
            break;
        case LEFT:
            for (int i = 0; i < gb.boardSize[0]; i++) {
                for (int j = 0; j < gb.boardSize[1]; j++) {
                    if (!gb.board[i][j].value && gb.board[i][j + 1].value) {
                        return true;
                    }
                }
            }
            break;
        case RIGHT:
            for (int i = 0; i < gb.boardSize[0]; i++) {
                for (int j = 0; j < gb.boardSize[1]; j++) {
                    if (gb.board[i][j].value && !gb.board[i][j + 1].value) {
                        return true;
                    }
                }
            }
            break;
        default:
            return false;
            break;
    }

    return false;
}

void moveTile (gameBoard &gb, Directions d) {

    vector<int> vectorToMergeUp, vectorToMergeDown, vectorToMergeLeft, vectorToMergeRight, vectorToMergeUp_, vectorToMergeDown_, vectorToMergeLeft_, vectorToMergeRight_;
    int check, pos;

    switch (d) {
// i and j in the vector index might need to be changed as now the two vectors have different length in all four cases (notice that when debugging)
        case UP:
            for (int i = 0; i < gb.boardSize[0]; i++) {
                check = 0;
                for (int j = 0; j < gb.boardSize[1]; j++) {
                    if (!gb.board[i][j].blocked && check == 0) {
                        vectorToMergeUp.push_back(gb.board[i][j].value);
                    } 
                    else if (!gb.board[i][j].blocked && check == 1){
                        vectorToMergeUp_.push_back(gb.board[i][j].value);    
                    }    
                    else {
                        check == 1;
                        break;
                    }
                }
                reverse(vectorToMergeUp.begin(), vectorToMergeUp.end());
                reverse(vectorToMergeUp_.begin(), vectorToMergeUp_.end());
                mergeTile(gb, vectorToMergeUp);
                mergeTile(gb, vectorToMergeUp_);
                reverse(vectorToMergeUp.begin(), vectorToMergeUp.end());
                reverse(vectorToMergeUp_.begin(), vectorToMergeUp_.end());
                check = 0;
                for (int j = 0; j < gb.boardSize[1]; j++) {
                    if (!gb.board[i][j].blocked && check == 0) {
                        gb.board[i][j].value = vectorToMergeUp[j];
                    } 
                    else if (!gb.board[i][j].blocked && check == 1)
                        {
                        gb.board[i][j].value = vectorToMergeUp_[j-pos-1];
                    } 
                    else {
                        pos = j;
                        check = 1;
                        break;
                    }  
                }
            }
            break;

        case DOWN:
            for (int i = 0; i < gb.boardSize[0]; i++) {
                check = 0;
                for (int j = gb.boardSize[1] - 1; j >= 0 ; j--) {
                    if (!gb.board[i][j].blocked && check == 0) {
                        vectorToMergeDown.push_back(gb.board[i][j].value);
                    } 
                    else if (!gb.board[i][j].blocked && check == 1){
                        vectorToMergeDown_.push_back(gb.board[i][j].value);
                    } 
                    else {
                        check = 1;
                        break;
                    }
                }
                reverse(vectorToMergeDown.begin(), vectorToMergeDown.end());
                reverse(vectorToMergeDown_.begin(), vectorToMergeDown_.end());
                mergeTile(gb, vectorToMergeDown);
                mergeTile(gb, vectorToMergeDown_);
                reverse(vectorToMergeDown.begin(), vectorToMergeDown.end());
                reverse(vectorToMergeDown_.begin(), vectorToMergeDown_.end());
                check = 0;
                for (int j = gb.boardSize[1] - 1; j >= 0 ; j--) {
                    if (!gb.board[i][j].blocked && check == 0) {
                        gb.board[i][j].value = vectorToMergeDown[j];
                    } 
                    else if (!gb.board[i][j].blocked && check == 1) {
                        gb.board[i][j].value = vectorToMergeDown_[j];
                    } 
                    else {
                        check = 1;
                        pos = j;
                        break;
                    }  
                }
            }
            break;

        case LEFT:
            for (int j = 0; j < gb.boardSize[1]; j++) {
                check = 0;
                for (int i = 0; i < gb.boardSize[0]; i++) {
                    if (!gb.board[i][j].blocked && check == 0) {
                        vectorToMergeLeft.push_back(gb.board[i][j].value);
                    } 
                    else if (!gb.board[i][j].blocked && check == 1) {
                        vectorToMergeLeft_.push_back(gb.board[i][j].value);
                    } 
                    else {
                        check = 1;
                        break;
                    }
                }
                reverse(vectorToMergeLeft.begin(), vectorToMergeLeft.end());
                reverse(vectorToMergeLeft_.begin(), vectorToMergeLeft_.end());
                mergeTile(gb, vectorToMergeLeft);
                mergeTile(gb, vectorToMergeLeft_);
                reverse(vectorToMergeLeft.begin(), vectorToMergeLeft.end());
                reverse(vectorToMergeLeft_.begin(), vectorToMergeLeft_.end());
                check = 0;
                for (int i = 0; i < gb.boardSize[0]; i++) {
                    if (!gb.board[i][j].blocked && check == 0) {
                        gb.board[i][j].value = vectorToMergeLeft[i];
                    } 
                    else if (!gb.board[i][j].blocked && check == 1) {
                        gb.board[i][j].value = vectorToMergeLeft_[i - pos -1];
                    } 
                    else {
                        check = 1;
                        pos = i;
                        break;
                    } 
                }
            }
            break;

        case RIGHT:
            for (int j = 0; j < gb.boardSize[1]; j++) {
                check = 0;
                for (int i = gb.boardSize[0] - 1; i >= 0 ; i--) {
                    if (!gb.board[i][j].blocked && check = 0) {
                        vectorToMergeRight.push_back(gb.board[i][j].value);
                    } 
                    else if (!gb.board[i][j].blocked && check = 1) {
                        vectorToMergeRight_.push_back(gb.board[i][j].value);
                    } 
                    else {
                        check = 1;
                        break;
                    }
                }
                reverse(vectorToMergeRight.begin(), vectorToMergeRight.end());
                reverse(vectorToMergeRight_.begin(), vectorToMergeRight_.end());
                mergeTile(gb, vectorToMergeRight);
                mergeTile(gb, vectorToMergeRight_);
                reverse(vectorToMergeRight.begin(), vectorToMergeRight.end());
                reverse(vectorToMergeRight_.begin(), vectorToMergeRight_.end());
                check = 0;
                for (int i = gb.boardSize[0] - 1; i >= 0 ; i--) {
                    if (!gb.board[i][j].blocked && check == 0) {
                        gb.board[i][j].value = vectorToMergeRight[i];
                    } 
                    else if (!gb.board[i][j].blocked && check == 1) {
                        gb.board[i][j].value = vectorToMergeRight[i];
                    } 
                    else {
                        check = 1;
                        pos = i;
                        break;
                    }
                }
            }
            break;
        default:
            break;
    }
}

void mergeTile (gameBoard &gb, std::vector<int> &vectorToMerge) {

    const int size = vectorToMerge.size();
    vectorToMerge.erase(remove(vectorToMerge.begin(), vectorToMerge.end(), 0), vectorToMerge.end());
    vectorToMerge.shrink_to_fit();

    bool merged = false;

    for (int i = vectorToMerge.size() - 1; i > 0; i--) {
        if (merged) {
            merged = false;
            if (!gb.superMove) {
                continue;
            }
        } else if (vectorToMerge[i] == vectorToMerge[i - 1]) {
            vectorToMerge[i] *= 2;
            gb.score += vectorToMerge[i - 1];
            gb.largestTile = gb.largestTile > vectorToMerge[i] ? gb.largestTile : vectorToMerge[i];
            vectorToMerge[i - 1] = 0;
            merged = true;
        }
    }

    vectorToMerge.erase(remove(vectorToMerge.begin(), vectorToMerge.end(), 0), vectorToMerge.end());
    vectorToMerge.shrink_to_fit();

    const int sizeafter = vectorToMerge.size();
    for (int i = 0; i < size - sizeafter; i++) {
        vectorToMerge.insert(vectorToMerge.begin(), 0);
    }
}

void blockTile(gameBoard &gb) {
    vector<vector<int>> usedTiles;
    for (int i = 0; i < gb.boardSize[0]; i++) {
        for (int j = 0; j < gb.boardSize[1]; j++) {
            if (gb.board[i][j].value) {
                vector<int> empty{i,j};
                usedTiles.push_back(empty);
            }
        }
    }

    srand(time(0));
    
    if (usedTiles.size()) {
        vector<int> usedTileRand = usedTiles[rand() % usedTiles.size()];
        int i = usedTileRand[0];
        int j = usedTileRand[1];
        gb.board[i][j].blocked = true;
    } 

}

void hasWon (gameBoard &gb) {
    if (gb.largestTile == gb.tar) {
        gb.won = true;
    }
}

void hasLost (gameBoard &gb) {
    for (int i = 0; i < gb.boardSize[0]; i++) {
        for (int j = 0; j < gb.boardSize[1]; j++) {
            if (!gb.board[i][j].value) {
                gb.lost = false;
            }
        }
    }

    for (int i = 0; i < gb.boardSize[0]; i++) {
        for (int j = 0; j < gb.boardSize[1] - 1; j++) {
            if (gb.board[i][j].value == gb.board[i][j + 1].value) {
                gb.lost = false;
            }
        }
    }

    for (int i = 0; i < gb.boardSize[0] - 1; i++) {
        for (int j = 0; j < gb.boardSize[1]; j++) {
            if (gb.board[i][j].value == gb.board[i + 1][j].value) {
                gb.lost = false;
            }
        }
    }
    gb.lost = true;
}


