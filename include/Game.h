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

    unsigned width;
    unsigned height;

    public:
        // functions
        Game(const std::string& WindowName, unsigned newWidth, unsigned newHeight);
        bool GetIsRunning() const {return bIsRunning;};
        void SetIsRunning(bool bIsRunning) {this->bIsRunning = bIsRunning;};
        unsigned GetWidth() const {return width;};
        unsigned GetHeight() const {return height;};
        void Run();
        ~Game();

        // variables
        State* state;
        Graphics* graphics;
        Input* input;
};