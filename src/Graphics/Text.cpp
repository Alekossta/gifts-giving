#include "Graphics/Text.h"
#include "SDL2/SDL_ttf.h"
#include "Game.h"
#include <stdio.h>
#include "Graphics/Graphics.h"

Text::Text(const std::string& spriteName, const std::string& startingText,const SDL_Color& startingColor,
 int zIndexNew) : Sprite(spriteName, NULL, zIndexNew)
{
    RegenerateTexture(startingColor, startingText);
}

void Text::Render(const SDL_Rect* sourceRectangle, 
    SDL_FRect* destinationRectangle, 
    float angle, 
    const SDL_FPoint* center, 
    SDL_RendererFlip flip)
{
    int w;
    int h;
    TTF_SizeText(Game::GetGameFont(), currentText.c_str(), &w, &h);
    destinationRectangle->w = w;
    destinationRectangle->h = h;
    SDL_RenderCopyExF(Graphics::GetRenderer(), texture->GetTexture(), NULL, destinationRectangle, angle, center, flip);    
}

void Text::RegenerateTexture(const SDL_Color& newColor, const std::string& newText)
{
    currentText = newText;
    SDL_Surface* surface = TTF_RenderText_Solid(Game::GetGameFont(), currentText.c_str(), newColor);
    if(texture)
    {
        delete texture;
        texture = new Texture(SDL_CreateTextureFromSurface(Graphics::GetRenderer(), surface), "TextTexture");
    }
    else
    {
        texture = new Texture(SDL_CreateTextureFromSurface(Graphics::GetRenderer(), surface), "TextTexture");
    }
    SDL_FreeSurface(surface);
}

Text::~Text()
{
    delete texture;
}