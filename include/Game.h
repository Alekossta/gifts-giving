#pragma once
#include <SDL2/SDL.h>
#include <string>

class Graphics;
class State;
class Input;

class Game {
    SDL_Renderer* renderer;
    SDL_Window* window;

    bool bIsRunning;

    public:
        // functions
        Game(const std::string& WindowName, unsigned Width, unsigned Height);
        bool GetIsRunning() const {return bIsRunning;};
        void SetIsRunning(bool bIsRunning) {this->bIsRunning = bIsRunning;};
        ~Game();

        // variables
        State* state;
        Graphics* graphics;
        Input* input;
};