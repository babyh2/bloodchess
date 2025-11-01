#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include "Commonfunc.h"
#include <map>
#include <string>

// Singleton class to manage all game resources (textures, fonts)
// Load once, reuse many times - avoid repeated I/O
class ResourceManager
{
public:
    static ResourceManager &GetInstance();

    // Initialize and load all resources
    bool LoadAllResources(SDL_Renderer *renderer);

    // Get cached resources
    SDL_Texture *GetTexture(const std::string &name);
    TTF_Font *GetFont(const std::string &name);

    // Cleanup
    void FreeAllResources();

private:
    ResourceManager() {}
    ~ResourceManager() { FreeAllResources(); }

    // Prevent copying
    ResourceManager(const ResourceManager &) = delete;
    ResourceManager &operator=(const ResourceManager &) = delete;

    std::map<std::string, SDL_Texture *> textures_;
    std::map<std::string, TTF_Font *> fonts_;

    SDL_Texture *LoadTexture(const std::string &path, SDL_Renderer *renderer);
    TTF_Font *LoadFont(const std::string &path, int size);
};

#endif // RESOURCE_MANAGER_H
