#pragma once

#include <vector>
#include <map>
#include "Object.h"
#include "Input/Input.h"
#include "LevelManager/Level.h"

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
        void MoveObjectInternal(Object* object, Vector2 newPosition);
        void AddObjectToAll(Object* objectToAdd);
    public:
        static State& GetInstance();
        static void Update(float deltatime);
        static void Init();
        static void MoveObject(Object* object, Vector2 newPosition);
        static std::map<std::string, Object*>& GetAllObjects() {return GetInstance().allObjects;};
        static bool AreObjectsOverlapping(Object* object1, Object* object2); 
        static bool AreObjectsClose(Object* object1, Object* object2);
        std::map<std::string, int> tileCodeToTextureIndex;
        std::vector<std::string> wallCodes;
};