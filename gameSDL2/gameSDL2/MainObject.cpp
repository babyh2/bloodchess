#include"stdafx.h"
#include"MainObject.h"

MainObject::MainObject(){
	x_pos_=0;
	y_pos_=0;
	x_val_=0;
	y_val_=0;
	width=0;
	height=0;
	status_= WALK_RIGHT;
};
MainObject::~MainObject(){

};


bool MainObject::LoadImg(std::string path, SDL_Renderer* screen){
	bool ret = BaseObject::LoadImg(path,screen); // ke thua da hinh tai su dung
	if (ret == true){
		width= rect_.w;
		height=rect_.h;

	}
	return ret;

} // ham de xuat anh ke thua da hinh

void MainObject::Show(SDL_Renderer* des){
	if(status_ == WALK_LEFT){
		LoadImg("img/sieunhan_left.jpg",des);
	}
	else if(status_ == WALK_RIGHT){
		LoadImg("img/sieunhan_right.jpg",des);
	}

	else if(status_ == WALK_UP){
		LoadImg("img/sieunhan_up.jpg",des);
	}
	else if(status_ == WALK_DOWN){
		LoadImg("img/sieunhan_down.jpg",des);
	}

	// cac ham xuat anh tuong ung
	rect_.x=x_pos_; // lay vi tri
	rect_.y=y_pos_; 

	SDL_Rect renderQuad = {rect_.x, rect_.y, width, height}; // luu toa do
	SDL_RenderCopy(des,p_object, NULL, &renderQuad);
}


void MainObject::HandelInputAction(SDL_Event events, SDL_Renderer* screen)
{
	if(events.type == SDL_KEYDOWN){
		switch(events.key.keysym.sym){
		case SDLK_RIGHT:
			{
				status_ = WALK_RIGHT;
				input_type_.right_ = 10;
			}
			break;
		case SDLK_LEFT:
			{
				status_ = WALK_LEFT;
				input_type_.left_ = -10;
			}
			break;
		case SDLK_UP:
			{
				status_ = WALK_UP;
				input_type_.up_ = 10;
			}
			break;
		case SDLK_DOWN:
			{
				status_ = WALK_DOWN;
				input_type_.down_ = -10;
			}
			break;
		default: break;
		}
	}
	else if(events.type == SDL_KEYUP)
	{
		
	}

}
