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
    SDL_Texture* loadBackground = loadImg("trang.jpg");
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
   SDL_Surface* imageSurface = IMG_Load("img/batdau.png");
    if (imageSurface == nullptr) {
        SDL_Log("Failed to load image: %s", IMG_GetError());
        return;
    }

    SDL_Texture* imageTexture = SDL_CreateTextureFromSurface(mRenderer, imageSurface);
    if (imageTexture == nullptr) {
        SDL_Log("Failed to create image texture: %s", SDL_GetError());
        SDL_FreeSurface(imageSurface);
        return;
    }

    SDL_Rect imageRect;
    imageRect.x = mWidth / 2 - imageSurface->w / 2;
    imageRect.y = mHeight / 2 - imageSurface->h / 2;
    imageRect.w = imageSurface->w;
    imageRect.h = imageSurface->h;

    SDL_RenderCopy(mRenderer, imageTexture, nullptr, &imageRect);

    SDL_FreeSurface(imageSurface);
    SDL_DestroyTexture(imageTexture);

}

void Window::renderGame() {
    // Vẽ trò chơi tại đây
}


