#pragma once
#include "SDL2/SDL.h"
#include <string>

class Texture
{
    private:
        SDL_Texture* texture;
        std::string src;
    public:
        Texture(const std::string& newSrc);
        ~Texture();
        SDL_Texture* GetTexture() const {return texture;};
};