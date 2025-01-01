#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include "Math/Vector2.h"
#include "State/Object.h"
#include <SDL2/SDL_ttf.h>

class TextBox : public Object {
private:
    std::string text;
    TTF_Font* font;

public:
    TextBox(const std::string& newName, Vector2 startingPosition, Vector2 startingSize,
         int zIndexNew, const std::string &text, TTF_Font* font, bool bCollidesNew=false, bool bOverlapsNew=true, 
         bool bIsVisibleNew=true, float rotation = 0.0);

    void setText(const std::string& newText) {
        text = newText;
    }

    std::string getText() const {
        return text;
    }

    void Begin() {};

    TTF_Font* getFont() { return font; };
    void Update(float deltatime) {};

};
