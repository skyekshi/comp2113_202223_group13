#include <random>
#include <vector>
#include <algorithm>
//#include <bits/stdc++.h>
#include "boardFunction.h"
using namespace std;

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

void moveTile (gameBoard &gb, Directions d) {

    vector<int> vectorToMergeUp, vectorToMergeDown, vectorToMergeLeft, vectorToMergeRight;

    switch (d) {
        case UP:
            for (int j = 0; j < gb.boardSize[1]; j++) {
                for (int i = 0; i < gb.boardSize[0]; i++) {
                    if (!gb.board[i][j].blocked) {
                        vectorToMergeUp.push_back(gb.board[i][j].value);
                    } else {
                        break;
                    }
                }
                reverse(vectorToMergeUp.begin(), vectorToMergeUp.end());
                mergeTile(gb, vectorToMergeUp);
                reverse(vectorToMergeUp.begin(), vectorToMergeUp.end());
                for (int i = 0; i < gb.boardSize[0]; i++) {
                    if (!gb.board[i][j].blocked) {
                        gb.board[i][j].value = vectorToMergeUp[i];
                    } else {
                        break;
                    }  
                }
                vectorToMergeUp.clear();
            }
            break;

        case DOWN:
            for (int j = 0; j < gb.boardSize[1]; j++) {
                for (int i = gb.boardSize[0] - 1; i >= 0 ; i--) {
                    if (!gb.board[i][j].blocked) {
                        vectorToMergeDown.push_back(gb.board[i][j].value);
                    } else {
                        break;
                    }
                }
                reverse(vectorToMergeDown.begin(), vectorToMergeDown.end());
                mergeTile(gb, vectorToMergeDown);
               // reverse(vectorToMergeDown.begin(), vectorToMergeDown.end());
                for (int i = gb.boardSize[0] - 1; i >= 0 ; i--) {
                    if (!gb.board[i][j].blocked) {
                        gb.board[i][j].value = vectorToMergeDown[i];
                    } else {
                        break;
                    }  
                }
                vectorToMergeDown.clear();
            }
            break;

        case LEFT:
            for (int i = 0; i < gb.boardSize[0]; i++) {
                for (int j = 0; j < gb.boardSize[1]; j++) {
                    if (!gb.board[i][j].blocked) {
                        vectorToMergeLeft.push_back(gb.board[i][j].value);
                    } else {
                        break;
                    }
                }
                reverse(vectorToMergeLeft.begin(), vectorToMergeLeft.end());
                mergeTile(gb, vectorToMergeLeft);
                reverse(vectorToMergeLeft.begin(), vectorToMergeLeft.end());
                for (int j = 0; j < gb.boardSize[1]; j++) {
                    if (!gb.board[i][j].blocked) {
                        gb.board[i][j].value = vectorToMergeLeft[j];
                    } else {
                        break;
                    } 
                }
                vectorToMergeLeft.clear();
            }
            break;

        case RIGHT:
            for (int i = 0; i < gb.boardSize[0]; i++) {
                for (int j = gb.boardSize[1] - 1; j >= 0 ; j--) {
                    if (!gb.board[i][j].blocked) {
                        vectorToMergeRight.push_back(gb.board[i][j].value);
                    } else {
                        break;
                    }
                }
                reverse(vectorToMergeRight.begin(), vectorToMergeRight.end());
                mergeTile(gb, vectorToMergeRight);
               // reverse(vectorToMergeRight.begin(), vectorToMergeRight.end());
                for (int j = gb.boardSize[1] - 1; j >= 0 ; j--) {
                    if (!gb.board[i][j].blocked) {
                        gb.board[i][j].value = vectorToMergeRight[j];
                    } else {
                        break;
                    }
                }
                vectorToMergeRight.clear();
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
                return;
            }
        }
    }

    for (int i = 0; i < gb.boardSize[0]; i++) {
        for (int j = 0; j < gb.boardSize[1] - 1; j++) {
            if (gb.board[i][j].value == gb.board[i][j + 1].value) {
                gb.lost = false;
                return;
            }
        }
    }

    for (int i = 0; i < gb.boardSize[0] - 1; i++) {
        for (int j = 0; j < gb.boardSize[1]; j++) {
            if (gb.board[i][j].value == gb.board[i + 1][j].value) {
                gb.lost = false;
                return;
            }
        }
    }
    gb.lost = true;
}


