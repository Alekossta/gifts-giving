#pragma once
#include "SDL2/SDL.h"
#include <string>
#include "Texture.h"

class Sprite
{
    std::string name;
    SDL_Rect sourceRectangle;
    SDL_FRect destinationRectangle;
    Texture* texture;
    public:
        Sprite(const std::string& newName);
        void Render();
        ~Sprite();
};