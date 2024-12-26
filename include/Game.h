#pragma once
#include <SDL2/SDL.h>
#include <string>

class Game {

    private:
        static Game instance;

        Game(){};
        ~Game(){};

        bool bIsRunning;

        unsigned width;
        unsigned height;

        void InitInternal(const std::string& windowName, unsigned newWidth, unsigned newHeight);
        void RunInternal();

    public:
        // functions
        static Game& GetInstance() {return instance;};
        static void Init(const std::string& windowName, unsigned newWidth, unsigned newHeight)
        {GetInstance().InitInternal(windowName, newWidth, newHeight);};

        static bool GetIsRunning() {return GetInstance().bIsRunning;};
        static void SetIsRunning(bool bIsRunning) {GetInstance().bIsRunning = bIsRunning;};

        static unsigned GetWidth() {return GetInstance().width;};
        static unsigned GetHeight() {return GetInstance().height;};
        static void Run() {GetInstance().RunInternal();};
};