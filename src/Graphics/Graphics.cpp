#include "Graphics/Graphics.h"
#include <iostream>

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
        sprite.second->Render();
    }
    SDL_RenderPresent(renderer);
}

void Graphics::Render()
{
    GetInstance().RenderInternal();
}