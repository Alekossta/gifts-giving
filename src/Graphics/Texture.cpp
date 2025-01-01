#include "Graphics/Texture.h"
#include "Graphics/Graphics.h"
#include "SDL2/SDL_image.h"

Texture::Texture(SDL_Texture* newTexture, const std::string& newSrc) : src(newSrc)
{   
    if (newTexture == NULL) {
        SDL_Surface* tempSurface = IMG_Load(newSrc.c_str());
        if(!tempSurface)
        {
            std::cout << "Error opening image: " << newSrc << std::endl;
        }
        texture = SDL_CreateTextureFromSurface(Graphics::GetRenderer(), tempSurface);
        SDL_FreeSurface(tempSurface);
    } else {
        texture = newTexture;
    }
}

Texture::~Texture()
{
    SDL_DestroyTexture(texture);
}