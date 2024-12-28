#include "State/Button.h"
#include "SDL2/SDL.h"
#include "State/State.h"

Button::Button(const std::string& buttonName, Vector2 position, Vector2 startingSize,
        const std::string& newSrcName, Vector2 newSourceRectanglePosition, Vector2 newSourceRectangleSize,
        int zIndexNew): Object(buttonName, position, startingSize, true, newSrcName,newSourceRectanglePosition,
 newSourceRectangleSize, zIndexNew)