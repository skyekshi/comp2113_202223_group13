#ifndef BOARDFUNCTION_H
#define BOARDFUNCTION_H

#include <tuple>
#include <vector>
#include <cstdlib>
#include <time.h>
#include <stdio.h>
//#include <conio.h>

class Tile {
    public:
        int value;
        bool blocked;
        Tile(): value(0), blocked(false) {}  
};

enum Directions {UP, DOWN, LEFT, RIGHT};

class gameBoard {
    public:
        int score;
        int largestTile;
        int tar;
        bool superMove;
        bool moreTile;
        bool init;
        bool won;
        bool woncheck;
        bool lost;
        std::vector<int> boardSize;
        std::vector<std::vector<Tile> > board;
        gameBoard(): score(0), largestTile(2), tar(2048), superMove(false), moreTile(false), init(false), boardSize({4,4}), board({}), won(false), woncheck(false), lost(false) {}
};

void addTile(gameBoard &gb);
//void updateBoard(gameBoard &gb);
bool canMove(gameBoard gb, Directions d);
void moveTile(gameBoard &gb, Directions d);
void mergeTile(gameBoard &gb, std::vector<int> &vectorToMerge);
void blockTile(gameBoard &gb);
void hasWon(gameBoard &gb);
void hasLost(gameBoard &gb);

void extension(gameBoard &gb);

#endif
