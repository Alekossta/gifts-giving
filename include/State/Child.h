#pragma once
#include "Object.h"
#include "Input/Input.h"
#include "State/Child.h"
#include "State/TextBox.h"
#include "TimerHandler.h"

class Child : public Object
{  
    private:
        TimerHandler timeToGiveGift;
        TimerHandler timeToDisappear;
        bool bAsksGift;

    public:

        Child(const std::string& childName, Vector2 position, Vector2 startingSize, 
            const std::string& newSrcName, Vector2 newSourceRectanglePosition, Vector2 newSourceRectangleSize,
            int zIndexNew, Object* newTextHolder, TextBox* textBox, TextBox* timeTexBox, int secondsLeft);
        ~Child(){};
        virtual void Begin() override;
        virtual void Update(float deltatime) override;
        Object* textHolder;
        TextBox* textBox;
        TextBox* timeTextBox;
};