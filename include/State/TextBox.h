#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include "Math/Vector2.h"
#include "State/Object.h"

class TextBox : public Object {
private:
    std::string text;
    
public:
    TextBox(const std::string& newName, Vector2 startingPosition, Vector2 startingSize,
         int zIndexNew, const std::string &text, bool bIsVisibleNew=true, SDL_Color color = {0, 0, 0},float rotation = 0.0);
    SDL_Color color;
    void setText(const std::string& newText);
    std::string getText() const { return text; }
};