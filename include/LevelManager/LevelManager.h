#pragma once

#include <vector>
#include <map>
#include "Level.h"

class Game;

class LevelManager {
    private:
        static LevelManager instance;

        void InitInternal();
        void UpdateInternal(float deltatime);
        LevelManager(){};
        ~LevelManager();

        std::map<std::string, Level*> levels;

    public:
        static LevelManager& GetInstance();
        static void Init();
        static std::map<std::string, Level*>& GetLevels();
};