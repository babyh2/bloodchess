#ifndef MAIN_OBJECT_H
#define MAIN_OBJECT_H

#include"Commonfunc.h"
#include"BaseObject.h"

#define PLAYER_SPEED 1

class MainObject : public BaseObject
{
public:
	MainObject();
	~MainObject();

	enum WalkType
	{
		WALK_RIGHT = 0,
		WALK_LEFT = 1,
		WALK_UP = 2,
		WALK_DOWN = 3,
	};

	bool LoadImg(std::string path, SDL_Renderer* screen);
	void Show(SDL_Renderer* des);
	void HandelInputAction(SDL_Event events, SDL_Renderer* screen);
	void DoPlayer(Map& map_data);
	void CheckToMap(Map& map_data);

private:
	int  x_val_;
	int  y_val_;
	
	int x_pos_;
	int y_pos_;

	int width;
	int height;

	Input input_type_;
	int status_;
};





#endif