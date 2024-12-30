#include "Graphics/Sprite.h"
#include "SDL2/SDL_image.h"
#include "Graphics/Graphics.h"

Sprite::Sprite(const std::string& newName, Texture* newTexture, int zIndexNew)
 : name(newName), texture(newTexture), zIndex(zIndexNew)
{

}

void Sprite::Render(const SDL_Rect* sourceRectangle, 
                  const SDL_FRect* destinationRectangle, 
                  float angle, 
                  const SDL_FPoint* center, 
                  SDL_RendererFlip flip) 
{
    SDL_RenderCopyExF(Graphics::GetRenderer(), texture->GetTexture(), sourceRectangle, destinationRectangle, angle, center, flip);
}
Sprite::~Sprite()
{
    
}