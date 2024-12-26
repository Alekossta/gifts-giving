#include "Graphics/Sprite.h"
#include "SDL2/SDL_image.h"
#include "Graphics/Graphics.h"

Sprite::Sprite(const std::string& newName) : name(newName)
{

}
void Sprite::Render()
{
    SDL_RenderCopyF(Graphics::GetRenderer(), texture->GetTexture(), &sourceRectangle, &destinationRectangle);
}

Sprite::~Sprite()
{
    
}