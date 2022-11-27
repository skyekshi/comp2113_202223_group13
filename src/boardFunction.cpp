#include <random>
#include <vector>
#include <algorithm>
#include <map>
//#include <bits/stdc++.h>
#include "boardFunction.h"
using namespace std;

/*
Add a random tile at random position
Input: gameboard 
Output: modified gameboard
*/
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

/*
Determine whether the move is legit
Input: gameboard, move direction
Output: modified gameboard
*/
bool canMove (gameBoard gb, Directions d) {

    switch (d) {
        case UP:
            for (int j = 0; j < gb.boardSize[1]; j++) {
                for (int i = 0; i < gb.boardSize[0] - 1; i++) {
                    if (gb.board[i][j].value == 0 && gb.board[i + 1][j].value != 0) {
                        return true;
                    } else if (gb.board[i][j].value != 0 && gb.board[i][j].value == gb.board[i + 1][j].value) {
                        return true;
                    }
                }
            }
            return false;
            break;
        case DOWN:
            for (int j = 0; j < gb.boardSize[1]; j++) {
                for (int i = 0; i < gb.boardSize[0] - 1; i++) {
                    if (gb.board[i][j].value != 0 && gb.board[i + 1][j].value == 0) {
                        return true;
                    } else if (gb.board[i][j].value != 0 && gb.board[i][j].value == gb.board[i + 1][j].value) {
                        return true;
                    }
                }
            }
            return false;
            break;
        case LEFT:
            for (int i = 0; i < gb.boardSize[0]; i++) {
                for (int j = 0; j < gb.boardSize[1] - 1; j++) {
                    if (gb.board[i][j].value == 0 && gb.board[i][j + 1].value != 0) {
                        return true;
                    } else if (gb.board[i][j].value != 0 && gb.board[i][j].value == gb.board[i][j + 1].value) {
                        return true;
                    }
                }
            }
            return false;
            break;
        case RIGHT:
            for (int i = 0; i < gb.boardSize[0]; i++) {
                for (int j = 0; j < gb.boardSize[1] - 1; j++) {
                    if (gb.board[i][j].value != 0 && gb.board[i][j + 1].value == 0) {
                        return true;
                    } else if (gb.board[i][j].value != 0 && gb.board[i][j].value == gb.board[i][j + 1].value) {
                        return true;
                    }
                }
            }
            return false;
            break;
        default:
            return false;
            break;
    }

    return false;
}

