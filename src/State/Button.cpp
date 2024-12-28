#include "State/Button.h"
#include "SDL2/SDL.h"
#include "State/State.h"

Button::Button(const std::string& buttonName, Vector2 position, Vector2 startingSize, bool bCollidesNew,
        const std::string& newSrcName, Vector2 newSourceRectanglePosition, Vector2 newSourceRectangleSize,
        int zIndexNew, bool bIsVisibleNew, bool bIsPressed, int opensDoorCode): Object(buttonName, position, startingSize, bCollidesNew, newSrcName, newSourceRectanglePosition,
        newSourceRectangleSize, zIndexNew, bIsVisibleNew), bIsPressed(bIsPressed), opensDoorCode(opensDoorCode) 
{

}

void Button::Update(float deltatime) {

}
void Button::Begin() {

}