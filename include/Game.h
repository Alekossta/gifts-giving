#pragma once
#include <SDL2/SDL.h>
#include <string>
#include "Math/Vector2.h"
#include <SDL2/SDL_ttf.h>

#define TILE_SIZE 80
#define NUM_OF_TILES_ROW (1280 / 80)
#define NUM_OF_TILES_COL (800 / 80)
#define PI 3.14

class Game {

    private:
        static Game instance;

        Game(){};
        ~Game(){};

        bool bIsRunning;

        unsigned width;
        unsigned height;

        Uint32 lastFrameStart;
        float deltatime;

        void InitInternal(const std::string& windowName, unsigned newWidth, unsigned newHeight);
        void RunInternal();
        TTF_Font* gameFont;

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

        static SDL_Rect Vectors2ToSdlRect(const Vector2& positionVector, const Vector2& scaleVector);
        static SDL_FRect Vectors2ToSdlFRect(const Vector2& positionVector, const Vector2& scaleVector);
        static TTF_Font* GetGameFont() { return GetInstance().gameFont; };

};