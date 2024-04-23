// gameSDL2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include"BaseObject.h"
#include"Commonfunc.h"
#include"Game_map.h"
#include"MainObject.h"
#include"ImpTime.h"
#include"TextObject.h"
#include"Menu.h"



TTF_Font* g_font_text = NULL;
BaseObject g_background;




// ham khoi tao cac gia tri trong bai
bool InitData();

// ham tai background

bool LoadBackground();
void RenderTextFor5Seconds(SDL_Renderer* screen, TTF_Font* font, const std::string& text,SDL_Color color);

// ham giai phong cac doi tuong
void close();
Menu menu_game;


int main(int argc, char* argv[])
{
	ImpTime fps_timer;
	 unsigned seed = time(0);
    srand(seed);

	if(InitData()==false) return -1;
	if(LoadBackground() == false) return -1;


	GameMap game_map;
	game_map.LoadMap("map/map01.dat");
	game_map.LoadTiles(g_screen);
	Map map_data = game_map.getMap();
	game_map.random_vatcan(map_data);

	MainObject p_player;
	

	TextObject mark_game;
	mark_game.SetColor(TextObject::RED);
	SDL_Color red = {255,0,0,255};

	int coin = 200;
	int mark_value =100;
	// tao mot vong lap vo han de load tam anh 
	bool is_quit = false;
	bool inMenu = true ;
	bool inShop = false;
	bool inGame = false; 
	int nhanvat=1;
	bool damua = false ;
	bool through_menu = false;
	bool through_home = false;

	while(inMenu){
		if(through_menu == false)
		{
			int ret_menu = menu_game.ShowMenu(g_screen, g_font_text);
			switch (ret_menu)
			{
			case 0: through_home = true; inGame = true; break;
			case 1: through_menu = false; inMenu = false; break;
			case 2: through_home = true;inShop = true; break;
			case 3: break;
			default:
				break;
			}
			if(through_home == true)
			{
				while(inShop){
					std::string coin_str = std::to_string(coin);
                    mark_game.LoadText(g_font_text, coin_str, g_screen);
                    mark_game.RenderText(g_screen, 1000, 10);
					
					int muaban = menu_game.menuMuaBan(g_screen, g_font_text);
					if (muaban == -1) return 0;
					else if(muaban ==3) {inShop = false;  through_menu = false; inGame = false; }
					else if(muaban ==0) 
						{
							nhanvat = 1; 
							
						}
					else if(muaban ==1)
						{
							if(coin>=100)
							{
								coin -= 100;
								damua = true;
							}
							else {
								RenderTextFor5Seconds(g_screen, g_font_text, "ban chua du tien hay choi game", red);
							}
							
						}
					else if(muaban == 2)
						{
							if(damua == true)
							{
								nhanvat = 2;
							}
							else RenderTextFor5Seconds(g_screen, g_font_text, "ban chua co nhan vat nay hay choi game", red);
						}
					SDL_RenderPresent(g_screen);
				}
				while(inGame)
				{
					if(nhanvat ==1) p_player.LoadImg("img/sieunhan_right.jpg", g_screen);
		            else if(nhanvat == 2) p_player.LoadImg("img/joker.png", g_screen);
		fps_timer.start();

		while(SDL_PollEvent(&g_event) !=0)
		{
			if(g_event.type == SDL_QUIT ) {

				is_quit = true;
				
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
		p_player.Show(g_screen, nhanvat);

		

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
	   
				}
			}

	   }//while(!in_menu)
//if(through_menu)
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


// Hàm hiển thị màn hình thắng cuộc

void RenderTextFor5Seconds(SDL_Renderer* screen, TTF_Font* font, const std::string& text, SDL_Color color) {
    // Tạo bề mặt văn bản (SDL_Surface) bằng hàm TTF_RenderText_Solid với văn bản và màu sắc đã cho
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), color);
    
    if (!textSurface) {
        return;
    }
    
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(screen, textSurface);
    
    if (!textTexture) {
        SDL_FreeSurface(textSurface);
        return;
    }
    
    int textWidth = textSurface->w;
    int textHeight = textSurface->h;
    
    SDL_Rect textRect = { 500, 380, textWidth, textHeight };

    // Hiển thị văn bản (text) lên màn hình
    SDL_RenderCopy(screen, textTexture, nullptr, &textRect);
    SDL_RenderPresent(screen);

    // Đợi trong 5 giây
    SDL_Delay(5000);

    // Không xóa màn hình hoặc vùng văn bản, hãy để vòng lặp render của trò chơi tự quản lý
    // Giải phóng tài nguyên
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
}



void close() {
	// tat tat ca cac hd va dua toan bo con tro ve null
	g_background.Free();
	SDL_DestroyRenderer(g_screen);
	g_screen = NULL;
	SDL_DestroyWindow(g_window);
	g_window = NULL;
	IMG_Quit();
	SDL_Quit();
	TTF_Quit();
}

