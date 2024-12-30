#include "Graphics/Sprite.h"
#include "SDL2/SDL_image.h"
#include "Graphics/Graphics.h"

Sprite::Sprite(const std::string& newName,Texture* newTexture, int zIndexNew)
 : name(newName), texture(newTexture), zIndex(zIndexNew)
{

}
void Sprite::Render(const SDL_FRect& destinationRectangle, const SDL_Rect& sourceRectangle)
{
    SDL_RenderCopyF(Graphics::GetRenderer(), texture->GetTexture(), &sourceRectangle, &destinationRectangle);
}

Sprite::~Sprite()
{
    
}