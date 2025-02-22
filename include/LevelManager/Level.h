#pragma once

#include <vector>
#include <map>
#include <string>
#include "Game.h"
#include "Input/Input.h"

class Game;

class Level {
    private:
        static Level instance;

        Level(){};
        ~Level();

        std::string fileName;
        
    public:
        Level(const std::string& filePath);
        static Level& GetInstance();
        static void Init();
        std::string grid[NUM_OF_TILES_COL][NUM_OF_TILES_ROW];
};