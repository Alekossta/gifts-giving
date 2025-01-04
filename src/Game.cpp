#include "Game.h"
#include "Graphics/Graphics.h"
#include "State/State.h"
#include "Input/Input.h"

Game Game::instance;

void Game::InitInternal(const std::string& windowName, unsigned newWidth, unsigned newHeight)
{
    width = newWidth;
    height = newHeight;
    TTF_Init(); 
    gameFont = TTF_OpenFont("assets/fonts/Roboto-Black.ttf", 20);

    SetIsRunning(true);

    int result = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    if(result < 0)
    {
        printf("Error in initialization of SDL subsystems: %s\n", SDL_GetError());
    }
    Input::Init();
    State::Init();
    Graphics::Init(windowName, width, height);
}

std::string Game::GetAssetPath(const std::string& path)
{
    #ifdef __EMSCRIPTEN__
        return "/assets/" + path; // Web
    #else
        return "./assets/" + path; // Local
    #endif
}

void Game::RunInternal()
{
    Uint32 frameStart = SDL_GetTicks();
    deltatime = (frameStart - lastFrameStart) / 1000.0f;
    lastFrameStart = frameStart;
    Input::Listen();
    State::Update(deltatime);
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