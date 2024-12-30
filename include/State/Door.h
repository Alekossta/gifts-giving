#pragma once
#include "Object.h"
#include "Input/Input.h"
#include "State/Button.h"

class Door : public Object
{  
    private:
        bool bIsOpen;
        int doorCode;
        std::vector<Button*> interactingButtons;
        
    public:
        Door(const std::string& doorName, Vector2 position, Vector2 startingSize, 
            const std::string& newSrcName, Vector2 newSourceRectanglePosition, Vector2 newSourceRectangleSize,
            int zIndexNew, int doorCode);
        ~Door(){};

        virtual void Begin() override;
        virtual void Update(float deltatime) override;
};