#include "Graphics.h"

Graphics::Graphics(const std::string& windowName, unsigned width, unsigned height, Game* game) {
    // Create the window and check errors
    window = SDL_CreateWindow(
        windowName.c_str(),
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width, height,
        SDL_WINDOW_SHOWN
    );
    if(!window) // Error check
    {
        printf("Could not create window: %s\n", SDL_GetError());
        if(game)
        {
            game->SetIsRunning(false);
        }
    }

    // Create the renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(!renderer) // Error check
    {
        printf("Could not create renderer: %s\n", SDL_GetError());
        if(game)
        {
            game->SetIsRunning(false);
        }      
    }    
}