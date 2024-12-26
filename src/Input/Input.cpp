#include "Input/Input.h"
#include <SDL2/SDL.h>
#include "Game.h"

Input Input::instance;

void Input::InitInternal()
{
    
}

void Input::ListenInternal()
{
    SDL_Event currentEvent;
    while(SDL_PollEvent(&currentEvent))
    {
        switch (currentEvent.type)
        {
            case SDL_QUIT:
                game->SetIsRunning(false);
                break;
            case SDL_MOUSEBUTTONDOWN:
                break;
            case SDL_MOUSEMOTION:
                break;
            default:
                break;
        }
    }

    const Uint8* keyboardState = SDL_GetKeyboardState(0);
    if(keyboardState[SDL_SCANCODE_SPACE] == 1)
    {
        printf("Space is pressed\n");
    }
}

void Input::Init()
{
    GetInstance().InitInternal();
}

void Input::Listen()
{
    GetInstance().ListenInternal();
}

static bool IsKeyPressed(SDL_Scancode keyCode)
{
    const Uint8* keyboardState = SDL_GetKeyboardState(NULL);
    return keyboardState[keyCode];
}