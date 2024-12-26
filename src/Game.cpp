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

SDL_Rect Game::Vectors2ToSdlRect(const Vector2& positionVector, const Vector2& scaleVector)
{
    SDL_Rect newRect;
    newRect.x = positionVector.x;
    newRect.y = positionVector.y;
    newRect.w = scaleVector.x;
    newRect.h = scaleVector.y;

    return newRect;
}

SDL_FRect Game::Vectors2ToSdlFRect(const Vector2& positionVector, const Vector2& scaleVector)
{
    SDL_FRect newRect;
    newRect.x = positionVector.x;
    newRect.y = positionVector.y;
    newRect.w = scaleVector.x;
    newRect.h = scaleVector.y;

    return newRect;
}