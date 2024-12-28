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
        std::map<std::string, Level*> GetLevelsInternal();
        LevelManager(){};
        

        std::map<std::string, Level*> levels;

    public:
        static LevelManager& GetInstance() {return instance;}
        static void Init();
        static std::map<std::string, Level*>& GetLevels() {return GetInstance().levels; };
        ~LevelManager() {};
};