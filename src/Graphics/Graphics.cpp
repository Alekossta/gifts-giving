#include "Graphics/Graphics.h"
#include "Game.h"
#include "General.h"
#include "Graphics/Texture.h"
#include "State/State.h"
#include "State/TextBox.h"
#include "Graphics/Text.h"
#include <algorithm>
#include <iostream>
#include <vector>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

Graphics &Graphics::GetInstance() {
  // Avoid global declaration of instance before first call of getInstance
  static Graphics instance;
  return instance;
}

void Graphics::createTextSprite(const std::string& name, TextBox* text) {
    Sprite* newSprite = new Text(name, text->getText(), text->color, text->zIndex);
    sprites[name] = newSprite;
}

void Graphics::createSprite(const std::string& name, Object* object) {
    auto foundTexturePair = textures.find(object->srcName);
    Texture* spriteTexture = NULL;
    if (foundTexturePair == textures.end()) // this means the texture does not exist
    {
      SDL_Surface* tempSurface = IMG_Load(object->srcName.c_str());
      if(!tempSurface)
      {
          std::cout << "Error opening image: " << object->srcName.c_str() << std::endl;
          std::cout << IMG_GetError() << std::endl;
      }
      SDL_Texture* sdlTexture = SDL_CreateTextureFromSurface(Graphics::GetRenderer(), tempSurface);
      SDL_FreeSurface(tempSurface);

      spriteTexture = new Texture(sdlTexture, object->srcName);
      textures[object->srcName] = spriteTexture;
    } 
    else
    {
      spriteTexture = textures[object->srcName];
    }

    Sprite *newSprite = new Sprite(object->name, spriteTexture, object->zIndex);
    sprites[name] = newSprite;
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

  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

  for (const auto &[name, object] : State::GetAllObjects()) 
  {   
    TextBox* text = dynamic_cast<TextBox*>(object);    
    if (text) 
    {
        createTextSprite(name, text);
    } 
    else // is normal object
    {
        createSprite(name, object);
    }
  }
}

void Graphics::DestroySpriteInternal(const std::string& name)
{
  if (sprites.find(name) == sprites.end()) return;
  Sprite* spriteToDestroy = sprites[name];
  if(spriteToDestroy)
  {
    sprites.erase(name);
    //delete spriteToDestroy;
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

    if (State::GetAllObjects()[pair.first]->bIsVisible == false || (State::GetBDisplayIntro() && !startsWith(pair.first, "intro"))) {
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