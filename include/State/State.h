#pragma once

#include <vector>
#include <map>
#include "Object.h"
#include "Input/Input.h"

class Game;

class State {
    private:
        static State instance;

        bool bPaused;
        Game* game;
        Input* input;

        void InitInternal();
        void UpdateInternal();
        State(){};
        ~State();

        std::map<std::string, Object*> allObjects;
        std::vector<Object*> collidingObjects;

        void AddObjectToAll(Object* objectToAdd);
        void AddObjectToColliding(Object* objectToAdd);
    public:
        static State& GetInstance();
        static void Update();
        static void Init();
};