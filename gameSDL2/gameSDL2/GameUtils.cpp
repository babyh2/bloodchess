#include "stdafx.h"
#include "GameUtils.h"
#include "GameConfig.h"

namespace GameUtils
{
    void RenderCenteredText(SDL_Renderer *screen, TTF_Font *font,
                            const std::string &text, SDL_Color color, int y_offset)
    {
        SDL_Surface *surface = TTF_RenderText_Solid(font, text.c_str(), color);
        if (!surface)
            return;

        SDL_Texture *texture = SDL_CreateTextureFromSurface(screen, surface);
        if (!texture)
        {
            SDL_FreeSurface(surface);
            return;
        }

        int text_w = surface->w;
        int text_h = surface->h;
        SDL_FreeSurface(surface);

        int x = (SCREEN_WIDTH - text_w) / 2;
        int y = (SCREEN_HEIGHT - text_h) / 2 + y_offset;

        SDL_Rect dest = {x, y, text_w, text_h};
        SDL_RenderCopy(screen, texture, nullptr, &dest);
        SDL_DestroyTexture(texture);
    }

    void ShowMessage(SDL_Renderer *screen, TTF_Font *font,
                     const std::string &text, SDL_Color color,
                     int duration_ms)
    {
        SDL_Surface *surface = TTF_RenderText_Solid(font, text.c_str(), color);
        if (!surface)
            return;

        SDL_Texture *texture = SDL_CreateTextureFromSurface(screen, surface);
        if (!texture)
        {
            SDL_FreeSurface(surface);
            return;
        }

        int text_w = surface->w;
        int text_h = surface->h;
        SDL_FreeSurface(surface);

        SDL_Rect dest = {75, 30, text_w, text_h};

        Uint32 start = SDL_GetTicks();
        bool running = true;

        while (running)
        {
            SDL_Event e;
            while (SDL_PollEvent(&e))
            {
                if (e.type == SDL_QUIT)
                {
                    running = false;
                }
                // Allow ESC to skip message
                if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)
                {
                    running = false;
                }
            }

            SDL_RenderCopy(screen, texture, nullptr, &dest);
            SDL_RenderPresent(screen);

            if (SDL_GetTicks() - start >= static_cast<Uint32>(duration_ms))
            {
                running = false;
            }

            SDL_Delay(16); // ~60 FPS
        }

        SDL_DestroyTexture(texture);
    }

    void RenderScoreDisplay(SDL_Renderer *screen, TTF_Font *font,
                            const std::string &label, int value, int x, int y)
    {
        TextObject text_label;
        text_label.SetColor(TextObject::RED);
        text_label.LoadText(font, label, screen);
        text_label.RenderText(screen, x, y);

        TextObject text_value;
        text_value.SetColor(TextObject::RED);
        text_value.LoadText(font, std::to_string(value), screen);
        text_value.RenderText(screen, x + 80, y);
    }
}
