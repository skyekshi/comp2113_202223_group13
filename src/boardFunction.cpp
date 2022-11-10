#include <random>
#include <vector>
#include "boardFunction.hpp"

namespace Game {
    namespace {
        

        switch (toupper(c)) {
            case CODE_WASD_UP:
                intendedmove[FLAG_MOVE_UP] = true;
                return false;
            case CODE_WASD_LEFT:
                intendedmove[FLAG_MOVE_LEFT] = true;
                return false;
            case CODE_WASD_DOWN:
                intendedmove[FLAG_MOVE_DOWN] = true;
                return false;
            case CODE_WASD_RIGHT:
                intendedmove[FLAG_MOVE_RIGHT] = true;
                return false;

        enum gameFlag {
            Flag_win,
            Flag_maxNo
        };

        using gameStatus = std::array<bool, Flag_maxNo>;
        //what I mean by limiting move when it is already at the place

        

        bool movePossible () {
            for (int i = 0; i < boardSize; i++) {
                for (int j = 0; j < boardSize; j++) {
                    if (!gameBoard[i][j].value) {
                        return true;
                    }
                }
            }


        }

        gameBoard toMove (char c, gameBoard gbd) {
            switch (toupper(c)) {
                case WASD_UP:
                    moveTileUp(gbd);
                    break;
                case WASD_DOWN:
                    moveTileDown(gbd);
                    break;
                case WASD_LEFT:
                    moveTileLeft(gbd);
                    break;
                case WASD_RIGHT:
                    moveTileRight(gbd);
                    break;
            }
            return gbd;
        }

        void moveHorizontal(Directions d, int i, int j) {

        }

        //task 1 for handling both + and -
        void handleCollision(int i, int j) {

        }

        //task 2 for supermerging
        void mergeTiles() {
            
        }

        //task 4 for bonus & punishment; should also take care of the user interface
        bool updateGameBoardStat() {

        }



        bool checkWin() {

        }

        bool checkFull() {
            
        }


        //mainly tile management; for task 6
        struct gameboardData {
            
        };
        

        int RandInt(int max) {
            std::random_device rd;     // Only used once to initialise (seed) engine
            std::mt19937 rng(rd());    // Random-number engine used (Mersenne-Twister in this case)
            std::uniform_int_distribution<int> uni(0,max); // Guaranteed unbiased

            auto random_integer = uni(rng);
            return random_integer;
        }

        bool Tile3nSwitch() {

        }

        void setTileValue(gameBoard &gbd, gameboardPoint pt, ull value) {
            gameboardData{}(gbd, pt).value = value;
        }
        

        bool addTile(gameBoard &gbd) {

            const auto indexList = getFreeTiles(gbd);

            if (!indexList.size()) {
                return true;
            }

            const int playsize = getPlaySize(gbd);
            const int randomIndex = indexList.at(RandInt(1000) % indexList.size());

            const auto randomIndex_toPoint = gameboardPoint{randomIndex % playsize, randomIndex / playsize};
            
            if (Tile3nSwitch()) {
                const auto a = RandInt(100);
                if (a >= 50) {
                    const auto RandValue = a >= 90 ? 9 : 3;
                } else {
                    const auto RandValue = a <= 15 ? 2 : 4;
                }
            } else {
                const auto RandValue = RandInt(100) > 75 ? 4 : 2;
            }

            setTileValue(gbd, randomIndex_toPoint, RandValue);

            return false;
        } 
    }
}