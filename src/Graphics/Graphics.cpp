#include "Graphics/Graphics.h"
#include "Game.h"
#include "General.h"
#include "Graphics/Texture.h"
#include "State/State.h"
#include "State/TextBox.h"
#include <algorithm>
#include <iostream>
#include <vector>
#include <SDL2/SDL_ttf.h>

Graphics &Graphics::GetInstance() {
  // Avoid global declaration of instance before first call of getInstance
  static Graphics instance;
  return instance;
}

// Initialization
void Graphics::InitInternal(const std::string &windowName, unsigned width,unsigned height) 
{  

  window =  SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_CENTERED,
  SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);

  if (!window) {
    std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
    throw std::runtime_error("Failed to create window");
  }

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (!renderer) {
    std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
    SDL_DestroyWindow(window);
    throw std::runtime_error("Failed to create renderer");
  }

  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

  for (const auto &[name, object] : State::GetAllObjects()) 
  {   
    TextBox* text = dynamic_cast<TextBox*>(object);    
    if (text) 
    {
        // Text sprites do not have an src rectangle or an image related to them
        // like regualar sprites. That's why their textures are created separately
        SDL_Surface* textSurface = TTF_RenderText_Solid(Game::GetGameFont(), text->getText().c_str(), {0, 0, 0});

        // Create texture from surface
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, textSurface);
        SDL_FreeSurface(textSurface);

        // Calculate text size
        int w, h;
        TTF_SizeText(Game::GetGameFont(), text->getText().c_str(), &w, &h);
        object->size = Vector2(w, h);

        Sprite* newSprite = new Text(name, texture, object->zIndex);
        sprites[name] = newSprite;
    } 
    else // is normal object
    {
        auto foundTexturePair = textures.find(object->srcName);
        Texture* spriteTexture = NULL;
        if (foundTexturePair ==
            textures.end()) // this means the texture does not exist
        {
          std::cout << "Creating new texture for source: " << object->srcName
                    << std::endl;
          spriteTexture = new Texture(NULL, object->srcName);
          textures[object->srcName] = spriteTexture; // add new texture to map
        } else {
          spriteTexture = textures[object->srcName];
        }

        Sprite *newSprite = new Sprite(object->name, spriteTexture, object->zIndex);
        sprites[name] = newSprite;
    }
  }
}

// Cleanup
Graphics::~Graphics() {
  if (renderer) {
    SDL_DestroyRenderer(renderer);
    renderer = nullptr;
  }
  if (window) {
    SDL_DestroyWindow(window);
    window = nullptr;
  }
  SDL_Quit();
}

void Graphics::Init(const std::string &windowName, unsigned width,
                    unsigned height) {
  GetInstance().InitInternal(windowName, width, height);
}

SDL_Renderer *Graphics::GetRenderer() { return GetInstance().renderer; }

bool compareByZIndex(Sprite *a, Sprite *b) {
  return a->GetIndexZ() < b->GetIndexZ(); // ascending order of z-index
}

void Graphics::RenderInternal() {
  SDL_RenderClear(renderer);
  std::vector<Sprite *> spriteVector;
  for (const auto &pair : sprites) {

    if (State::GetAllObjects()[pair.first]->bIsVisible == false) {
      continue;
    }
    spriteVector.push_back(pair.second);
  }
  std::sort(spriteVector.begin(), spriteVector.end(), compareByZIndex);

  // render all sprites
  for (Sprite *sprite : spriteVector) {

    Object* correspondingObject = State::GetAllObjects()[sprite->GetName()];
    if(correspondingObject)
    {
      // get sprite (destination rectangle) position and size
      Vector2 spritePosition = State::GetAllObjects()[sprite->GetName()]->position;
      Vector2 spriteSize = State::GetAllObjects()[sprite->GetName()]->size;
      SDL_FRect destinationRectangle = Game::Vectors2ToSdlFRect(spritePosition, spriteSize);

      SDL_FPoint bottomRightCenter = {
          0.5f * destinationRectangle.w, // Bottom-right X
          0.5f * destinationRectangle.h  // Bottom-right Y
      };

      TextBox* textBox = dynamic_cast<TextBox*>(correspondingObject);
      if(!textBox)
      {
        // get source rectangle position and size
        Vector2 sourcePosition = State::GetAllObjects()[sprite->GetName()]->sourceRectanglePosition;
        Vector2 sourceSize = State::GetAllObjects()[sprite->GetName()]->sourceRectangleSize;
        SDL_Rect sourceRectangle =Game::Vectors2ToSdlRect(sourcePosition, sourceSize);

        sprite->Render(&sourceRectangle, &destinationRectangle,correspondingObject->rotation,
          &bottomRightCenter);
      }
      else
      {
        sprite->Render(NULL, &destinationRectangle,correspondingObject->rotation,
          &bottomRightCenter);
      }
    }
  }
  SDL_RenderPresent(renderer);
}

void Graphics::Render() { GetInstance().RenderInternal(); }