#pragma once
#include "Object.h"
#include "Input/Input.h"
#include "State/Child.h"
#include "State/TextBox.h"
#include "TimerHandler.h"

class Child : public Object
{  
    private:
        
        bool bAsksGift;
        bool bDisappearing = false;

    public:
        TimerHandler timeToGiveGift;
        TimerHandler timeToDisappear;
        Child(const std::string& childName, Vector2 position, Vector2 startingSize, 
            const std::string& newSrcName, Vector2 newSourceRectanglePosition, Vector2 newSourceRectangleSize,
            int zIndexNew, Object* newTextHolder, TextBox* textBox, TextBox* timeTexBox, int secondsLeft);
        ~Child(){};
        virtual void Begin() override;
        virtual void Update(float deltatime) override;
        void DisappearTimerEnded();
        Object* textHolder;
        TextBox* textBox;
        TextBox* timeTextBox;
};