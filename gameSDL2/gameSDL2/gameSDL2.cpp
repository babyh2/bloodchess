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


int main(int argc, char* argv[]) {
    ImpTime fps_timer;
    unsigned seed = time(0);
    srand(seed);

	

    if (!InitData()) return -1;
    if (!LoadBackground()) return -1;

    GameMap game_map;
    game_map.LoadMap("map/map01.dat");
    game_map.LoadTiles(g_screen);

    Map map_data = game_map.getMap();
    game_map.random_vatcan(map_data);

    MainObject p_player;

    TextObject mark_game;
    mark_game.SetColor(TextObject::RED);
    SDL_Color red = {255, 0, 0, 255};

    int coin = 200;
    int mark_value = 100;
	int nhanvat = 1;
	bool damua = false ;
    // Quản lý các trạng thái của trò chơi
    enum GameState {
        MENU,
        GAME,
        SHOP,
        RULES,
        WIN,
        LOSS,
        EXIT
    };
    
    GameState currentState = MENU;
    GameState previousState = MENU;

    // Vòng lặp chính của trò chơi
    while (currentState != EXIT) {
        switch (currentState) {
            case MENU:
             {   // Xử lý trạng thái menu
                int ret_menu = menu_game.ShowMenu(g_screen, g_font_text);
                previousState = currentState;
                if (ret_menu == 0) {
                    currentState = GAME;
                } else if (ret_menu == 1) {
                    currentState = EXIT;
                } else if (ret_menu == 2) {
                    currentState = SHOP;
                } else if (ret_menu == 3) {
                    currentState = RULES;
                }
                break;
			 }
            case GAME:
				{
                // Xử lý trạng thái trò chơi
                fps_timer.start();

                while (SDL_PollEvent(&g_event) != 0) {
                    if (g_event.type == SDL_QUIT) {
                        currentState = EXIT;
                        break;
                    } else if (g_event.type == SDL_KEYDOWN && g_event.key.keysym.sym == SDLK_ESCAPE) {
                        // Quay trở lại menu chính khi nhấn phím Escape
                        currentState = MENU;
                        break;
                    }
                    p_player.HandelInputAction(g_event, g_screen);
                }

                if (currentState == EXIT || currentState == MENU) {
                    break;
                }
				g_background.Render(g_screen, NULL);
                // Xử lý cập nhật trò chơi
                p_player.SetMapXY(map_data.start_x_, map_data.start_y_);
    p_player.DoPlayer(map_data);
    p_player.Show(g_screen, nhanvat);
    game_map.SetMap(map_data);
    game_map.DrawMap(g_screen);

    // Hiển thị điểm của trò chơi lên màn hình
    std::string mark_value_str = std::to_string(mark_value);
    mark_game.LoadText(g_font_text, mark_value_str, g_screen);
    mark_game.RenderText(g_screen, 100, 10);
    mark_game.LoadText(g_font_text, "MARK : ", g_screen);
    mark_game.RenderText(g_screen, 20, 10);

    // Kiểm tra và xử lý các vật phẩm trên bản đồ
    if (p_player.checktaodoc(map_data, BLANK_TAODOC, MOI_TAO_DOC)) {
        if (nhanvat == 1) {
            mark_value -= 10;
        } else if (nhanvat == 2) {
            mark_value -= 0;
        }
    } else if (p_player.checkhoiphuc(map_data, BLANK_HOIPHUC, MOI_HOI_PHUC)) {
        mark_value += 10;
    } else if (p_player.checkbom(map_data, BLANK_BOM, MOI_BOM)) {
        mark_value -= 40;
    } else if (p_player.checksieuhoiphuc(map_data, BLANK_SIEUHOIPHUC, MOI_SIEU_HOI_PHUC)) {
        mark_value += 30;
    }

    // Kiểm tra điều kiện thắng hoặc thua
    if (p_player.checktaixiu(map_data, END_GAME)) {
        currentState = WIN;
        break;
    }

    if (mark_value <= 0) {
        currentState = LOSS;
        break;
    }

    // Hiển thị màn hình cập nhật
    SDL_RenderPresent(g_screen);

    // Tính toán thời gian đã sử dụng và điều chỉnh tốc độ trò chơi
    int real_imp_time = fps_timer.get_ticks(); // Thời gian thực tế đã sử dụng
    int time_on_frame = 1000 / FRAME_PER_SECOND; // Thời gian tối đa cho mỗi khung hình (frame)
    if (real_imp_time < time_on_frame) {
        int delay_time = time_on_frame - real_imp_time;
        if (delay_time >= 0) {
            SDL_Delay(delay_time); // Thêm độ trễ để duy trì tốc độ trò chơi
        }
    }

                break;
				}
            case SHOP:
      {          // Xử lý trạng thái shop
				// Hiển thị menu của cửa hàng
    int muaban = menu_game.menuMuaBan(g_screen, g_font_text, coin);
    // Kiểm tra kết quả từ menu cửa hàng
    if (muaban == -1) {
        // Người dùng muốn thoát cửa hàng
        currentState = MENU; // Quay trở lại menu chính
    } else if (muaban == 0) {
        // Người dùng mua nhân vật đầu tiên
        nhanvat = 1; // Chuyển đổi nhân vật chính thành nhân vật đầu tiên
    } else if (muaban == 1) {
        // Người dùng muốn mua nhân vật thứ hai
        if (coin >= 100) {
            // Kiểm tra nếu người chơi có đủ tiền
            coin -= 100; // Trừ tiền người chơi
            damua = true; // Đánh dấu đã mua
        } else {
            // Nếu không đủ tiền, hiển thị thông báo
            RenderTextFor5Seconds(g_screen, g_font_text, "You do not have enough money to buy this character. Play the game to earn more.", red);
        }
    } else if (muaban == 2) {
        // Người dùng muốn chọn nhân vật thứ hai
        if (damua == true) {
            nhanvat = 2; // Chuyển đổi nhân vật chính thành nhân vật thứ hai
        } else {
            // Nếu chưa mua nhân vật thứ hai, hiển thị thông báo
            RenderTextFor5Seconds(g_screen, g_font_text, "You do not own this character yet.", red);
        }
    }
                 else if (muaban == 3) {
                    currentState = MENU;
                }
                break;
	  }
            case RULES:
              {  // Xử lý trạng thái quy tắc trò chơi
                int x = menu_game.menuRules(g_screen, g_font_text);
                if (x == 0) {
                    currentState = MENU;
                }
                break;
			  }
            case WIN:
             {   // Xử lý trạng thái chiến thắng
                int win_choice = menu_game.menuWin(g_screen, g_font_text);
                if (win_choice == 0) {
                    // Quay lại trò chơi
                    currentState = GAME;
                } else if (win_choice == 1) {
                    currentState = MENU;
                }
                break;
			 }
            case LOSS:
           {     // Xử lý trạng thái thua cuộc
                int loss_choice = menu_game.menuLoss(g_screen, g_font_text);
                if (loss_choice == 0) {
                    // Quay lại trò chơi
                    currentState = GAME;
                } else if (loss_choice == 1) {
                    currentState = MENU;
                }
                break;
		   }
            default:
              {  // Nếu không có trạng thái nào khớp, thoát chương trình
                currentState = EXIT;
				break;}
        }
    }

    // Đóng trò chơi và giải phóng tài nguyên
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
    
    SDL_Rect textRect = {75, 30, textWidth, textHeight };

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

void khophuc();

void close() {
	// tat tat ca cac hd va dua toan bo con tro ve null
	
	SDL_DestroyRenderer(g_screen);
	g_screen = NULL;
	SDL_DestroyWindow(g_window);
	g_window = NULL;
	IMG_Quit();
	SDL_Quit();
	TTF_Quit();
}

