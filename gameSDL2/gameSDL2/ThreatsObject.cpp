#include"stdafx.h"
#include"ThreatsObject.h"

ThreatsObject::ThreatsObject(){
	width =0;
	height = 0;
	x_pos_ =0 ;
	y_pos_=0;
	x_val_=0;
	y_val_=0;

	status_=0;

}

ThreatsObject::~ThreatsObject(){

}
void ThreatsObject::LoadMap(char* name){
    FILE* fp = NULL;
	fopen_s(&fp, name, "rb");
	if(fp == NULL) return;

	game_map_.max_x_=0;
	game_map_.max_y_=0;

	for(int i=0;i<MAX_MAP_Y;i++){
		for(int j=0;j<MAX_MAP_X;j++){
			fscanf_s(fp,"%d",&game_map_.tile[i][j]);
			int val = game_map_.tile[i][j];
			if(val>0){
				if(j>game_map_.max_x_){
					game_map_.max_x_=j;
				}
				if(i>game_map_.max_y_){
					game_map_.max_y_=i;
				}
			}
		}
	}

	game_map_.max_x_=(game_map_.max_x_+1)*TILE_SIZE;
	game_map_.max_y_=(game_map_.max_y_+1)*TILE_SIZE;

	game_map_.start_x_=0;
	game_map_.start_y_=0;
	game_map_.file_name_=name;
	fclose(fp);

}
bool ThreatsObject::LoadImg(std::string path, SDL_Renderer* screen)
{
	bool ret = BaseObject::LoadImg(path,screen);
	if(ret)
	{
		width=rect_.w;
		height=rect_.h;
	}
	return ret;
}

void ThreatsObject::Show(SDL_Renderer* des){
	int x1=0;
	int x2=0;
	int y1=0;
	int y2=0;
	int map_x = 0;
	int map_y = 0;
	/* map_x va map_y dung de xac ding vi tri tren ma tran de lay gia tri tuong ung voi anh
	   de dua anh len man hinh
	*/
	if(status_ == 0 ) LoadImg("img/chamhoi.jpg",des);
	for(int i=0;i<MAX_MAP_Y;i++){
		for(int j=0;j<MAX_MAP_X;j++){
			if(game_map_.tile[i][j]==2){
				rect_.x = j* TILE_SIZE;
				rect_.y = i* TILE_SIZE;
				SDL_Rect rendQuad = {rect_.x,rect_.y,width,height};
	            SDL_RenderCopy (des, p_object,NULL,& rendQuad);
			}
		}
	}
}

