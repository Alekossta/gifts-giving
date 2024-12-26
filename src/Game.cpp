#include "Game.h"
#include "Graphics/Graphics.h"
#include "State/State.h"
#include "Input/Input.h"

Game::Game(const std::string& windowName, unsigned width, unsigned height)
{
   // Initialize SDL subsystems
    int result = SDL_Init(SDL_INIT_EVERYTHING);
    if(result < 0)
    {
        printf("Error in initialization of SDL subsystems: %s\n", SDL_GetError());
    }
    input = new Input(this);
    state = new State(this, input);
    graphics = new Graphics(windowName, width, height, this);
}

void Game::Run()
{
    input->Listen();
    state->Update();
    graphics->Render();   
}

Game::~Game()
{
    delete input;
    delete state;
    delete graphics;

    SDL_Quit();
}