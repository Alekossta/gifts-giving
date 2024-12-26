#include "Graphics/Sprite.h"
#include "SDL2/SDL_image.h"
#include "Graphics/Graphics.h"

Sprite::Sprite(const std::string& newName,Texture* newTexture, const SDL_Rect& newSourceRectangle) : name(newName),
texture(newTexture), sourceRectangle(newSourceRectangle)
{

}
void Sprite::Render(const SDL_FRect& destinationRectangle)
{
    SDL_RenderCopyF(Graphics::GetRenderer(), texture->GetTexture(), &sourceRectangle, &destinationRectangle);
}

Sprite::~Sprite()
{
    
}