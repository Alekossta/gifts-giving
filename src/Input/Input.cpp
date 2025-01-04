#include "Input/Input.h"
#include <SDL2/SDL.h>
#include "Game.h"
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

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
                Game::SetIsRunning(false);
                #ifdef __EMSCRIPTEN__
                    emscripten_cancel_main_loop();
                #endif
                break;
            case SDL_MOUSEBUTTONDOWN:
                break;
            case SDL_MOUSEMOTION:
                break;
            default:
                break;
        }
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

bool Input::IsKeyPressed(SDL_Scancode keyCode)
{
    const Uint8* keyboardState = SDL_GetKeyboardState(NULL);
    return keyboardState[keyCode];
}