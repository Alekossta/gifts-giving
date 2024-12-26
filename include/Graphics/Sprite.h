#pragma once
#include "SDL2/SDL.h"
#include <string>
#include "Texture.h"
#include "Math/Vector2.h"

class Sprite
{
    std::string name;
    Texture* texture;
    SDL_Rect sourceRectangle;
    int zIndex;
    public:
        Sprite(const std::string& newName, Texture* newTexture, const SDL_Rect& newSourceRectangle, int zIndexNew);
        void Render(const SDL_FRect& destinationRectangle);
        ~Sprite();
        std::string GetName() const {return name;};
        int GetIndexZ() const {return zIndex;};
};