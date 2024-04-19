// gameSDL2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include"BaseObject.h"
#include"Commonfunc.h"
#include"Game_map.h"
#include"MainObject.h"
#include"ImpTime.h"
#include"TextObject.h"


TTF_Font* g_font_text = NULL;
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
	Map map_data = game_map.getMap();
	game_map.random_vatcan(map_data);

	MainObject p_player;
	p_player.LoadImg("img/sieunhan_right.jpg", g_screen);

	TextObject mark_game;
	mark_game.SetColor(TextObject::RED);
	

	int mark_value = 100;
	// tao mot vong lap vo han de load tam anh 
	bool is_quit = false;
	while(!is_quit){
		
		fps_timer.start();

		while(SDL_PollEvent(&g_event) !=0)
		{
			if(g_event.type == SDL_QUIT ) {
				is_quit = true;
				//mark_value =100;
			}
			p_player.HandelInputAction(g_event, g_screen);
		}
		SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR,
			RENDER_DRAW_COLOR,RENDER_DRAW_COLOR);
        // lam moi du lieu man hinh xoa man hinh 
		SDL_RenderClear(g_screen);
		// ham dua anh ra man hinh
		g_background.Render(g_screen, NULL);
		// ham update lai man hinh
		
		
		

		p_player.SetMapXY(map_data.start_x_, map_data.start_y_);


		p_player.DoPlayer(map_data);
		p_player.Show(g_screen);

		

		game_map.SetMap(map_data);
		game_map.DrawMap(g_screen);




		
		std::string mark_value_str = std::to_string(mark_value);
        mark_game.LoadText(g_font_text, mark_value_str, g_screen);
        mark_game.RenderText(g_screen, 100, 10);

		mark_game.LoadText(g_font_text, "MARK : ", g_screen); 
	    mark_game.RenderText(g_screen, 20, 10); 
		
		
		if(p_player.checktaodoc(map_data, BLANK_TAODOC, MOI_TAO_DOC))
		{
			mark_value -= 10;
		}

		else if(p_player.checkhoiphuc(map_data,BLANK_HOIPHUC,MOI_HOI_PHUC))
		{
			mark_value += 10;
		}

		else if(p_player.checkbom(map_data,BLANK_BOM, MOI_BOM))
		{
			mark_value-=40;
		}
		else if(p_player.checksieuhoiphuc(map_data,BLANK_SIEUHOIPHUC, MOI_SIEU_HOI_PHUC))
		{
			mark_value +=30;
		}

		
        // Hiển thị giá trị của mark_value lên màn hình
        



		SDL_RenderPresent(g_screen);
		int real_imp_time = fps_timer.get_ticks(); // lay thoi gian da choi
		int time_on_frame = 1000/FRAME_PER_SECOND;//MS

		if(real_imp_time < time_on_frame){
			int delay_time = time_on_frame - real_imp_time;
			
			if(delay_time>=0) SDL_Delay(delay_time);// de chuong trinh chay nhanh hon thi tang fps len
		}
	}
	game_map.KhoiPhucMap(map_data);
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
		
	if (TTF_Init() == GA_FAILED) return false;

    g_font_text = TTF_OpenFont("Dreams.ttf", 30);
    if (g_font_text == NULL) return false;

   
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
	TTF_Quit();
}
