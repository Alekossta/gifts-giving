#pragma once
#include "Object.h"
#include "Input/Input.h"

class Player : public Object
{  
    private:
        unsigned playerIndex;
        float playerSpeed;
    public:
        Player(const std::string& playerName, Vector2 startingPosition, Vector2 startingSize,
        const std::string& newSrcName, Vector2 newSourceRectanglePosition, Vector2 newSourceRectangleSize,
         unsigned newPlayerIndex, float newPlayerSpeed);
        ~Player();
        virtual void Begin() override;
        virtual void Update(float deltatime) override;
};