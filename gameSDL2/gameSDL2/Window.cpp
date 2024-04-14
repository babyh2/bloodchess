#include "stdafx.h"
#include "Window.h"

Window::Window() :
    mWindow(nullptr),
    mRenderer(nullptr),
    mIsVisible(false),
    mIsInGame(false),
    mTitle(""),
    mWidth(0),
    mHeight(0)
{}

Window::~Window() {
    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);
    SDL_Quit();
}

bool Window::init(const std::string& title, int width, int height) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
        return false;
    }

    mWindow = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    if (mWindow == nullptr) {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        return false;
    }

    mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (mRenderer == nullptr) {
        SDL_Log("Failed to create renderer: %s", SDL_GetError());
        return false;
    }

    mTitle = title;
    mWidth = width;
    mHeight = height;

    return true;
}

SDL_Texture* Window::loadImg(const std::string& path)
{
	SDL_Surface* surface = IMG_Load(path.c_str());
    if (!surface) {
        SDL_Log("Failed to load image: %s", SDL_GetError());
        return nullptr;
    }

    // Tạo texture từ surface
    SDL_Texture* texture = SDL_CreateTextureFromSurface(mRenderer, surface);
    SDL_FreeSurface(surface); // Giải phóng surface sau khi tạo texture
    if (!texture) {
        SDL_Log("Failed to create texture: %s", SDL_GetError());
        return nullptr;
    }

    return texture;
}

void Window::handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                mIsVisible = false;
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (!mIsInGame) {
                    // Nếu đang ở trạng thái menu và chuột được click, chuyển sang trạng thái game
                    mIsInGame = true;
                }
                break;
        }
    }
}

void Window::render() {
    SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);
    SDL_RenderClear(mRenderer);

    SDL_Rect loadBG = {0, 0, 748, 503};
    SDL_Texture* loadBackground = loadImg("bs-1.png");
    if (loadBackground) {
        SDL_RenderCopy(mRenderer, loadBackground, nullptr, &loadBG);
        SDL_DestroyTexture(loadBackground); // Giải phóng texture sau khi sử dụng
    } else {
        SDL_Log("Failed to load background image");
    }

    if (!mIsInGame) {
        // Nếu đang ở trạng thái menu, vẽ menu
        renderMenu();
    } else {
        // Nếu đang ở trạng thái game, vẽ game
        renderGame();
    }

    SDL_RenderPresent(mRenderer);
}

void Window::show(bool visible) {
    mIsVisible = visible;
}

void Window::renderMenu() {
    // Vẽ chữ "Bắt đầu" ở giữa cửa sổ
    TTF_Font* font = TTF_OpenFont("arial.ttf", 24);
    if (font == nullptr) {
        SDL_Log("Failed to load font: %s", TTF_GetError());
        return;
    }

    SDL_Color textColor = {0, 0, 0, 255};
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, "Bắt đầu", textColor);
    if (textSurface == nullptr) {
        SDL_Log("Failed to render text surface: %s", TTF_GetError());
        TTF_CloseFont(font);
        return;
    }

    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(mRenderer, textSurface);
    if (textTexture == nullptr) {
        SDL_Log("Failed to create text texture: %s", SDL_GetError());
        SDL_FreeSurface(textSurface);
        TTF_CloseFont(font);
        return;
    }

    SDL_Rect textRect;
    textRect.x = mWidth / 2 - textSurface->w / 2;
    textRect.y = mHeight / 2 - textSurface->h / 2;
    textRect.w = textSurface->w;
    textRect.h = textSurface->h;

    SDL_RenderCopy(mRenderer, textTexture, nullptr, &textRect);

    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
    TTF_CloseFont(font);
}

void Window::renderGame() {
    // Vẽ trò chơi tại đây
}
