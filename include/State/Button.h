#pragma once
#include "Object.h"
#include "Input/Input.h"

class Button : public Object
{  
    private:
        unsigned playerIndex;
        float playerSpeed;
    public:
        Button(const std::string& buttonName, Vector2 position, Vector2 startingSize,
        const std::string& newSrcName, Vector2 newSourceRectanglePosition, Vector2 newSourceRectangleSize,
        int zIndexNew);
        ~Button();
        virtual void Begin() override;
        virtual void Update(float deltatime) override;
};