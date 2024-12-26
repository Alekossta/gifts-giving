#include "Graphics/Sprite.h"
#include "SDL2/SDL_image.h"
#include "Graphics/Graphics.h"

Sprite::Sprite(const std::string& newName, const std::string& newSrc) : name(newName), src(newSrc)
{
    SDL_Surface* tempSurface = IMG_Load(newSrc.c_str()); 
    texture = SDL_CreateTextureFromSurface(Graphics::GetRenderer(), tempSurface);
    SDL_FreeSurface(tempSurface);
}
void Sprite::Render()
{
    SDL_RenderCopyF(Graphics::GetRenderer(), texture, &sourceRectangle, &destinationRectangle);
}

Sprite::~Sprite()
{
    SDL_DestroyTexture(texture);
}