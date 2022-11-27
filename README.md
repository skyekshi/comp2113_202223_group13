# COMP2113 Group 13 - New 2048

## Group Members
Li Kehan 3035637216 \
Shi Keyan 3035638208 \
Zheng Mengming 3035844285

## Game Description

A new variation of the classical 2048 game. We introduced supermerging, dynamic gameboard, target reset, more value possibilities. The game rules are: 
1. N/n: start new game
2. R/r: resume the last game
3. Q/q: quit game
4. B/b: block a random tile
5. M/m: enable supermerging such that any consecutive same tiles will be merged
6. T/t: enable the gameboard to generate tiles of 3 and 9 (together with 2 and 4)
7. U/u: change your winning target, by default it is 2048.
8. Z/z: change the board size, it can vary from 4x4 to 6x6, and rectangle is allowed 
9. W/w, A/a, S/s, D/d: control the moving direction. Up, left, down, and right, respectively.

## Code Requirements

- Generation of random game sets or events \
The value and position of the tile generated each time (on legit moves) is completely randomized. 

- Data structures for storing game status \
We used class to store the gameboard status and the tile. For example, the current score, the largest tile, whether supermerging and extra tiles are allowed, the board size, the value in the grid.

- Dynamic memory management \
We used new and delete for creating and deleting gameboard, so that we release memory when we are no longer using them.

- File input/output (e.g., for loading/saving game status) \
We store the historical highest points and last game status in separate text files, and those files are loaded if one wants to resume the last game.

- Program codes in multiple files \
The main function is gamePlay.cpp. We separate the functions for moving board, storing and retrieving data, and user interface into different files. This kind of frontend and backend divide improves efficiency.

- Proper indentation and naming styles \
Namings are indicative, indentations are standard.

- In-code documentation \
In-place explanations provided.

## List of non-standard C/C++ libraries

No need for additional downloading.

## Compilation and Execution

To compile:
```
make 2048
```
To execute:
```
./2048
```

## Demonstration Video
Link [here](https://youtu.be/X8xBxvtmrKA).
