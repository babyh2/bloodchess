#ifndef GAME_UTILS_H
#define GAME_UTILS_H

#include "Commonfunc.h"
#include "TextObject.h"

// Utility functions to reduce code duplication
namespace GameUtils
{
    // Render text centered on screen
    void RenderCenteredText(SDL_Renderer *screen, TTF_Font *font,
                            const std::string &text, SDL_Color color, int y_offset = 0);

    // Show temporary message (non-blocking, responsive)
    void ShowMessage(SDL_Renderer *screen, TTF_Font *font,
                     const std::string &text, SDL_Color color,
                     int duration_ms = 3000);

    // Render score/stats display
    void RenderScoreDisplay(SDL_Renderer *screen, TTF_Font *font,
                            const std::string &label, int value, int x, int y);
}

#endif // GAME_UTILS_H
