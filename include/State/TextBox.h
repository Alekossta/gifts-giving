#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include "Math/Vector2.h"
#include "State/Object.h"

class TextBox : public Object {
private:
    std::string text;
    Object* textBackground;
public:
    TextBox(const std::string& newName, Vector2 startingPosition, Vector2 startingSize,
         int zIndexNew, const std::string &text , Object* textBackground, bool bIsVisibleNew=true, float rotation = 0.0);

    void setText(const std::string& newText);
    std::string getText() const {return text; }
    void setBIsVisible(bool newBIsVisible) override { 
        bIsVisible = newBIsVisible; 
        if (textBackground) {
            textBackground->bIsVisible = newBIsVisible; 
        }
    };
};