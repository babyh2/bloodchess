#include"stdafx.h"
#include "Menu.h"

Menu::Menu() : BaseObject() {
     
    menu_width_ = 0;
    menu_height_ = 0;
}

Menu::~Menu() {
    
}

bool Menu::LoadMenu(SDL_Renderer* screen, std::string temp) {
    // Load ảnh của menu và gán vào p_object
    bool ret = LoadImg(temp, screen);
    if (ret) {
        // Gán kích thước của menu
        menu_width_ = rect_.w;
        menu_height_ = rect_.h;
    }
    return ret;
}

void Menu::Show(SDL_Renderer* screen,int x,int y)
{
	
	SDL_Rect renderQuad = {x,y,menu_width_, menu_height_};
	SDL_RenderCopy(screen, p_object, NULL, &renderQuad);
}

bool Menu::CheckFocus(const int& x, const int& y, const SDL_Rect& rect)
{
	if(x>=rect.x && x < rect.x + rect.w
		&& y>=rect.y && y<=rect.y + rect.h)
		return true;
	else return false;
}

int Menu::ShowMenu(SDL_Renderer* screen, TTF_Font* font) {
    const int kMenuNum = 4;
    SDL_Rect pos_arr[kMenuNum] = {
        {200, 300, 0, 0},
        {200, 400, 0, 0},
        {200, 500, 0, 0},
        {200, 600, 0, 0}
		
    };

    TextObject textMenu[kMenuNum];
    const std::string menuItems[kMenuNum] = {"START GAME", "EXIT", "SHOPPING", "RULES OF THE GAME"};
    
    // Thiết lập menu ban đầu
    for (int i = 0; i < kMenuNum; i++) {
        textMenu[i].SetColor(TextObject::RED);  // Màu mặc định là màu đỏ
        textMenu[i].LoadText(font, menuItems[i], screen);
        textMenu[i].SetRect(pos_arr[i].x, pos_arr[i].y);
        textMenu[i].GetSize(pos_arr[i].w, pos_arr[i].h);
    }

    // Mảng để theo dõi mục menu đã chọn
    bool selected[kMenuNum] = {false, false, false, false};

    SDL_Event m_event;
	bool in_game = true;
    while (in_game) {
        // Load background menu và hiển thị
        LoadMenu(screen, "menuchinh.png");
        Show(screen, 0, 0);

        // Hiển thị các mục menu
        for (int i = 0; i < kMenuNum; i++) {
            textMenu[i].RenderText(screen, pos_arr[i].x, pos_arr[i].y);
        }

        // Xử lý sự kiện
        while (SDL_PollEvent(&m_event)) {
            if (m_event.type == SDL_QUIT) {
                // Thoát chương trình
                return 1;
            } else if (m_event.type == SDL_MOUSEMOTION) {
                int xm = m_event.motion.x;
                int ym = m_event.motion.y;
                
                // Kiểm tra di chuyển chuột vào mục menu
                for (int i = 0; i < kMenuNum; i++) {
                    bool isFocus = CheckFocus(xm, ym, pos_arr[i]);
                    
                    // Kiểm tra trạng thái trước đó và thay đổi màu sắc nếu cần
                    if (isFocus && !selected[i]) {
                        selected[i] = true;
                        textMenu[i].SetColor(TextObject::YELLOW); // Đổi sang màu vàng khi con trỏ chuột đến
                        textMenu[i].LoadText(font, menuItems[i], screen);  // Cập nhật văn bản
                    } else if (!isFocus && selected[i]) {
                        selected[i] = false;
                        textMenu[i].SetColor(TextObject::RED); // Trở lại màu đỏ khi con trỏ chuột rời khỏi
                        textMenu[i].LoadText(font, menuItems[i], screen);  // Cập nhật văn bản
                    }
                }
            } else if (m_event.type == SDL_MOUSEBUTTONDOWN) {
                int xm = m_event.button.x;
                int ym = m_event.button.y;
                // Kiểm tra chọn mục menu
                for (int i = 0; i < kMenuNum; i++) {
                    if (CheckFocus(xm, ym, pos_arr[i])) {
                        // Người dùng chọn mục menu
						if(i==2) in_game = false;
                        return i; // Trả về chỉ số của mục menu đã chọn
                    }
                }
            } else if (m_event.type == SDL_KEYDOWN) {
                if (m_event.key.keysym.sym == SDLK_ESCAPE) {
                    // Thoát chương trình khi nhấn phím Escape
                    return 1;
                }
            }
        }
        
        // Cập nhật màn hình sau khi xử lý sự kiện
        SDL_RenderPresent(screen);
    }
    return 1;
}



