#include <iostream>
#include "Game.h"
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#ifdef __EMSCRIPTEN__
void main_loop() {
    Game::Run();
}
#endif

int main()
{
    Game::Init("Gifts Giving", 1280, 800);
    #ifdef __EMSCRIPTEN__
        emscripten_set_main_loop(main_loop, 0, 1);
    #else
        while (Game::GetIsRunning())
        {
            Game::Run();
        }
    #endif
}