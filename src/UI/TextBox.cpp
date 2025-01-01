#include "UI/TextBox.h"

TextBox::TextBox(const std::string& newName, Vector2 startingPosition, Vector2 startingSize,
                 int zIndexNew, const std::string &text, TTF_Font* font, bool bCollidesNew, 
                 bool bOverlapsNew, bool bIsVisibleNew, float rotation)
    : Object(newName, startingPosition, startingSize, "", {}, {}, zIndexNew, 
             bCollidesNew, bOverlapsNew, bIsVisibleNew, rotation),
      text(text), font(font) {}
