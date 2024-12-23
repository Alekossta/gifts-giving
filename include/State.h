#pragma once
class State {
    bool bPaused;
    public:
        State();
        void Create();
        void Update();
        ~State();
};