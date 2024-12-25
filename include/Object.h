#pragma once
#include "Math/Vector2.h"

class Object
{
    public:
        Object(Vector2 startingPosition, Vector2 startingSize);
        Vector2 position;
        Vector2 size;
};