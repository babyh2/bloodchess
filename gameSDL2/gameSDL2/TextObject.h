#ifndef TEXTOBJECT_H
#define TEXTOBJECT_H

#include "BaseObject.h"
#include "Commonfunc.h"

class TextObject : public BaseObject {
public:
    TextObject();
    ~TextObject();

    enum Color {
        RED = 1,
        GREEN = 2,
        BLUE = 3,
        YELLOW = 4,
        WHITE = 5,
        BLACK = 6,
    };

    bool LoadText(TTF_Font* font, std::string text, SDL_Renderer* screen);
    void RenderText(SDL_Renderer* des, int x, int y);
    void SetColor(const int& type); // Thêm phương thức SetColor

private:
    SDL_Texture* text_texture_;
	SDL_Color Text_Color_;
};

#endif // TEXTOBJECT_H