int Menu::menuMuaBan(SDL_Renderer* screen,TTF_Font* font, int& coin)
{
   
	const int kMenuNum = 5;
	SDL_Rect pos_arr[kMenuNum] = {
        {200, 670, 0, 0},
        {775, 544, 0, 0},
        {775, 670, 0, 0},
        {10, 10, 0, 0},
		{900, 10, 0, 0}
    };
	TextObject textMenu[kMenuNum];
	const std::string menuItems[kMenuNum] = {"USE", "BUY", "USE", "EXIT" ,"COIN"};
	for (int i = 0; i < kMenuNum; i++) {
        textMenu[i].SetColor(TextObject::RED);  // Màu mặc định là màu đỏ
        textMenu[i].LoadText(font, menuItems[i], screen);
        textMenu[i].SetRect(pos_arr[i].x, pos_arr[i].y);
        textMenu[i].GetSize(pos_arr[i].w, pos_arr[i].h);
    }
	bool selected[kMenuNum-1] = {false, false, false, false};
	bool in_game = true;
	while(in_game){
	 LoadMenu(screen, "shop.png");
     Show(screen, 0, 0);
	 for (int i = 0; i < kMenuNum; i++) {
            textMenu[i].RenderText(screen, pos_arr[i].x, pos_arr[i].y);
        }
	 std::string coin_str = std::to_string(coin);
	 TextObject coin;
	 coin.SetColor(TextObject::RED);
	 coin.LoadText(font, coin_str, screen);
	 coin.RenderText(screen, 1000, 10);
	SDL_Event m_event;
	
	while (SDL_PollEvent(&m_event)) {
            if (m_event.type == SDL_QUIT) {
                // Thoát chương trình
                return -1;
            } else if (m_event.type == SDL_MOUSEMOTION) {
                int xm = m_event.motion.x;
                int ym = m_event.motion.y;
                
                // Kiểm tra di chuyển chuột vào mục menu
                for (int i = 0; i < kMenuNum-1; i++) {
                    bool isFocus = CheckFocus(xm, ym, pos_arr[i]);
                    
                    // Kiểm tra trạng thái trước đó và thay đổi màu sắc nếu cần
                    if (isFocus && !selected[i]) {
                        selected[i] = true;
                        textMenu[i].SetColor(TextObject::YELLOW); // Đổi sang màu vàng khi con trỏ chuột đến
                        textMenu[i].LoadText(font, menuItems[i], screen);  // Cập nhật văn bản
                    } else if (!isFocus && selected[i]) {
                        selected[i] = false;
                        textMenu[i].SetColor(TextObject::RED); // Trở lại màu đỏ khi con trỏ chuột rời khỏi
                        textMenu[i].LoadText(font, menuItems[i], screen);  // Cập nhật văn bản
                    }
                }
			}
			else if (m_event.type == SDL_MOUSEBUTTONDOWN) {
                int xm = m_event.button.x;
                int ym = m_event.button.y;
                // Kiểm tra chọn mục menu
				for (int i = 0; i < kMenuNum-1; i++) {
                    if (CheckFocus(xm, ym, pos_arr[i])) {
						if(i==4) in_game = false;
						return i;
                    }
                }
				}
			else if (m_event.type == SDL_KEYDOWN) {
                if (m_event.key.keysym.sym == SDLK_ESCAPE) {
                    // Thoát chương trình khi nhấn phím Escape
                    return -1;
                }
			}

}
	SDL_RenderPresent(screen);
	
	 
	}
	return 3;
}

