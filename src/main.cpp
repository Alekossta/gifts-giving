#include <iostream>
#include "Game.h"

int main()
{
    Game mainGame ("Gifts Giving", 1280, 800);
    while (mainGame.GetIsRunning())
    {
        mainGame.Run();
    }
}