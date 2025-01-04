#pragma once
#include "Math/Vector2.h"
#include "string.h"
#include <vector>

class Object
{
    public:
        Object(const std::string& newName, Vector2 startingPosition, Vector2 startingSize,
         const std::string& newSrcName, Vector2 newSourceRectanglePosition, Vector2 newSourceRectangleSize,
         int zIndexNew,bool bCollidesNew=true, bool bOverlapsNew=true, bool bIsVisibleNew=true, float rotation = 0.0);
        virtual ~Object();
        virtual void Begin();
        virtual void Update(float deltatime);
        virtual void setIsVisible(bool newbIsVisible);
        std::string name;
        Vector2 position;
        Vector2 size;
        std::string srcName;
        Vector2 sourceRectanglePosition;
        Vector2 sourceRectangleSize;
        int zIndex;
        bool bCollides;
        std::vector<std::string> Tags;
        std::vector<std::string> CollisionIgnoreTags;
        std::vector<Object*> children;
        bool bIsVisible;
        float rotation;
};