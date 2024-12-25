#pragma once
#include "Math/Vector2.h"
#include "string.h"

class Object
{
    public:
        Object(const std::string& newName, Vector2 startingPosition, Vector2 startingSize,bool bCollidesNew=false);
        virtual ~Object();
        virtual void Begin();
        virtual void Update();
        std::string name;
        Vector2 position;
        Vector2 size;
        bool bCollides;

    static Object* CreateObject(const std::string& newName,
     Vector2 startingPosition, Vector2 startingSize, bool bCollidesNew=false);
    static void DeleteObject(Object* object);
};