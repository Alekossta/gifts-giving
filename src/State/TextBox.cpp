#include "State/TextBox.h"
#include "Game.h"

TextBox::TextBox(const std::string& newName, Vector2 startingPosition, Vector2 startingSize,
int zIndexNew, const std::string &text , bool bIsVisibleNew=true, float rotation = 0.0)
: Object(newName, startingPosition, startingSize, "", {}, {}, zIndexNew, 
false, false, bIsVisibleNew, rotation),text(text){

}

void setText(const std::string& newText)
{
    Graphics::
}