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
    const std::string menuItems[kMenuNum] = {"START GAME", "EXIT", "INSTRUCTION", "HIGH SCORE"};
    
    // Thiết lập menu ban đầu
    for (int i = 0; i < kMenuNum; i++) {
        textMenu[i].SetColor(TextObject::BLACK);
        textMenu[i].LoadText(font, menuItems[i], screen);
        textMenu[i].SetRect(pos_arr[i].x, pos_arr[i].y);
        textMenu[i].GetSize(pos_arr[i].w, pos_arr[i].h);
    }

    // Mảng để theo dõi mục menu đã chọn
    bool selected[kMenuNum] = {false, false, false, false};

	int xm =0;
	int ym =0;

    // Vòng lặp chính để hiển thị menu
    SDL_Event m_event;
    while (true) {
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
                // Xử lý sự kiện di chuyển chuột
                xm = m_event.motion.x;
                ym = m_event.motion.y;
                for (int i = 0; i < kMenuNum; i++) {
                    if (CheckFocus(xm, ym, pos_arr[i])) {
                        if (!selected[i]) {
                            selected[i] = true;
                            textMenu[i].SetColor(TextObject::GREEN);
                        }
                    } else {
                        if (selected[i]) {
                            selected[i] = false;
                            textMenu[i].SetColor(TextObject::BLACK);
                        }
                    }
                }
            } else if (m_event.type == SDL_MOUSEBUTTONDOWN) {
                // Xử lý sự kiện nhấp chuột
                xm = m_event.button.x;
                ym = m_event.button.y;
                for (int i = 0; i < kMenuNum; i++) {
                    if (CheckFocus(xm, ym, pos_arr[i])) {
                        // Người dùng chọn mục menu
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

