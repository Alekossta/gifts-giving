#include "LevelManager/LevelManager.h"
#include <string>
#include <iostream>
#include <filesystem>

LevelManager LevelManager::instance;

void LevelManager::InitInternal() 
{
    std::string path = "/assets/levels";
    int counter = 0;
    for (const auto & entry : std::filesystem::directory_iterator(path)) 
    {
        levels["Level" + std::to_string(counter++)] = new Level(entry.path()); 
    }
}

void LevelManager::Init() {
    LevelManager::GetInstance().InitInternal();
}