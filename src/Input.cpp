#include "Input.h"
#include <SDL2/SDL.h>
#include "Game.h"

Input::Input(Game* game)
{
    
}

void Input::Listen()
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

Input::~Input()
{

}