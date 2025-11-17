#include "stdafx.h"
#include "PuzzleScreen.h"
#include "TextObject.h"
#include "GameUtils.h"

PuzzleScreen::PuzzleScreen(SDL_Renderer *renderer, TTF_Font *font)
    : renderer_(renderer), font_(font)
{
}

void PuzzleScreen::RenderCenteredText(const std::string &text, int y_offset, SDL_Color color)
{
    SDL_Surface *surface = TTF_RenderText_Solid(font_, text.c_str(), color);
    if (!surface)
        return;
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer_, surface);
    int w = surface->w;
    int h = surface->h;
    SDL_FreeSurface(surface);
    int x = (SCREEN_WIDTH - w) / 2;
    int y = (SCREEN_HEIGHT - h) / 2 + y_offset;
    SDL_Rect dest = {x, y, w, h};
    SDL_RenderCopy(renderer_, texture, NULL, &dest);
    SDL_DestroyTexture(texture);
}

void PuzzleScreen::RenderUI(const std::string &word, const std::vector<char> &displayChars, int time_left, int points)
{
    // Render background dim
    SDL_SetRenderDrawBlendMode(renderer_, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 200);
    SDL_Rect full = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    SDL_RenderFillRect(renderer_, &full);

    // Title
    SDL_Color white = {255, 255, 255, 255};
    RenderCenteredText("Guess the Word", -120, white);

    // Display points and timer
    TextObject t;
    t.SetColor(TextObject::WHITE);
    std::string pts = "Points: " + std::to_string(points);
    t.LoadText(font_, pts, renderer_);
    t.RenderText(renderer_, SCREEN_WIDTH - 200, 40);

    std::string timer_text = "Time left: " + std::to_string(time_left);
    TextObject t2;
    t2.SetColor(TextObject::WHITE);
    t2.LoadText(font_, timer_text, renderer_);
    t2.RenderText(renderer_, 40, 40);

    // Draw boxes and characters in center
    int len = static_cast<int>(displayChars.size());
    int boxSize = 48;
    int gap = 12;
    int totalW = len * boxSize + (len - 1) * gap;
    int startX = (SCREEN_WIDTH - totalW) / 2;
    int y = SCREEN_HEIGHT / 2 - boxSize / 2;

    SDL_SetRenderDrawColor(renderer_, 255, 255, 255, 255);
    for (int i = 0; i < len; i++)
    {
        SDL_Rect r = {startX + i * (boxSize + gap), y, boxSize, boxSize};
        SDL_RenderDrawRect(renderer_, &r);
        if (displayChars[i] != '\0')
        {
            std::string s(1, displayChars[i]);
            TextObject ch;
            ch.SetColor(TextObject::WHITE);
            ch.LoadText(font_, s, renderer_);
            int cw, chh;
            ch.GetSize(cw, chh);
            ch.RenderText(renderer_, r.x + (boxSize - cw) / 2, r.y + (boxSize - chh) / 2);
        }
    }

    // Also show hint: Press Enter to submit
    TextObject hint;
    hint.SetColor(TextObject::YELLOW);
    hint.LoadText(font_, "Type and press ENTER to submit. Press ESC to cancel.", renderer_);
    hint.RenderText(renderer_, startX, y + boxSize + 30);
}

PuzzleResult PuzzleScreen::RunPuzzle(const std::string &word)
{
    PuzzleResult res{false, 0};
    if (word.empty())
        return res;
    int len = static_cast<int>(word.size());
    int time_ms = len * 5 * 1000; // 5 sec per letter
    int points = len;

    // display char array: initially nulls
    std::vector<char> displayChars(len, '\0');
    std::string currentInput;
    std::vector<int> revealed(len, 0);

    Uint32 start = SDL_GetTicks();
    Uint32 lastReveal = start;

    SDL_StartTextInput();
    bool running = true;
    while (running)
    {
        SDL_Event e;
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                running = false;
                break;
            }
            else if (e.type == SDL_KEYDOWN)
            {
                if (e.key.keysym.sym == SDLK_ESCAPE)
                {
                    running = false;
                    break;
                }
                else if (e.key.keysym.sym == SDLK_RETURN || e.key.keysym.sym == SDLK_KP_ENTER)
                {
                    // submit
                    // trim and lowercase currentInput
                    std::string guess = currentInput;
                    for (auto &c : guess)
                        c = tolower(c);
                    std::string target = word;
                    for (auto &c : target)
                        c = tolower(c);
                    if (guess == target)
                    {
                        res.solved = true;
                        res.awardedPoints = points;
                        running = false;
                        break;
                    }
                    else
                    {
                        // Wrong: Let the player continue, maybe show small message
                        // We deduct nothing until time out
                    }
                }
                else if (e.key.keysym.sym == SDLK_BACKSPACE)
                {
                    if (!currentInput.empty())
                        currentInput.pop_back();
                }
            }
            else if (e.type == SDL_TEXTINPUT)
            {
                char ch = e.text.text[0];
                if (isalpha(ch) && static_cast<int>(currentInput.size()) < len)
                {
                    currentInput.push_back(ch);
                }
            }
        }

        Uint32 now = SDL_GetTicks();
        int elapsed = (now - start);
        int time_left = std::max(0, time_ms - elapsed) / 1000;

        // Reveal letter every 5 seconds
        if ((now - lastReveal) >= 5000 && points > 0)
        {
            // pick random unrevealed index
            std::vector<int> available;
            for (int i = 0; i < len; i++)
                if (!revealed[i])
                    available.push_back(i);
            if (!available.empty())
            {
                unsigned seed = (unsigned)(now ^ SDL_GetTicks());
                srand(seed);
                int idx = available[rand() % available.size()];
                revealed[idx] = 1;
                displayChars[idx] = word[idx];
                points = std::max(0, points - 1);
            }
            lastReveal = now;
        }

        // Copy currentInput to display positions (left-aligned)
        for (int i = 0; i < len; i++)
        {
            if (!revealed[i])
            {
                if (i < static_cast<int>(currentInput.size()))
                    displayChars[i] = currentInput[i];
                else
                    displayChars[i] = '\0';
            }
        }

        SDL_RenderClear(renderer_);
        // Optionally draw the game background or previous state; for now a dark overlay
        RenderUI(word, displayChars, time_left, points);
        SDL_RenderPresent(renderer_);

        if (elapsed >= time_ms)
        {
            running = false;
            res.solved = false;
            res.awardedPoints = 0;
            break;
        }
        SDL_Delay(16);
    }
    SDL_StopTextInput();
    return res;
}
