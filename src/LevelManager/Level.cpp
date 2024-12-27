#include "LevelManager/Level.h"
#include <string>
#include <iostream>
#include <fstream>


Level::Level(const std::string& filePath) {
    std::ifstream file(filePath.c_str());
    for (int i = 0; i < NUM_OF_TILES_ROW; i++) 
    {
        for (int j = 0; j < NUM_OF_TILES_COL; j++) 
        {
            file >> grid[i][j];
        }
    }
}