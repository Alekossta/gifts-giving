#include "Graphics/Texture.h"
#include "Graphics/Graphics.h"
#include "SDL2/SDL_image.h"

Texture::Texture(SDL_Texture* newTexture, const std::string& newSrc) : src(newSrc), texture(newTexture)
{   

}

void Texture::Destroy()
{
    SDL_DestroyTexture(texture);
}

Texture::~Texture()
{
    Destroy();
}