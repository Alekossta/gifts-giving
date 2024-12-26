#include "Game.h"
#include "Graphics/Graphics.h"
#include "State/State.h"
#include "Input/Input.h"

Game Game::instance;

void Game::InitInternal(const std::string& windowName, unsigned width, unsigned height)
{
    SetIsRunning(true);

    int result = SDL_Init(SDL_INIT_EVERYTHING);
    if(result < 0)
    {
        printf("Error in initialization of SDL subsystems: %s\n", SDL_GetError());
    }
    Input::Init();
    State::Init();
    Graphics::Init(windowName, width, height);
}

void Game::RunInternal()
{
    Input::Listen();
    State::Update();
    Graphics::Render();
}
