#ifndef COMMONFUNC_H
#define COMMONFUNC_H

#include<Windows.h>
#include<string>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_mixer.h>
#include<SDL_ttf.h>
#include<fstream>
#include<vector>

#define BLANK_TILE 2
#define BLANK_TAIXIU 1

static SDL_Window* g_window;
static SDL_Renderer* g_screen;
static SDL_Event g_event;

//screen
const int FRAME_PER_SECOND = 50;
const int SCREEN_WIDTH = 1120;
const int SCREEN_HEIGHT = 840;
const int SCREEN_BPP = 32;

const int COLOR_KEY_R = 167;
const int COLOR_KEY_G = 175;
const int COLOR_KEY_B = 180;

const int SCREEN_TWIDTH = 748;
const int SCREEN_THEIGHT = 503;

const int RENDER_DRAW_COLOR = 0Xff;

#define TILE_SIZE 40 // chieu dai va rong cua mot o map
#define MAX_MAP_X 210 
#define MAX_MAP_Y 21
typedef struct Map{
	int start_x_; // vi tri bat dau cua o map
	int start_y_; // vi tri bat dau cua o map

	int max_x_; // chi so cua o trong map(o thu bao nhieu)
	int max_y_;



	int tile[MAX_MAP_Y][MAX_MAP_X];
	char* file_name_;
};

typedef struct Input
{
	int left_;
	int right_;
	int up_;
	int down_;

};

#endif 