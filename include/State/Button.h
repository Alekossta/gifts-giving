#pragma once
#include "Object.h"
#include "Input/Input.h"

class Button : public Object
{  
    private:
        bool bIsActive;
        int opensDoorCode;
    public:
        Button(const std::string& buttonName, Vector2 position, Vector2 startingSize, 
            const std::string& newSrcName, Vector2 newSourceRectanglePosition, Vector2 newSourceRectangleSize,
            int zIndexNew, int opensDoorCode);
        ~Button(){};
        bool getIsActive() const { return bIsActive; };
        int getOpensDoorCode() const { return opensDoorCode; };
        virtual void Begin() override;
        virtual void Update(float deltatime) override;

        void Activate();
        void DeActivate();
};