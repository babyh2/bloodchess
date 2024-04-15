#ifndef TEXTOBJECT_H
#define TEXTOBJECT_H

#include"Commonfunc.h"

class TextObject {
public:
    TextObject(SDL_Renderer* renderer, TTF_Font* font, const std::string& text, int x, int y);
    ~TextObject();

    void setText(const std::string& text);
    void setPosition(int x, int y);
    void setColor(const SDL_Color& color);

    void render(SDL_Renderer* renderer);

    bool isMouseOver(int mouseX, int mouseY);

private:
    SDL_Renderer* mRenderer;
    TTF_Font* mFont;
    SDL_Texture* mTexture;
    SDL_Rect mRect;
    SDL_Color mColor;
};

#endif // TEXTOBJECT_H
