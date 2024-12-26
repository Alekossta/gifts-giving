#include "Texture.h"
#include "Graphics.h"
#include "SDL2/SDL_image.h"

Texture::Texture(const std::string& newSrc) : src(newSrc)
{
    SDL_Surface* tempSurface = IMG_Load(newSrc.c_str()); 
    texture = SDL_CreateTextureFromSurface(Graphics::GetRenderer(), tempSurface);
    SDL_FreeSurface(tempSurface);
}

Texture::~Texture()
{
    SDL_DestroyTexture(texture);
}