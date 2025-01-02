#pragma once
#include "SDL2/SDL.h"
#include <string>
#include "Texture.h"
#include "Math/Vector2.h"

class Sprite
{
    protected:
        std::string name;
        Texture* texture;
        int zIndex;
    public:
        Sprite(const std::string& newName, Texture* newTexture, int zIndexNew);
        
        virtual void Render(const SDL_Rect* sourceRectangle, 
                  SDL_FRect* destinationRectangle, 
                  float angle = 0.0f, 
                  const SDL_FPoint* center = nullptr, 
                  SDL_RendererFlip flip = SDL_FLIP_NONE);
        ~Sprite();
        std::string GetName() const {return name;};
        int GetIndexZ() const {return zIndex;};
        SDL_Texture* GetTexture() const { return texture->GetTexture(); };
        void SetTexture(Texture* newTexture);
};