int Menu::menuWin(SDL_Renderer* screen, TTF_Font* font )
{
	const int kMenuNum = 2;
	SDL_Rect pos_arr[kMenuNum]=
	{
		{360, 560, 0,0},
		{675, 560, 0,0}
	};
	TextObject textMenu[kMenuNum];
	const std::string menuItems[kMenuNum] = {"REPLAY", "EXIT"};
	for (int i = 0; i < kMenuNum; i++) {
        textMenu[i].SetColor(TextObject::RED);  // Màu mặc định là màu đỏ
        textMenu[i].LoadText(font, menuItems[i], screen);
        textMenu[i].SetRect(pos_arr[i].x, pos_arr[i].y);
        textMenu[i].GetSize(pos_arr[i].w, pos_arr[i].h);
    }
	bool selected[kMenuNum] = {false, false };
	while (true)
	{
		LoadMenu(screen, "win.png");
		Show(screen, 310, 180);
		SDL_Event m_event;
	    for (int i = 0; i < kMenuNum; i++) {
            textMenu[i].RenderText(screen, pos_arr[i].x, pos_arr[i].y);
        }
	while (SDL_PollEvent(&m_event)) {
            if (m_event.type == SDL_QUIT) {
                // Thoát chương trình
                return -1;
            } else if (m_event.type == SDL_MOUSEMOTION) {
                int xm = m_event.motion.x;
                int ym = m_event.motion.y;
                
                // Kiểm tra di chuyển chuột vào mục menu
                for (int i = 0; i < kMenuNum; i++) {
                    bool isFocus = CheckFocus(xm, ym, pos_arr[i]);
                    
                    // Kiểm tra trạng thái trước đó và thay đổi màu sắc nếu cần
                    if (isFocus && !selected[i]) {
                        selected[i] = true;
                        textMenu[i].SetColor(TextObject::YELLOW); // Đổi sang màu vàng khi con trỏ chuột đến
                        textMenu[i].LoadText(font, menuItems[i], screen);  // Cập nhật văn bản
                    } else if (!isFocus && selected[i]) {
                        selected[i] = false;
                        textMenu[i].SetColor(TextObject::RED); // Trở lại màu đỏ khi con trỏ chuột rời khỏi
                        textMenu[i].LoadText(font, menuItems[i], screen);  // Cập nhật văn bản
                    }
                }
			}
			else if (m_event.type == SDL_MOUSEBUTTONDOWN) {
                int xm = m_event.button.x;
                int ym = m_event.button.y;
                // Kiểm tra chọn mục menu
				for (int i = 0; i < kMenuNum; i++) {
                    if (CheckFocus(xm, ym, pos_arr[i])) {
						return i;
                    }
                }
				}
			else if (m_event.type == SDL_KEYDOWN) {
                if (m_event.key.keysym.sym == SDLK_ESCAPE) {
                    // Thoát chương trình khi nhấn phím Escape
                    return -1;
                }
			}

	}
	SDL_RenderPresent(screen);
}
	return 1;
}

