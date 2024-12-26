#pragma once
#include "Object.h"
#include "Input/Input.h"

class Player : public Object
{  
    public:
        Player(const std::string& playerName, Vector2 startingPosition, Vector2 startingSize,
        const std::string& newSrcName, Vector2 newSourceRectanglePosition, Vector2 newSourceRectangleSize);
        ~Player();
        virtual void Begin() override;
        virtual void Update() override;
        static Player* CreatePlayer(const std::string& newName,
            Vector2 startingPosition, Vector2 startingSize,
            const std::string& newSrcName, Vector2 newSourceRectanglePosition, Vector2 newSourceRectangleSize);
};