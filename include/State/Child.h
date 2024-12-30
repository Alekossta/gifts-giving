#pragma once
#include "Object.h"
#include "Input/Input.h"
#include "State/Child.h"

class Child : public Object
{  
    private:
        bool bIsActive;
        int opensDoorCode;
    public:
        Child(const std::string& childName, Vector2 position, Vector2 startingSize, 
            const std::string& newSrcName, Vector2 newSourceRectanglePosition, Vector2 newSourceRectangleSize,
            int zIndexNew);
        ~Child(){};
        bool getIsActive() const { return bIsActive; };
        bool getOpensDoorCode() const { return opensDoorCode; };
        virtual void Begin() override;
        virtual void Update(float deltatime) override;
        virtual void OnOverlap(Object* overlappingObject) override {};

        void AskGift();
        void DontAskGift();
};