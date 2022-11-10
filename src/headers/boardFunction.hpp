#ifndef BOARDFUNCTION_H
#define BOARDFUNCTION_H

#include <tuple>
#include <vector>
#include <cstdlib>
#include <time.h>
#include <stdio.h>
#include <conio.h>

class Tile {
    public:
        long value;
        bool blocked;
        Tile(): value(0), blocked(false) {}  
};

enum Directions {UP, DOWN, LEFT, RIGHT};

class gameBoard {
    private:
        bool moved;
        int score;
        int largestTile;
        long moveCount;
        std::vector<int> boardSize;
        std::vector<std::vector<Tile>> board;

        void initializeBoard();
        void getFreeTiles(std::vector<std::vector<int>> &freeTiles);
        bool addTile();
        void userInput();
        bool canMove(Directions d);
        void moveTile(Directions d);
        void move(int, int, int, int);
        bool hasWon(int tar);
        bool hasLost();
        void saveScore();

    public:
        gameBoard(): won(false), score(0), largestTile(2), moveCount(-2), boardSize({4,4}), boardFull(false) {}
        void startGame();
};

void gameBoard::initializeBoard () {
    for (int i = 0; i < boardSize[0]; i++) {
        std::vector<Tile> boardArray;
        for (int j = 0; j < boardSize[1]; j++) {
            Tile newTile;
            boardArray.push_back(newTile);
        }
        board.push_back(boardArray);
    }
}

void gameBoard::getFreeTiles(std::vector<std::vector<int>> &freeTiles) {
    for (int i = 0; i < boardSize[0]; i++) {
        for (int j = 0; j < boardSize[1]; j++) {
            if (!board[i][j].value) {
                std::vector<int> empty{i,j};
                freeTiles.push_back(empty);
            }
        }
    }
}

bool gameBoard::addTile (int prob) {
    
    if (hasLost) return true;

    std::vector<std::vector<int>> freeTiles;

    srand(time(0));
    
    std::vector<int> freeTileRand = freeTiles[rand() % freeTiles.size()];
    int i = freeTileRand[0];
    int j = freeTileRand[1];
    board[i][j].value = rand() % 100 > prob ? 4 : 2;

    moveCount++;
    moved = true;

    return canMove(UP) || canMove(DOWN) || canMove(LEFT) || canMove(RIGHT);
}

void userInput() {

    moved = false;

    char c;

    c = getch();

    switch (toupper(c)) {
        case "W":
            if (canMove(UP)) {
                moveTile(UP);
            }
            break;
        case "S":
            if (canMove(DOWN)) {
                moveTile(DOWN);
            }
            break;
        case "A":
            if (canMove(LEFT)) {
                moveTile(LEFT);
            }
            break;
        case "D":
            if (canMove(RIGHT)) {
                moveTile(RIGHT);
            }
            break;
        default:
            break;
    }
}

bool gameBoard::canMove(Directions d) {

    switch (d) {
        case UP:
            for (int j = 0; j < boardSize; j++) {
                for (int i = 0; i < boardSize; i++) {
                    if (!board[i][j].value && board[i + 1][j].value) {
                        return true;
                    }
                }
            }
            break;
        case DOWN:
            for (int j = 0; j < boardSize; j++) {
                for (int i = 0; i < boardSize; i++) {
                    if (board[i][j].value && !board[i + 1][j].value) {
                        return true;
                    }
                }
            }
            break;
        case LEFT:
            for (int i = 0; i < boardSize; i++) {
                for (int j = 0; j < boardSize; j++) {
                    if (!board[i][j].value && board[i][j + 1].value) {
                        return true;
                    }
                }
            }
            break;
        case RIGHT:
            for (int i = 0; i < boardSize; i++) {
                for (int j = 0; j < boardSize; j++) {
                    if (board[i][j].value && !board[i][j + 1].value) {
                        return true;
                    }
                }
            }
            break;
        default:
            return false;
            break;
    }
}

void gameBoard::moveTile (Directions d) {

    switch (d) {
        case UP:
            for (int j = 0; j < boardSize; j++) {
                int i = 1;
                while (i < boardSize) {
                    move(i, j, -1, 0);
                }
                i++;
            }
            break;
        case DOWN:
            for (int j = 0; j < boardSize; j++) {
                int i = boardSize - 2;
                while (i >= 0) {
                    move(i, j, 1, 0);
                }
                i--;
            }
            break;
        case LEFT:
            for (int i = 0; i < boardSize; i++) {
                int j = 1;
                while (j < boardSize) {
                    move(i, j, 0, -1);
                }
                j++;
            }
            break;
        case RIGHT:
            for (int i = 0; i < boardSize; i++) {
                int j = boardSize - 2;
                while (j >= 0) {
                    move(i, j, 0, 1);
                }
                j--;
            }
            break;
    }
}

void gameBoard::move (int i, int j, int k, int l) {
    Tile &cur = board[i][j];
    Tile &tar = board[i + k][j + l];

    if (cur->value) {
        if (!tar.value) {
            tar.value = cur.value;
            cur.value = 0;
        } else if (cur.value == tar.value && !cur.blocked && tar.blocked) {
            tar.value *= 2;
            cur.value = 0;
            largestTile = largestTile < tar.value ? tar.value : largestTile;
            } 
    }
}

bool gameBoard::hasWon (int tar) {
    if (largestTile == tar) {
        return true;
    } else {
        return false;
    }
}

bool gameBoard::hasLost () {
    std::vector<std::vector<int>> freeTiles;
    getFreeTiles(freeTiles);

    if (!freeTiles.size()) {
        return true;
    } else {
        return false;
    }
}
 
void gameBoard::saveScore () {

}

void gameBoard::startGame () {

}



#endif
