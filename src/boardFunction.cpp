#include <random>
#include <vector>
#include <algorithm>
//#include <bits/stdc++.h>
#include "boardFunction.h"
using namespace std;

/*void updateBoard (gameBoard &gb) {
    srand(time(0));

    if (!gb.init) {
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
}*/

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
                        gb.board[i][j].value = vectorToMergeUp[j];
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
                reverse(vectorToMergeDown.begin(), vectorToMergeDown.end());
                for (int i = gb.boardSize[0] - 1; i >= 0 ; i--) {
                    if (!gb.board[i][j].blocked) {
                        gb.board[i][j].value = vectorToMergeDown[j];
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
                        gb.board[i][j].value = vectorToMergeLeft[i];
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
                reverse(vectorToMergeRight.begin(), vectorToMergeRight.end());
                for (int j = gb.boardSize[1] - 1; j >= 0 ; j--) {
                    if (!gb.board[i][j].blocked) {
                        gb.board[i][j].value = vectorToMergeRight[i];
                    } else {
                        break;
                    }
                }
                vectorToMergeDown.clear();
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

/*void bonus(gameBoard& gb) {
	srand(time());
	bool flag = rand() % 2;
	int row = rand() % gb.boardSize[0], cal = rand() % gb.boardSize[1];
	int a[4]{ 1,0,-1,0 }, b[4]{ 0,1,0,-1 };
	if (flag) {
		while (gb.board[row][cal] == 0)
		{
			row = rand() % gb.boardSize[0];
			cal = rand() % gb.boardSize[1];
		}
		gb.board[row][cal].value = 0;
	}
	else {
		while (true) {
			while (gb.board[row][cal] == 0)
			{
				row = rand() % gb.boardSize[0];
				cal = rand() % gb.boardSize[1];
			}
			for (int i = 0; i < 4; i++)
			{
				int x = row + a[4], y = cal + b[4];
				if (x > 0 && x < gb.boardSize[0] && y>0 && y < gb.boardSize[1] && gb.board[x][y] == 0)
				{
					gb.board[x][y] = gb.board[row][cal];
					return;
				}
			}
		}
	}
}
void punishment(gameBoard& gb) {
	srand(time());
	bool flag = rand() % 2;
	if (flag) {
		int row = rand() % gb.boardSize[0], cal = rand() % gb.boardSize[1];
		while (gb.board[row][cal] == 0)
		{
			row = rand() % gb.boardSize[0];
			cal = rand() % gb.boardSize[1];
		}
		gb.board[row][cal].value *=4;
	}
	else {
		for (int i = 0; i < 2; i++)
			addTile(gb);
	}
}*/
