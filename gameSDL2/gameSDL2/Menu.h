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
	int ShowMenuTaiXiu(SDL_Renderer* screen, TTF_Font* font);
	int menuMuaBan(SDL_Renderer* screen, TTF_Font* font, int& coin);
	int menuWin(SDL_Renderer* screen, TTF_Font* font);
	int menuLoss(SDL_Renderer* screen, TTF_Font* font);
	int menuHighScore(SDL_Renderer* screen, TTF_Font* font, int& high_score );

};

#endif // MENU_H





