#ifndef COMMONFUNC_H
#define COMMONFUNC_H

#include<Windows.h>
#include<string>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_mixer.h>
#include<SDL_ttf.h>


static SDL_Window* g_window;
static SDL_Renderer* g_screen;
static SDL_Event g_event;

//screen
const int SCREEN_WIDTH = 1320;
const int SCREEN_HEIGHT = 688;
const int SCREEN_BPP = 32;

const int COLOR_KEY_R = 167;
const int COLOR_KEY_G = 175;
const int COLOR_KEY_B = 180;


const int RENDER_DRAW_COLOR = 0Xff;




#endif 