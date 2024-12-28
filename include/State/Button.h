#pragma once
#include "Object.h"
#include "Input/Input.h"

class Button : public Object
{  
    private:
        bool bIsPressed;
        int opensDoorCode;
    public:
        Button(const std::string& buttonName, Vector2 position, Vector2 startingSize, bool bCollidesNew,
        const std::string& newSrcName, Vector2 newSourceRectanglePosition, Vector2 newSourceRectangleSize,
        int zIndexNew, bool bIsPressed, bool bIsVisibleNew, int opensDoorCode);
        ~Button(){};
        virtual void Begin() override;
        virtual void Update(float deltatime) override;
};