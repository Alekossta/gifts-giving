#pragma once
#include "SDL2/SDL.h"
#include <string>

class Texture
{
    private:
        SDL_Texture* texture;
        std::string src;
    public:
        Texture(SDL_Texture* texture, const std::string& newSrc);
        ~Texture();
        void Destroy();
        SDL_Texture* GetTexture() const {return texture;};
};