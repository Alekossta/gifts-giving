#pragma once
#include "Object.h"
#include "Input/Input.h"

class Player : public Object
{  
    private:
        unsigned playerIndex;
        float playerSpeed;
        void CheckButtonCollision();
    public:
        Player(const std::string& playerName, Vector2 startingPosition, Vector2 startingSize,
        const std::string& newSrcName, Vector2 newSourceRectanglePosition, Vector2 newSourceRectangleSize,
        int zIndexNew, unsigned newPlayerIndex, float newPlayerSpeed);
        ~Player();
        virtual void Begin() override;
        virtual void Update(float deltatime) override;
        virtual void OnOverlap(Object* overlappingObject) override {};
};