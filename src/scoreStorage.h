#ifndef SCORESTORAGE_H
#define SCORESTORAGE_H
#include "boardFunction.h"

void saveScore(int);
int retrieveScore();
void saveGame(gameBoard gb);
void retrieveGame(gameBoard &gb);

#endif