/*
Move the gameboard in a certain direction
Input: gameboard, move direction 
Output: modified gameboard
*/
void moveTile (gameBoard &gb, Directions d) {

    vector<int> vectorToMergeUp, vectorToMergeDown, vectorToMergeLeft, vectorToMergeRight;
    int k;

    switch (d) {
        case UP:
            for (int j = 0; j < gb.boardSize[1]; j++) {
                k = gb.boardSize[0];
                for (int i = 0; i < gb.boardSize[0]; i++) {
                    if (gb.board[i][j].blocked) {
                        k = i;
                    } 
                }
                for (int i = 0; i < k; i++) {
                    vectorToMergeUp.push_back(gb.board[i][j].value);
                }

                reverse(vectorToMergeUp.begin(), vectorToMergeUp.end());
                mergeTile(gb, vectorToMergeUp);
                reverse(vectorToMergeUp.begin(), vectorToMergeUp.end());
                for (int i = 0; i < k; i++) {
                        gb.board[i][j].value = vectorToMergeUp[i];
                    }

                vectorToMergeUp.clear();
                for (int i = k + 1; i < gb.boardSize[0]; i++) {
                    vectorToMergeUp.push_back(gb.board[i][j].value);
                }

                reverse(vectorToMergeUp.begin(), vectorToMergeUp.end());
                mergeTile(gb, vectorToMergeUp);
                reverse(vectorToMergeUp.begin(), vectorToMergeUp.end());
                for (int i = k + 1; i < gb.boardSize[0]; i++) {
                        gb.board[i][j].value = vectorToMergeUp[i - k - 1];
                }
                vectorToMergeUp.clear();
                k = gb.boardSize[0];
            }
            break;

        case DOWN:
            for (int j = 0; j < gb.boardSize[1]; j++) {
                k = gb.boardSize[0]; 
                for (int i = gb.boardSize[0] - 1; i >= 0 ; i--) {
                    if (gb.board[i][j].blocked) {
                        k = i;
                    } 
                }

                for (int i = gb.boardSize[0] - 1; i > k; i--) {
                    vectorToMergeDown.push_back(gb.board[i][j].value);
                }

                reverse(vectorToMergeDown.begin(), vectorToMergeDown.end());
                mergeTile(gb, vectorToMergeDown);
               // reverse(vectorToMergeDown.begin(), vectorToMergeDown.end());
                for (int i = gb.boardSize[0] - 1; i > k; i--) {
                        gb.board[i][j].value = vectorToMergeDown[i - k - 1];
                }
                vectorToMergeDown.clear();

                for (int i = k - 1; i >= 0; i--) {
                    vectorToMergeDown.push_back(gb.board[i][j].value);
                }

                reverse(vectorToMergeDown.begin(), vectorToMergeDown.end());
                mergeTile(gb, vectorToMergeDown);
               // reverse(vectorToMergeDown.begin(), vectorToMergeDown.end());
                for (int i = k - 1; i >= 0; i--) {
                        gb.board[i][j].value = vectorToMergeDown[i];
                }
                vectorToMergeDown.clear();
                               
            }
            break;

        case LEFT:
            for (int i = 0; i < gb.boardSize[0]; i++) {
                k = gb.boardSize[1];
                for (int j = 0; j < gb.boardSize[1]; j++) {
                    if (gb.board[i][j].blocked) {
                        k = j;
                    }
                }

                for (int j = 0; j < k; j++) {
                    vectorToMergeLeft.push_back(gb.board[i][j].value);
                }

                reverse(vectorToMergeLeft.begin(), vectorToMergeLeft.end());
                mergeTile(gb, vectorToMergeLeft);
                reverse(vectorToMergeLeft.begin(), vectorToMergeLeft.end());
                for (int j = 0; j < k; j++) {
                    gb.board[i][j].value = vectorToMergeLeft[j];
                }
                vectorToMergeLeft.clear();
                
                for (int j = k + 1; j < gb.boardSize[1]; j++) {
                    vectorToMergeLeft.push_back(gb.board[i][j].value);
                }

                reverse(vectorToMergeLeft.begin(), vectorToMergeLeft.end());
                mergeTile(gb, vectorToMergeLeft);
                reverse(vectorToMergeLeft.begin(), vectorToMergeLeft.end());
                for (int j = k + 1; j < gb.boardSize[1]; j++) {
                    gb.board[i][j].value = vectorToMergeLeft[j - k - 1];
                }
                vectorToMergeLeft.clear();
            }
            break;

        case RIGHT:
            for (int i = 0; i < gb.boardSize[0]; i++) {
                k = gb.boardSize[1];
                for (int j = gb.boardSize[1] - 1; j >= 0 ; j--) {
                    if (gb.board[i][j].blocked) {
                        k = j;
                    }
                }

                for (int j = gb.boardSize[1] - 1; j > k; j--) {
                        vectorToMergeRight.push_back(gb.board[i][j].value);
                }
                reverse(vectorToMergeRight.begin(), vectorToMergeRight.end());
                mergeTile(gb, vectorToMergeRight);
               // reverse(vectorToMergeRight.begin(), vectorToMergeRight.end());
                for (int j = gb.boardSize[1] - 1; j > k; j--) {
                    gb.board[i][j].value = vectorToMergeRight[j - k - 1];
                }
                vectorToMergeRight.clear();

                for (int j = k - 1; j >= 0; j--) {
                        vectorToMergeRight.push_back(gb.board[i][j].value);
                }
                reverse(vectorToMergeRight.begin(), vectorToMergeRight.end());
                mergeTile(gb, vectorToMergeRight);
               // reverse(vectorToMergeRight.begin(), vectorToMergeRight.end());
                for (int j = k - 1; j >= 0; j--) {
                    gb.board[i][j].value = vectorToMergeRight[j];
                }
                vectorToMergeRight.clear();
            }
            break;
        default:
            break;
    }
}

