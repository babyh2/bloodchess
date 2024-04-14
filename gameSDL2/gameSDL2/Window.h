#ifndef WINDOW_H
#define WINDOW_H

#include "Commonfunc.h"

class Window {
public:
    Window();
    ~Window();

    bool init(const std::string& title, int width, int height);
    void handleEvents();
    void render();
    void show(bool visible); // Hiển thị hoặc ẩn cửa sổ
	SDL_Texture* loadImg(const std::string& path);

private:
    SDL_Window* mWindow;
    SDL_Renderer* mRenderer;
    bool mIsVisible;
    bool mIsInGame;
    std::string mTitle;
    int mWidth;
    int mHeight;

    void renderMenu();
    void renderGame();

};

#endif
