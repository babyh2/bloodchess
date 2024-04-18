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

void Menu::ShowMenu(SDL_Renderer* screen, TTF_Font* font) {

    // Hiển thị menu lên màn hình
	
	const int kMenuNum = 4;
	SDL_Rect pos_arr[kMenuNum];

	pos_arr[0].x = 200;
	pos_arr[0].y = 300;

	pos_arr[1].x = 200;
	pos_arr[1].y = 400;
	
	pos_arr[2].x = 200;
	pos_arr[2].y = 500;

	pos_arr[3].x = 200;
	pos_arr[3].y = 600;

	TextObject textMenu[kMenuNum];

	textMenu[0].SetColor(TextObject::BLACK);
	textMenu[0].SetRect(pos_arr[0].x,pos_arr[0].y);
	textMenu[0].LoadText(font, "START GAME", screen);


	textMenu[1].SetColor(TextObject::BLACK);
	textMenu[1].SetRect(pos_arr[1].x,pos_arr[1].y);
	textMenu[1].LoadText(font, "EXIT", screen);

	textMenu[2].SetColor(TextObject::BLACK);
	textMenu[2].SetRect(pos_arr[2].x,pos_arr[2].y);
	textMenu[2].LoadText(font, "INSTRUCTION", screen);

	textMenu[3].SetColor(TextObject::BLACK);
	textMenu[3].SetRect(pos_arr[3].x,pos_arr[3].y);
	textMenu[3].LoadText(font, "HIGH SCORE", screen);


	bool selected[kMenuNum] = {0,0,0,0};

	// vong lap hien thi chuot va menu
	SDL_Event m_event;

	while(true)
	{
		LoadMenu(screen, "menuchinh.png");
		Show(screen, 0,0);
		for(int i=0;i<kMenuNum;i++)
		{
			textMenu[i].RenderText(screen, pos_arr[i].x, pos_arr[i].y);
		}
	}
	
}
