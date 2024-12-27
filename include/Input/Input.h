#pragma once
#include "SDL2/SDL.h"

class Game;

class Input
{
    private:
        static Input instance;

        Input(){};
        ~Input(){};

        void InitInternal();
        void ListenInternal();
        
    public:
        static Input& GetInstance() {return instance;};
        static void Init();
        static void Listen();
        static bool IsKeyPressed(SDL_Scancode keyCode);
};