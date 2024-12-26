#include "Graphics/Graphics.h"
#include <iostream>
#include "State/State.h"
#include "Game.h"
#include "Graphics/Texture.h"

Graphics& Graphics::GetInstance() {
    // Avoid global declaration of instance before first call of getInstance
    static Graphics instance;
    return instance;
}

// Initialization
void Graphics::InitInternal(const std::string& windowName, unsigned width, unsigned height)
{
    window = SDL_CreateWindow(windowName.c_str(),
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              width,
                              height,
                              SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        throw std::runtime_error("Failed to create window");
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        throw std::runtime_error("Failed to create renderer");
    }
    
    for(const auto& pair : State::GetAllObjects())
    {
        Object* object = pair.second;
        auto foundTexturePair = textures.find(object->srcName);
        Texture* spriteTexture = NULL;
        if (foundTexturePair == textures.end()) // this means the texture does not exist
        {
            std::cout << "Creating new texture for source: " << object->srcName << std::endl;
            spriteTexture = new Texture(object->srcName);
            textures[object->srcName] = spriteTexture; // add new texture to map
        }
        else
        {
            spriteTexture = textures[object->srcName];
        }

        // create a sprite for each object
        SDL_Rect sourceRectangle = Game::Vectors2ToSdlRect(object->sourceRectanglePosition, object->sourceRectangleSize);
        Sprite* newSprite = new Sprite(pair.second->name, spriteTexture, sourceRectangle);
        sprites[object->name] = newSprite;
    }
}

// Cleanup
Graphics::~Graphics()
{
    if (renderer) {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }
    if (window) {
        SDL_DestroyWindow(window);
        window = nullptr;
    }
    SDL_Quit();
}

void Graphics::Init(const std::string& windowName, unsigned width, unsigned height)
{
    GetInstance().InitInternal(windowName, width, height);
}

SDL_Renderer* Graphics::GetRenderer() {
    return GetInstance().renderer;
}

void Graphics::RenderInternal()
{ 
    SDL_RenderClear(renderer);
    // render all sprites
    for(auto& sprite : sprites)
    {
        Vector2 spritePosition = State::GetAllObjects()[sprite.second->GetName()]->position;
        Vector2 spriteSize = State::GetAllObjects()[sprite.second->GetName()]->size;
        SDL_FRect destinationRectangle = Game::Vectors2ToSdlFRect(spritePosition, spriteSize);
        sprite.second->Render(destinationRectangle);
    }
    SDL_RenderPresent(renderer);
}

void Graphics::Render()
{
    GetInstance().RenderInternal();
}