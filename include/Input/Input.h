#pragma once

class Game;

class Input
{
    Game* game;
    public:
        Input(Game* game);
        void Listen();
        ~Input();
};