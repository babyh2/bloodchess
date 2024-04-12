#ifndef THREATS_OBJECT_H
#define THREATS_OBJECT_H
// xay dung quai dau cham ?  \


#include"Commonfunc.h"
#include"BaseObject.h"
 



class ThreatsObject : public BaseObject{
public: 
	ThreatsObject();
	~ThreatsObject();
	void Set_x_val(const int &x){x_val_=x;}
	void Set_y_val(const int  &y){y_val_=y;}

	void Set_x_pos(const int &xp){x_pos_=xp;}
	void Set_y_pos(const int &yp){y_pos_=yp;}

	int Get_x_pos(){return x_pos_;}
	int Get_y_pos(){return y_pos_;}
	void SetMap(const int& mpx, const int& mpy){
		map_x_=mpx;
		map_y_=mpy;
	}
	void LoadMap(char* name);
	bool LoadImg(std::string path, SDL_Renderer* screen);
	void Show(SDL_Renderer *des);


private:
	int x_pos_;
	int y_pos_;
	int x_val_;
	int y_val_;

	int map_x_;
	int map_y_;


	int width;
	int height;
	int status_;
	Map game_map_;
};





#endif