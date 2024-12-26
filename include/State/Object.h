#pragma once
#include "Math/Vector2.h"
#include "string.h"

class Object
{
    public:
        Object(const std::string& newName, Vector2 startingPosition, Vector2 startingSize,bool bCollidesNew,
        const std::string& newSrcName, Vector2 newSourceRectanglePosition, Vector2 newSourceRectangleSize);
        virtual ~Object();
        virtual void Begin();
        virtual void Update(float deltatime);
        std::string name;
        Vector2 position;
        Vector2 size;
        bool bCollides;

        std::string srcName;
        Vector2 sourceRectanglePosition;
        Vector2 sourceRectangleSize;

    static Object* CreateObject(const std::string& newName,
     Vector2 startingPosition, Vector2 startingSize, bool bCollidesNew,
     const std::string& newSrcName, Vector2 newSourceRectanglePosition, Vector2 newSourceRectangleSize);
    static void DeleteObject(Object* object);
};