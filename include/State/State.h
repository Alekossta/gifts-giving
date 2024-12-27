#pragma once

#include <vector>
#include <map>
#include "Object.h"
#include "Input/Input.h"
#include "Level/Level.h"

class Game;

class State {
    private:
        static State instance;

        bool bPaused;
        Level* currentLevel;

        void InitInternal();
        void UpdateInternal(float deltatime);
        State(){};
        ~State();

        std::map<std::string, Object*> allObjects;
        std::vector<Object*> collidingObjects;
        void MoveObjectInternal(Object* object, Vector2 newPosition);
        void AddObjectToAll(Object* objectToAdd);
        void AddObjectToColliding(Object* objectToAdd);
    public:
        static State& GetInstance();
        static void Update(float deltatime);
        static void Init();
        static void MoveObject(Object* object, Vector2 newPosition);
        static std::map<std::string, Object*>& GetAllObjects() {return GetInstance().allObjects;};
};