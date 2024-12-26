#include <iostream>
#include "Game.h"

int main()
{
    Game::Init("Gifts Giving", 1280, 800);
    while (Game::GetIsRunning())
    {
        Game::Run();
    }
}