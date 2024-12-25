#include <iostream>
#include "Game.h"
#include "Graphics.h"
#include "State.h"
#include "Input.h"

int main()
{
    Game mainGame ("Gift Giving", 1280, 800);
    while (mainGame.GetIsRunning())
    {
        mainGame.input->Listen();
        mainGame.state->Update();
        mainGame.graphics->Render();
    }
}