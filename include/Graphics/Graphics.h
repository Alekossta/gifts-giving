#pragma once
#include "SDL2/SDL.h"
#include <string>
#include <map>
#include "Sprite.h"

class Game;

class Graphics {
    private:
        static Graphics instance; // Singleton instance
        SDL_Renderer* renderer;
        SDL_Window* window;
        // name, Sprite
        std::map<std::string, Sprite*> sprites;
        // srcName, Texture
        std::map<std::string, Texture*> textures;

        // Private constructor for singleton pattern
        Graphics(){};

        // internal
        void RenderInternal();
        void InitInternal(const std::string& windowName, unsigned width, unsigned height);

        void InitSpritesInternal();

        // Delete copy constructor and assignment operator to prevent duplicates
        Graphics(const Graphics&) = delete;
        Graphics& operator=(const Graphics&) = delete;

        ~Graphics();
    public:
        static Graphics& GetInstance();
        static SDL_Renderer* GetRenderer();
        static void Render();
        static void Init(const std::string& windowName, unsigned width, unsigned height);
};