#pragma once
#include "SDL2/SDL.h"
#include <string>
#include "Texture.h"
#include "Math/Vector2.h"

class Sprite
{
    std::string name;
    Texture* texture;
    int zIndex;
    public:
        Sprite(const std::string& newName, Texture* newTexture, int zIndexNew);
        void Render(const SDL_FRect& destinationRectangle, const SDL_Rect& sourceRectangle);
        ~Sprite();
        std::string GetName() const {return name;};
        int GetIndexZ() const {return zIndex;};
};