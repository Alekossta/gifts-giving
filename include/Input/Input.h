#pragma once

class Game;

class Input
{
    private:
        static Input instance;

        Input(){};
        ~Input(){};

        void InitInternal();
        void ListenInternal();

        Game* game;
    public:
        static Input& GetInstance() {return instance;};
        static void Init();
        static void Listen();
};