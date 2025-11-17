#include "stdafx.h"
#include "ResourceManager.h"

#include <fstream>

bool ResourceManager::LoadWordsList(const std::string &path)
{
    words_.clear();
    std::ifstream file(path);
    if (!file.is_open())
        return false;
    std::string w;
    while (std::getline(file, w))
    {
        // trim spaces
        while (!w.empty() && isspace(w.back()))
            w.pop_back();
        while (!w.empty() && isspace(w.front()))
            w.erase(w.begin());
        if (!w.empty())
            words_.push_back(w);
    }
    file.close();
    return !words_.empty();
}

std::string ResourceManager::GetRandomWord() const
{
    if (words_.empty())
        return std::string();
    unsigned seed = unsigned(SDL_GetTicks() ^ SDL_GetPerformanceCounter());
    srand(seed);
    int idx = rand() % static_cast<int>(words_.size());
    return words_[idx];
}
