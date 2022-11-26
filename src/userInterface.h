#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include <string>
#include "boardFunction.h"
using namespace std;

vector<int> getLinuxShape();
void printLeftPadding(int);
void printUpPadding(int);
void printMenu();
void printMessage(string);
void printMenuAfter();
void printGamePage(gameBoard, int);

#endif