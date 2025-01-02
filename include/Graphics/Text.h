#pragma once
#include <string>
#include <SDL2/SDL.h>
#include "Graphics/Sprite.h"

class Text : public Sprite
{
    public:
        // courent text
        std::string currentText;
        Text(const std::string& spriteName, const std::string& startingText,
        const SDL_Color& startingColor, int zIndexNew);
        virtual void Render(const SDL_Rect* sourceRectangle, 
                SDL_FRect* destinationRectangle, 
                float angle = 0.0f, 
                const SDL_FPoint* center = nullptr, 
                SDL_RendererFlip flip = SDL_FLIP_NONE) override;
        ~Text();
        void RegenerateTexture(const SDL_Color& newColor, const std::string& newText);
};