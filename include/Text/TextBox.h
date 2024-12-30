#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

class TextBox {
private:
    SDL_Rect box;
    SDL_Color boxColor;
    SDL_Color textColor;
    TTF_Font* font;
    std::string text;
    SDL_Texture* textTexture;

public:
    TextBox(SDL_Renderer* renderer, TTF_Font* font, int x, int y, int w, int h,
                SDL_Color boxColor = {255, 255, 255, 255}, SDL_Color textColor = {0, 0, 0, 255})
        : font(font), boxColor(boxColor), textColor(textColor),
        textTexture(nullptr) {
        box = {x, y, w, h};
    }

    ~TextBox() {
        if (textTexture) {
            SDL_DestroyTexture(textTexture);
        }
    }

    void setText(const std::string& newText) {
        text = newText;
    }

    std::string getText() const {
        return text;
    }

};
