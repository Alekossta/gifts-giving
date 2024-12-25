#pragma once

class Game;

class State {
    bool bPaused;
    Game* game;
    public:
        State(Game* game);
        void Update();
        ~State();

        
};