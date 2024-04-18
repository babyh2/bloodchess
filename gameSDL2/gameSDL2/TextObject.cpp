#include"stdafx.h"
#include "TextObject.h"


TextObject::TextObject() : BaseObject(), text_texture_(NULL) {}

TextObject::~TextObject() {
    // Giải phóng bộ nhớ
    SDL_DestroyTexture(text_texture_);
    text_texture_ = NULL;
}

bool TextObject::LoadText(TTF_Font* font, std::string text, SDL_Renderer* screen) {
    // Tạo surface từ text và font
	SDL_Surface* text_surface = TTF_RenderText_Solid(font, text.c_str(),Text_Color_);
    if (text_surface != NULL) {
        // Tạo texture từ surface
        text_texture_ = SDL_CreateTextureFromSurface(screen, text_surface);
        // Lấy kích thước của texture
        rect_.w = text_surface->w;
        rect_.h = text_surface->h;
        // Giải phóng surface sau khi đã sử dụng xong
        SDL_FreeSurface(text_surface);
    }
    return text_texture_ != NULL;
}

void TextObject::RenderText(SDL_Renderer* des, int x, int y) {
    SDL_Rect render_quad = { x, y, rect_.w, rect_.h };
    SDL_RenderCopy(des, text_texture_, NULL, &render_quad);
}

void TextObject::SetColor(const int& type) {
	if(type == RED)
	{
		SDL_Color color = {255, 0, 0, 255};
		Text_Color_ = color;
	}
	else if(type == GREEN)
	{
		SDL_Color color = {0, 255, 0, 255};
		Text_Color_ = color;
	}
	else if(type == BLUE)
	{
		SDL_Color color = {0, 0, 255, 255};
		Text_Color_ = color;
	}
	else if(type == YELLOW)
	{
		SDL_Color color = {255, 255, 0, 255};
		Text_Color_ = color;
	}
	else if(type == WHITE)
	{ 
		SDL_Color color = {255, 255, 255, 255};
		Text_Color_ = color;
	}
	else if(type == BLACK)
	{
		SDL_Color color = {0, 0, 0, 255};
		Text_Color_ = color;
	}
}
