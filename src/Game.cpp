#include "Game.h"
#include "Graphics.h"
#include "State.h"
#include "Input.h"

Game::Game(const std::string& windowName, unsigned width, unsigned height)
{
   // Initialize SDL subsystems
    int result = SDL_Init(SDL_INIT_EVERYTHING);
    if(result < 0)
    {
        printf("Error in initialization of SDL subsystems: %s\n", SDL_GetError());
    }
    
    graphics = new Graphics(windowName, width, height, this);
    state = new State(this);
    input = new Input(this);
}

Game::~Game()
{
    delete input;
    delete state;
    delete graphics;

    SDL_Quit();
}