int Menu::menuLoss(SDL_Renderer* screen, TTF_Font* font )
{
	const int kMenuNum = 2;
	SDL_Rect pos_arr[kMenuNum]=
	{
		{360, 560, 0,0},
		{675, 560, 0,0}
	};
	TextObject textMenu[kMenuNum];
	const std::string menuItems[kMenuNum] = {"REPLAY", "EXIT"};
	for (int i = 0; i < kMenuNum; i++) {
        textMenu[i].SetColor(TextObject::RED);  // Màu mặc định là màu đỏ
        textMenu[i].LoadText(font, menuItems[i], screen);
        textMenu[i].SetRect(pos_arr[i].x, pos_arr[i].y);
        textMenu[i].GetSize(pos_arr[i].w, pos_arr[i].h);
    }
	bool selected[kMenuNum] = {false, false };
	while (true)
	{
		LoadMenu(screen, "loss.png");
		Show(screen, 310, 180);
		SDL_Event m_event;
	    for (int i = 0; i < kMenuNum; i++) {
            textMenu[i].RenderText(screen, pos_arr[i].x, pos_arr[i].y);
        }
	while (SDL_PollEvent(&m_event)) {
            if (m_event.type == SDL_QUIT) {
                // Thoát chương trình
                return -1;
            } else if (m_event.type == SDL_MOUSEMOTION) {
                int xm = m_event.motion.x;
                int ym = m_event.motion.y;
                
                // Kiểm tra di chuyển chuột vào mục menu
                for (int i = 0; i < kMenuNum; i++) {
                    bool isFocus = CheckFocus(xm, ym, pos_arr[i]);
                    
                    // Kiểm tra trạng thái trước đó và thay đổi màu sắc nếu cần
                    if (isFocus && !selected[i]) {
                        selected[i] = true;
                        textMenu[i].SetColor(TextObject::YELLOW); // Đổi sang màu vàng khi con trỏ chuột đến
                        textMenu[i].LoadText(font, menuItems[i], screen);  // Cập nhật văn bản
                    } else if (!isFocus && selected[i]) {
                        selected[i] = false;
                        textMenu[i].SetColor(TextObject::RED); // Trở lại màu đỏ khi con trỏ chuột rời khỏi
                        textMenu[i].LoadText(font, menuItems[i], screen);  // Cập nhật văn bản
                    }
                }
			}
			else if (m_event.type == SDL_MOUSEBUTTONDOWN) {
                int xm = m_event.button.x;
                int ym = m_event.button.y;
                // Kiểm tra chọn mục menu
				for (int i = 0; i < kMenuNum; i++) {
                    if (CheckFocus(xm, ym, pos_arr[i])) {
						return i;
                    }
                }
				}
			else if (m_event.type == SDL_KEYDOWN) {
                if (m_event.key.keysym.sym == SDLK_ESCAPE) {
                    // Thoát chương trình khi nhấn phím Escape
                    return -1;
                }
			}

	}
	SDL_RenderPresent(screen);
}
	return 1;
}


int Menu::menuRules(SDL_Renderer* screen, TTF_Font* font) {
    const int kMenuNum = 1;
    SDL_Rect pos_arr = {20, 20, 0, 0};
    TextObject textMenu;
    const std::string menuItem = "EXIT";
    textMenu.SetColor(TextObject::RED);
    textMenu.LoadText(font, menuItem, screen);
    textMenu.SetRect(pos_arr.x, pos_arr.y);
    textMenu.GetSize(pos_arr.w, pos_arr.h);

    bool selected = false;
    bool in_game = true;
    bool exitGame = false; // Biến mới để kiểm soát thoát game

    while (in_game) {
        LoadMenu(screen, "RULES_OF_THE_GAME.png");
        Show(screen, 0, 0);
        textMenu.RenderText(screen, pos_arr.x, pos_arr.y);
        SDL_Event m_event;

        while (SDL_PollEvent(&m_event)) {
            if (m_event.type == SDL_QUIT) {
                // Người dùng nhấp vào nút đóng cửa sổ
                exitGame = true;
                break;
            } else if (m_event.type == SDL_MOUSEMOTION) {
                int xm = m_event.motion.x;
                int ym = m_event.motion.y;
                
                // Kiểm tra di chuyển chuột vào mục menu
                bool isFocus = CheckFocus(xm, ym, pos_arr);
                
                if (isFocus && !selected) {
                    selected = true;
                    textMenu.SetColor(TextObject::YELLOW);
                    textMenu.LoadText(font, menuItem, screen);
                } else if (!isFocus && selected) {
                    selected = false;
                    textMenu.SetColor(TextObject::RED);
                    textMenu.LoadText(font, menuItem, screen);
                }
            } else if (m_event.type == SDL_MOUSEBUTTONDOWN) {
                int xm = m_event.button.x;
                int ym = m_event.button.y;
                
                // Kiểm tra chọn mục menu
                if (CheckFocus(xm, ym, pos_arr)) {
                    exitGame = true;
                    break; // Thoát khỏi vòng lặp sự kiện
                }
            } else if (m_event.type == SDL_KEYDOWN) {
                if (m_event.key.keysym.sym == SDLK_ESCAPE) {
                    // Người dùng nhấn phím Escape
                    exitGame = true;
                    break;
                }
            }
        }

        SDL_RenderPresent(screen);

        if (exitGame) {
            in_game = false;
            break;
        }
    }

    // Thoát hàm và đóng game
    return 0;
}
