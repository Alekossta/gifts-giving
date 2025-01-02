#include "State/TextBox.h"
#include "Game.h"
#include "Graphics/Graphics.h"
#include "Graphics/Text.h"

TextBox::TextBox(const std::string& newName, Vector2 startingPosition, Vector2 startingSize,
int zIndexNew, const std::string &text , bool bIsVisibleNew, float rotation)
: Object(newName, startingPosition, startingSize, "", {}, {}, zIndexNew, 
false, false, bIsVisibleNew, rotation),text(text){

}

void TextBox::setText(const std::string& newText)
{
    Text* text = dynamic_cast<Text*>(Graphics::GetSprites()[name]);
    if(text)
    {
        SDL_Color defaultColor {0,0,0};
        text->RegenerateTexture(defaultColor, newText);
    }
}