#include "stdafx.h"
#include "ResourceManager.h"

ResourceManager &ResourceManager::GetInstance()
{
    static ResourceManager instance;
    return instance;
}

SDL_Texture *ResourceManager::LoadTexture(const std::string &path, SDL_Renderer *renderer)
{
    SDL_Surface *surface = IMG_Load(path.c_str());
    if (!surface)
    {
        return nullptr;
    }

    // Apply color key for transparency
    SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, COLOR_KEY_R, COLOR_KEY_G, COLOR_KEY_B));

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    return texture;
}

TTF_Font *ResourceManager::LoadFont(const std::string &path, int size)
{
    TTF_Font *font = TTF_OpenFont(path.c_str(), size);
    return font;
}

bool ResourceManager::LoadAllResources(SDL_Renderer *renderer)
{
    if (!renderer)
        return false;

    // Load all textures once
    textures_["background"] = LoadTexture("dennham.jpg", renderer);
    textures_["menu_main"] = LoadTexture("menuchinh.png", renderer);
    textures_["menu_shop"] = LoadTexture("shop.png", renderer);
    textures_["menu_win"] = LoadTexture("win.png", renderer);
    textures_["menu_loss"] = LoadTexture("loss.png", renderer);
    textures_["menu_rules"] = LoadTexture("RULES_OF_THE_GAME.png", renderer);

    // Player sprites
    textures_["player_left"] = LoadTexture("img/sieunhan_left.jpg", renderer);
    textures_["player_right"] = LoadTexture("img/sieunhan_right.jpg", renderer);
    textures_["player_up"] = LoadTexture("img/sieunhan_up.jpg", renderer);
    textures_["player_down"] = LoadTexture("img/sieunhan_down.jpg", renderer);
    textures_["player_alt"] = LoadTexture("img/joker.png", renderer);

    // Map tiles (0-19)
    for (int i = 0; i < MAX_TILES; i++)
    {
        char filename[30];
        sprintf_s(filename, "map/%d.jpg", i);

        // Check if file exists before loading
        FILE *fp = nullptr;
        fopen_s(&fp, filename, "rb");
        if (fp)
        {
            fclose(fp);
            std::string key = "tile_" + std::to_string(i);
            textures_[key] = LoadTexture(filename, renderer);
        }
    }

    // Load fonts
    fonts_["main"] = LoadFont("Dreams.ttf", 30);
    if (!fonts_["main"])
    {
        return false;
    }

    // Load words list for puzzles
    if (!LoadWordsList("wordsEn.txt"))
    {
        SDL_Log("Warning: words list not loaded");
    }

    return true;
}

SDL_Texture *ResourceManager::GetTexture(const std::string &name)
{
    auto it = textures_.find(name);
    if (it != textures_.end())
    {
        return it->second;
    }
    return nullptr;
}

TTF_Font *ResourceManager::GetFont(const std::string &name)
{
    auto it = fonts_.find(name);
    if (it != fonts_.end())
    {
        return it->second;
    }
    return nullptr;
}

void ResourceManager::FreeAllResources()
{
    // Free all textures
    for (auto &pair : textures_)
    {
        if (pair.second)
        {
            SDL_DestroyTexture(pair.second);
        }
    }
    textures_.clear();

    // Free all fonts
    for (auto &pair : fonts_)
    {
        if (pair.second)
        {
            TTF_CloseFont(pair.second);
        }
    }
    fonts_.clear();
}
