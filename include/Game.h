#pragma once
#include <SDL2/SDL.h>
#include <string>
#include "State.h"
#include "Graphics.h"

class Game {
    SDL_Renderer* renderer;
    SDL_Window* window;
    State state;
    Graphics graphics;
    bool bIsRunning;

    public:
        Game(const std::string& WindowName, unsigned Width, unsigned Height);
        bool GetIsRunning() const {return bIsRunning;};
        void SetIsRunning(bool bIsRunning) {this->bIsRunning = bIsRunning;};
};