/*
Merge tile for a 1d vector 
Input: gameboard, vector to merge
Output: modified gameboard
*/
void mergeTile (gameBoard &gb, std::vector<int> &vectorToMerge) {

    const int size = vectorToMerge.size();
    vectorToMerge.erase(remove(vectorToMerge.begin(), vectorToMerge.end(), 0), vectorToMerge.end());
    vectorToMerge.shrink_to_fit();

    bool merged = false;

    for (int i = vectorToMerge.size() - 1; i > 0; i--) {
        if (!gb.superMove) {
            if (merged) {
                merged = false;
                continue;
            } else if (vectorToMerge[i] == vectorToMerge[i - 1]) {
                vectorToMerge[i] *= 2;
                gb.score += vectorToMerge[i - 1];
                gb.largestTile = gb.largestTile > vectorToMerge[i] ? gb.largestTile : vectorToMerge[i];
                vectorToMerge[i - 1] = 0;
                merged = true;
            }
        } else {
            int k = i;
            if (k == 5) {
                if (vectorToMerge[i] == vectorToMerge[i - 1] && vectorToMerge[i] == vectorToMerge[i - 2] && vectorToMerge[i] == vectorToMerge[i - 3] && vectorToMerge[i] == vectorToMerge[i - 4] && vectorToMerge[i] == vectorToMerge[i - 5]) {
                    vectorToMerge[i - 5] *= 6;
                    gb.score += 5 * vectorToMerge[i - 1];
                    gb.largestTile = gb.largestTile > vectorToMerge[i] ? gb.largestTile : vectorToMerge[i];
                    vectorToMerge[i - 1] = 0;
                    vectorToMerge[i - 2] = 0;
                    vectorToMerge[i - 3] = 0;
                    vectorToMerge[i - 4] = 0;
                    vectorToMerge[i] = 0;
                } else if (vectorToMerge[i] == vectorToMerge[i - 1] && vectorToMerge[i] == vectorToMerge[i - 2] && vectorToMerge[i] == vectorToMerge[i - 3] && vectorToMerge[i] == vectorToMerge[i - 4]) {
                    vectorToMerge[i - 5] *= 5;
                    gb.score += 4 * vectorToMerge[i - 1];
                    gb.largestTile = gb.largestTile > vectorToMerge[i] ? gb.largestTile : vectorToMerge[i];
                    vectorToMerge[i - 1] = 0;
                    vectorToMerge[i - 2] = 0;
                    vectorToMerge[i - 3] = 0;
                    vectorToMerge[i] = 0;
                } else if (vectorToMerge[i] == vectorToMerge[i - 1] && vectorToMerge[i] == vectorToMerge[i - 2] && vectorToMerge[i] == vectorToMerge[i - 3]) {
                    vectorToMerge[i - 3] *= 4;
                    gb.score += 3 * vectorToMerge[i - 1];
                    gb.largestTile = gb.largestTile > vectorToMerge[i] ? gb.largestTile : vectorToMerge[i];
                    vectorToMerge[i - 1] = 0;
                    vectorToMerge[i - 2] = 0;
                    vectorToMerge[i] = 0;
                } else if (vectorToMerge[i] == vectorToMerge[i - 1] && vectorToMerge[i] == vectorToMerge[i - 2]) {
                    vectorToMerge[i - 2] *= 3;
                    gb.score +=  2 * vectorToMerge[i - 1];
                    gb.largestTile = gb.largestTile > vectorToMerge[i] ? gb.largestTile : vectorToMerge[i];
                    vectorToMerge[i - 1] = 0;
                    vectorToMerge[i] = 0;
                } else if (vectorToMerge[i] == vectorToMerge[i - 1]) {
                    vectorToMerge[i - 1] *= 2;
                    gb.score += vectorToMerge[i - 1];
                    gb.largestTile = gb.largestTile > vectorToMerge[i] ? gb.largestTile : vectorToMerge[i];
                    vectorToMerge[i] = 0;
                }
            } else if (k == 4) {
                if (vectorToMerge[i] == vectorToMerge[i - 1] && vectorToMerge[i] == vectorToMerge[i - 2] && vectorToMerge[i] == vectorToMerge[i - 3] && vectorToMerge[i] == vectorToMerge[i - 4]) {
                    vectorToMerge[i - 5] *= 5;
                    gb.score += 4 * vectorToMerge[i - 1];
                    gb.largestTile = gb.largestTile > vectorToMerge[i] ? gb.largestTile : vectorToMerge[i];
                    vectorToMerge[i - 1] = 0;
                    vectorToMerge[i - 2] = 0;
                    vectorToMerge[i - 3] = 0;
                    vectorToMerge[i] = 0;
                } else if (vectorToMerge[i] == vectorToMerge[i - 1] && vectorToMerge[i] == vectorToMerge[i - 2] && vectorToMerge[i] == vectorToMerge[i - 3]) {
                    vectorToMerge[i - 3] *= 4;
                    gb.score += 3 * vectorToMerge[i - 1];
                    gb.largestTile = gb.largestTile > vectorToMerge[i] ? gb.largestTile : vectorToMerge[i];
                    vectorToMerge[i - 1] = 0;
                    vectorToMerge[i - 2] = 0;
                    vectorToMerge[i] = 0;
                } else if (vectorToMerge[i] == vectorToMerge[i - 1] && vectorToMerge[i] == vectorToMerge[i - 2]) {
                    vectorToMerge[i - 2] *= 3;
                    gb.score +=  2 * vectorToMerge[i - 1];
                    gb.largestTile = gb.largestTile > vectorToMerge[i] ? gb.largestTile : vectorToMerge[i];
                    vectorToMerge[i - 1] = 0;
                    vectorToMerge[i] = 0;
                } else if (vectorToMerge[i] == vectorToMerge[i - 1]) {
                    vectorToMerge[i - 1] *= 2;
                    gb.score += vectorToMerge[i - 1];
                    gb.largestTile = gb.largestTile > vectorToMerge[i] ? gb.largestTile : vectorToMerge[i];
                    vectorToMerge[i] = 0;
                }
            } else if (k == 3) {
                if (vectorToMerge[i] == vectorToMerge[i - 1] && vectorToMerge[i] == vectorToMerge[i - 2] && vectorToMerge[i] == vectorToMerge[i - 3]) {
                    vectorToMerge[i - 3] *= 4;
                    gb.score += 3 * vectorToMerge[i - 1];
                    gb.largestTile = gb.largestTile > vectorToMerge[i] ? gb.largestTile : vectorToMerge[i];
                    vectorToMerge[i - 1] = 0;
                    vectorToMerge[i - 2] = 0;
                    vectorToMerge[i] = 0;
                } else if (vectorToMerge[i] == vectorToMerge[i - 1] && vectorToMerge[i] == vectorToMerge[i - 2]) {
                    vectorToMerge[i - 2] *= 3;
                    gb.score +=  2 * vectorToMerge[i - 1];
                    gb.largestTile = gb.largestTile > vectorToMerge[i] ? gb.largestTile : vectorToMerge[i];
                    vectorToMerge[i - 1] = 0;
                    vectorToMerge[i] = 0;
                } else if (vectorToMerge[i] == vectorToMerge[i - 1]) {
                    vectorToMerge[i - 1] *= 2;
                    gb.score += vectorToMerge[i - 1];
                    gb.largestTile = gb.largestTile > vectorToMerge[i] ? gb.largestTile : vectorToMerge[i];
                    vectorToMerge[i] = 0;
                }
            } else if (k == 2) {
                if (vectorToMerge[i] == vectorToMerge[i - 1] && vectorToMerge[i] == vectorToMerge[i - 2]) {
                    vectorToMerge[i - 2] *= 3;
                    gb.score +=  2 * vectorToMerge[i - 1];
                    gb.largestTile = gb.largestTile > vectorToMerge[i] ? gb.largestTile : vectorToMerge[i];
                    vectorToMerge[i - 1] = 0;
                    vectorToMerge[i] = 0;
                } else if (vectorToMerge[i] == vectorToMerge[i - 1]) {
                    vectorToMerge[i - 1] *= 2;
                    gb.score += vectorToMerge[i - 1];
                    gb.largestTile = gb.largestTile > vectorToMerge[i] ? gb.largestTile : vectorToMerge[i];
                    vectorToMerge[i] = 0;
                }
            } else if (k == 1) {
                if (vectorToMerge[i] == vectorToMerge[i - 1]) {
                vectorToMerge[i - 1] *= 2;
                gb.score += vectorToMerge[i - 1];
                gb.largestTile = gb.largestTile > vectorToMerge[i] ? gb.largestTile : vectorToMerge[i];
                vectorToMerge[i] = 0;
                }
            }
        } 
    }

    vectorToMerge.erase(remove(vectorToMerge.begin(), vectorToMerge.end(), 0), vectorToMerge.end());
    vectorToMerge.shrink_to_fit();

    const int sizeafter = vectorToMerge.size();
    for (int i = 0; i < size - sizeafter; i++) {
        vectorToMerge.insert(vectorToMerge.begin(), 0);
    }
}

