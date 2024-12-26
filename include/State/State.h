#pragma once

#include <vector>
#include <map>
#include "Object.h"
#include "Input/Input.h"

class Game;

class State {
    bool bPaused;
    Game* game;
    Input* input;
    public:
        State(Game* newGame, Input* newInput);
        void Update();
        ~State();
        std::map<std::string, Object*> allObjects;
        std::vector<Object*> collidingObjects;

        void AddObjectToAll(Object* objectToAdd);
        void AddObjectToColliding(Object* objectToAdd);
};