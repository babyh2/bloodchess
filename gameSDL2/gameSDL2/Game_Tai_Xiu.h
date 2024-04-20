#ifndef GAMe_TAI_XIU_H
#define GAME_TAI_XIU_H

#include"BaseObject.h"
#include"Commonfunc.h"
#include"TextObject.h"



class Game_Tai_Xiu : public BaseObject
{
public:
	int num[3];
	int numtong;

	int taimoney;
    int xiumoney;

	int menu_width_;
	int menu_height_;
	
private:

	Game_Tai_Xiu();
	~Game_Tai_Xiu();

	bool LoadMenuTaiXiu(SDL_Renderer* screen, std::string path);
    void ShowMenu(SDL_Renderer* screen, int x, int y);
	bool CheckTaiXiu(const int& x, const int& y, const SDL_Rect& rect);
	bool ShowMenuTaiXiu(SDL_Renderer* screen, TTF_Font* font);
	void gameThuc(SDL_Renderer* screen, TTF_Font* font, int &mark_value);
	void logicgame(SDL_Renderer* screen, int& mark_value);


};








#endif