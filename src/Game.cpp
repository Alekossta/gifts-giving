#include "Game.h"

Game::Game(const std::string& windowName, unsigned width, unsigned height)
{
   // Initialize SDL subsystems
    int result = SDL_Init(SDL_INIT_EVERYTHING);
    if(result < 0)
    {
        printf("Error in initialization of SDL subsystems: %s\n", SDL_GetError());
    }
    
    graphics = Graphics(windowName, width, height, this);
    state = State();
}
