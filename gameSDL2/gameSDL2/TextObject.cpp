
#include"stdafx.h"
#include "TextObject.h"


TextObject::TextObject(SDL_Renderer* renderer, TTF_Font* font, const std::string& text, int x, int y)
{
    mRenderer=renderer; 
	mFont=font;
	mTexture=nullptr;
	mColor={255, 255, 255, 255};
    setText(text);
    setPosition(x, y);
}

TextObject::~TextObject() {
    if (mTexture != nullptr) {
        SDL_DestroyTexture(mTexture);
        mTexture = nullptr;
    }
}

void TextObject::setText(const std::string& text) {
    SDL_Surface* textSurface = TTF_RenderText_Solid(mFont, text.c_str(), mColor);
    if (textSurface == nullptr) {
        
        return;
    }

    if (mTexture != nullptr) {
        SDL_DestroyTexture(mTexture);
        mTexture = nullptr;
    }

    mTexture = SDL_CreateTextureFromSurface(mRenderer, textSurface);
    if (mTexture == nullptr) {
        
        SDL_FreeSurface(textSurface);
        return;
    }

    mRect.w = textSurface->w;
    mRect.h = textSurface->h;

    SDL_FreeSurface(textSurface);
}

void TextObject::setPosition(int x, int y) {
    mRect.x = x;
    mRect.y = y;
}

void TextObject::setColor(const SDL_Color& color) {
    mColor = color;
    setText("");
}

void TextObject::render(SDL_Renderer* renderer) {
    SDL_RenderCopy(renderer, mTexture, nullptr, &mRect);
}

bool TextObject::isMouseOver(int mouseX, int mouseY) {
    return (mouseX >= mRect.x && mouseX <= mRect.x + mRect.w && mouseY >= mRect.y && mouseY <= mRect.y + mRect.h);
}
