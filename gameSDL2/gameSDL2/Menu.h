#ifndef MENU_H
#define MENU_H

#include"Commonfunc.h"
#include "BaseObject.h"
#include"TextObject.h"

class Menu : public BaseObject {
private:
    int menu_width_;
    int menu_height_;

public:
    Menu();
    ~Menu();

    bool LoadMenu(SDL_Renderer* screen, std::string temp);
	void Show(SDL_Renderer* screen,int x,int y);
	int ShowMenu(SDL_Renderer* screen, TTF_Font* font);
    
	bool CheckFocus(const int &x,const int &y,const  SDL_Rect& rect);
};

#endif // MENU_H