/*
Block a random tile
Input: gameboard 
Output: modified gameboard
*/
void blockTile(gameBoard &gb) {
    /*vector<vector<int>> usedTiles;
    for (int i = 0; i < gb.boardSize[0]; i++) {
        for (int j = 0; j < gb.boardSize[1]; j++) {
            if (gb.board[i][j].value) {
                vector<int> empty{i,j};
                usedTiles.push_back(empty);
            }
        }
    }*/

    srand(time(0));
    
    int row = rand() % gb.boardSize[0];
    int col = rand() % gb.boardSize[1];
    gb.board[row][col].blocked = true;
    
    /*if (usedTiles.size()) {
        vector<int> usedTileRand = usedTiles[rand() % usedTiles.size()];
        int i = usedTileRand[0];
        int j = usedTileRand[1];
        gb.board[i][j].blocked = true;
    }*/

}

/*
Check whether the current gameboard status has won
Input: gameboard 
Output: modified gameboard
*/
void hasWon (gameBoard &gb) {
    if (gb.largestTile >= gb.tar) {
        gb.won = true;
    }
}

/*
Check whether the current gameboard status has lost
Input: gameboard 
Output: modified gameboard
*/
void hasLost (gameBoard &gb) {
    for (int i = 0; i < gb.boardSize[0]; i++) {
        for (int j = 0; j < gb.boardSize[1]; j++) {
            if (!gb.board[i][j].value) {
                gb.lost = false;
                return;
            }
        }
    }

    int row, col;
    
    for (int i = 0; i < gb.boardSize[0]; i++) {
        for (int j = 0; j < gb.boardSize[1]; j++) {
            if (gb.board[i][j].blocked) {
                row = i;
                col = j;
                break;
            }
        }
    }


    for (int i = 0; i < gb.boardSize[0]; i++) {
        for (int j = 0; j < gb.boardSize[1] - 1; j++) {
            if (j > col + 1 || j < col - 1) {
                if (gb.board[i][j].value == gb.board[i][j + 1].value) {
                    gb.lost = false;
                    return;
                }
            }
        }
    }

    for (int i = 0; i < gb.boardSize[0] - 1; i++) {
        for (int j = 0; j < gb.boardSize[1]; j++) {
            if (i > row + 1 || i < row - 1) {
                if (gb.board[i][j].value == gb.board[i + 1][j].value) {
                    gb.lost = false;
                    return;
                }
            }
        }
    }
    gb.lost = true;
    return;
}


