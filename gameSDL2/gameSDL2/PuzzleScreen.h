#ifndef PUZZLE_SCREEN_H
#define PUZZLE_SCREEN_H

#include "Commonfunc.h"
#include "ResourceManager.h"

struct PuzzleResult
{
    bool solved;
    int awardedPoints;
};

class PuzzleScreen
{
public:
    PuzzleScreen(SDL_Renderer *renderer, TTF_Font *font);
    // Run puzzle for a random word
    PuzzleResult RunPuzzle(const std::string &word);

private:
    SDL_Renderer *renderer_;
    TTF_Font *font_;

    void RenderUI(const std::string &word, const std::vector<char> &displayChars, int time_left, int points);
    void RenderCenteredText(const std::string &text, int y_offset, SDL_Color color);
};

#endif // PUZZLE_SCREEN_H
