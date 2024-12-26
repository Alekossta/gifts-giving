#pragma once
#include "SDL2/SDL.h"
#include "string"

class Sprite
{
    std::string name;
    std::string src;
    SDL_Texture* texture;
    SDL_Rect sourceRectangle;
    SDL_FRect destinationRectangle;
    public:
        Sprite(const std::string& newName, const std::string& newSrc);
        void Render();
        ~Sprite();
};