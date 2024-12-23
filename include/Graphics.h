#pragma once
#include "SDL2/SDL.h"
#include "string.h"
#include "Game.h"

class Graphics {
    SDL_Renderer* renderer;
    SDL_Window* window;
    Game* game;
    public:
        Graphics();
        Graphics(const std::string& windowName, unsigned width, unsigned height, Game* game);
        void Render();
        ~Graphics();
};