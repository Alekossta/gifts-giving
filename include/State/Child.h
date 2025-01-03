#pragma once
#include "Object.h"
#include "Input/Input.h"
#include "State/Child.h"
#include "State/TextBox.h"

class Child : public Object
{  
    private:
        bool bIsActive;
        int opensDoorCode;
        TextBox* textBox;
        int secondsToGiveGift;
        TextBox* timeTextBox;
    public:
        Child(const std::string& childName, Vector2 position, Vector2 startingSize, 
            const std::string& newSrcName, Vector2 newSourceRectanglePosition, Vector2 newSourceRectangleSize,
            int zIndexNew, TextBox* textBox, TextBox* timeTexBox, int secondsToGiveGift);
        ~Child(){};
        bool getIsActive() const { return bIsActive; };
        bool getOpensDoorCode() const { return opensDoorCode; };
        virtual void Begin() override;
        virtual void Update(float deltatime) override;
        virtual void OnOverlap(Object* overlappingObject) override {};
};