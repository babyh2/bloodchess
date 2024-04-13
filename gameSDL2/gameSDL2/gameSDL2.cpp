// gameSDL2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include"BaseObject.h"
#include"Commonfunc.h"
#include"Game_map.h"
#include"MainObject.h"
#include"ImpTime.h"
#include"ThreatsObject.h"

BaseObject g_background;

// ham khoi tao cac gia tri trong bai
bool InitData();

// ham tai background

bool LoadBackground();
// ham giai phong cac doi tuong
void close();


int main(int argc, char* argv[])
{
	ImpTime fps_timer;


	if(InitData()==false) return -1;
	if(LoadBackground() == false) return -1;

	GameMap game_map;
	game_map.LoadMap("map/map01.dat");
	game_map.LoadTiles(g_screen);

	MainObject p_player;
	p_player.LoadImg("img/sieunhan_right.jpg", g_screen);

	ThreatsObject dauchamhoi;
	dauchamhoi.LoadImg("img/chamhoi.jpg",g_screen);

	// tao mot vong lap vo han de load tam anh 
	bool is_quit = false;
	while(!is_quit){
		fps_timer.start();

		while(SDL_PollEvent(&g_event) !=0)
		{
			if(g_event.type == SDL_QUIT ) is_quit = true;
			p_player.HandelInputAction(g_event, g_screen);
		}
		SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR,
			RENDER_DRAW_COLOR,RENDER_DRAW_COLOR);
        // lam moi du lieu man hinh xoa man hinh 
		SDL_RenderClear(g_screen);
		// ham dua anh ra man hinh
		g_background.Render(g_screen, NULL);
		// ham update lai man hinh
		
		Map map_data= game_map.getMap();

		p_player.SetMapXY(map_data.start_x_, map_data.start_y_);


		p_player.DoPlayer(map_data);
		p_player.Show(g_screen);

		game_map.SetMap(map_data);
		game_map.DrawMap(g_screen);

		dauchamhoi.Show(g_screen);

		SDL_RenderPresent(g_screen);
		int real_imp_time = fps_timer.get_ticks(); // lay thoi gian da choi
		int time_on_frame = 1000/FRAME_PER_SECOND;//MS

		if(real_imp_time < time_on_frame){
			int delay_time = time_on_frame - real_imp_time;
			
			if(delay_time>=0) SDL_Delay(delay_time);// de chuong trinh chay nhanh hon thi tang fps len
		}
	}
	close();
	return 0;
}


bool InitData()
	{
	bool success = true;
	int ret = SDL_Init(SDL_INIT_VIDEO);// thiet lap moi truong ban dau cho sdl
	if(ret < 0) return false;
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY,"1");
	// tao cua so window cho project game
	g_window = SDL_CreateWindow("blood chess", SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if(g_window == NULL){
			success = false;
		}
		else {
			g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
			if(g_screen == NULL){
				success =false;
			}
			else {
				// dung de ve do hoa
				SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR,
					RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
				int imgFlg= IMG_INIT_PNG;
				if(!(IMG_Init(imgFlg) && imgFlg)){
					success = false;
				}
			}
		}
		return success;
}

bool LoadBackground(){

	//ham load tam anh len
	bool ret = g_background.LoadImg("dennham.jpg", g_screen);
	if(ret == false ) return false;
	return true;
}

void close(){
	// tat tat ca cac hd va dua toan bo con tro ve null
	g_background.Free();
	SDL_DestroyRenderer(g_screen);
	g_screen = NULL;
	SDL_DestroyWindow(g_window);
	g_window=NULL;
	IMG_Quit();
	SDL_Quit();
}