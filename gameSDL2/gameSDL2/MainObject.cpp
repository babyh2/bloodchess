#include"stdafx.h"
#include"MainObject.h"

MainObject::MainObject(){
	x_pos_=2;
	y_pos_=762;
	x_val_=0;
	y_val_=0;
	width=0;
	height=0;
	status_= WALK_RIGHT;
	input_type_.left_=0;
	input_type_.right_=0;
	input_type_.up_=0;
	input_type_.down_=0;
	map_x_=0;
	map_y_=0;
	speed = PLAYER_SPEED;
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
	rect_.x=x_pos_ - map_x_; // lay vi tri
	rect_.y=y_pos_ - map_y_; // khi chay nhan vat man hinh bi cuon theo nen phai tru di luong man hinh bi cuon di
	// tru di de giu nhan vat luon o giua man hinh 

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
				input_type_.right_ = 1;
				input_type_.left_=0;
				input_type_.down_=0;
				input_type_.up_=0;
			}
			break;
		case SDLK_LEFT:
			{
				status_ = WALK_LEFT;
				input_type_.left_ = 1;
				input_type_.right_ = 0;
				input_type_.down_=0;
				input_type_.up_=0;
			}
			break;
		case SDLK_UP:
			{
				status_ = WALK_UP;
				input_type_.up_ = 1;
				input_type_.right_ = 0;
				input_type_.left_=0;
				input_type_.down_=0;
				
			}
			break;
		case SDLK_DOWN:
			{
				status_ = WALK_DOWN;
				input_type_.down_ = 1;
				input_type_.right_ = 0;
				input_type_.left_=0;
				input_type_.up_=0;
			}
			break;
		default: break;
		}
	}
	else if(events.type == SDL_KEYUP)
	{
		switch (events.key.keysym.sym)
		{
		case SDLK_RIGHT:
			{
				input_type_.right_=0;
			}
			break;
		case SDLK_LEFT:
			{
				input_type_.left_=0;
			}
			break;
		case SDLK_UP:
			{
				input_type_.up_=0;
			}
			break;
		case SDLK_DOWN:
			{
				input_type_.down_=0;
			}

		default:
			break;
		}
	}

}


void MainObject::DoPlayer(Map& map_data){
	x_val_=0;
	y_val_=0;
	if(input_type_.left_ == 1){
        x_val_ -= speed;
	}
	if(input_type_.right_ ==1){
		x_val_ += speed;
	}
	if(input_type_.up_ ==1){
		y_val_ -= speed;
	}
	if(input_type_.down_ == 1){
		y_val_ += speed;
	}
	CheckToMap(map_data);
	CenterEntityOnMap(map_data);
}

void MainObject::CenterEntityOnMap(Map& map_data)
{
	//Neu nhan vat di chuyen den vi tri nua ban do thi di chuyen map theo nhan vat
	map_data.start_x_=x_pos_ - (SCREEN_WIDTH/2);
	if(map_data.start_x_ <0)// xet nhan vat di chuyen theo chieu ngang
	{
		map_data.start_x_=0;
	}
	else if(map_data.start_x_ + SCREEN_WIDTH >= map_data.max_x_)
	{
		map_data.start_x_=map_data.max_x_-SCREEN_WIDTH;
	}
	map_data.start_y_ = y_pos_ -(SCREEN_HEIGHT/2);
	if(map_data.start_y_<0)// xet nhan vat di chuyen theo chieu doc
	{
		map_data.start_y_ =0;

	}
	else if(map_data.start_y_+SCREEN_HEIGHT>= map_data.max_y_)
	{
		map_data.start_y_=map_data.max_y_-SCREEN_HEIGHT;
	}
}

void MainObject::CheckToMap(Map& map_data){
	int x1=0;
	int x2=0;

	int y1=0;
	int y2=0;

	// kiemtra theo chieu cao;
	int height_min = height < TILE_SIZE ? height : TILE_SIZE;
	//lay chieu cao gioi han

	x1 = (x_pos_ + x_val_)/ TILE_SIZE;
	x2 = (x_pos_ + x_val_ + width -1)/ TILE_SIZE;

	y1 = (y_pos_ + y_val_)/TILE_SIZE;
	y2 = (y_pos_ + y_val_ +height_min -1)/TILE_SIZE;

	// lay vi tri hien tai cua buc anh dang ow o thu bao nhieu tren ban do

	if(x1>=0 && x2<MAX_MAP_X && y1>0 && y2<MAX_MAP_Y)
	{
		if(x_val_ > 0)// vat dang di chuyen tien sang phai
		{
			if(map_data.tile[y1][x2] == BLANK_TILE || map_data.tile[y2][x2] == BLANK_TILE)
			{
				x_pos_ = x2*TILE_SIZE;
				x_pos_ -= width + 1;
				x_val_=0;
			}
		}
		else if(x_val_ < 0)
		{
			if(map_data.tile[y1][x1] == BLANK_TILE || map_data.tile[y2][x1] == BLANK_TILE)
			{
				x_pos_ = (x1 + 1) * TILE_SIZE;
				x_val_=0;
			}
		}
	}// ktra dua tren map xay dung boi cac so trong file mapdata.dat

	// so sanh theo chieu doc 
	int width_min = width < TILE_SIZE ? width : TILE_SIZE;
	x1 = x_pos_ / TILE_SIZE;
	x2 = (x_pos_ + width_min) / TILE_SIZE;

	y1 = (y_pos_ + y_val_) / TILE_SIZE;
	y2 = (y_pos_ + y_val_ + height -1) / TILE_SIZE;

	if(x1>=0 && x2<MAX_MAP_X && y1>=0 && y2<MAX_MAP_Y)
	{
		if(y_val_ >0)
		{
			if(map_data.tile[y2][x1] == BLANK_TILE || map_data.tile[y2][x2] == BLANK_TILE)
			{
				y_pos_ = y2*TILE_SIZE;
				y_pos_ -= (height +1);
				y_val_=0;
			}
		}
		if(y_val_<0)
		{
			if(map_data.tile[y1][x1] == BLANK_TILE || map_data.tile[y1][x2] == BLANK_TILE)
			{
				y_pos_ = (y1+1) * TILE_SIZE;
				y_val_=0;
			}
		}
	}



	x_pos_ += x_val_;
	y_pos_ += y_val_;

	if(x_pos_<0) x_pos_ =0;
	else if (x_pos_ + width > map_data.max_x_)
	{
		x_pos_ = map_data.max_x_ - width -1 ;
	}
	if(y_pos_ < TILE_SIZE ) y_pos_ = TILE_SIZE;
	else if( y_pos_ + height > map_data.max_y_-TILE_SIZE)
	{
		y_pos_ = map_data.max_y_ -height -1-TILE_SIZE;
	}
}

bool MainObject::CheckTaiXiu(Map& map_data){
	int x1=0;
	int y1=0;
	int x2=0;
	int y2=0;

	int height_min = height < TILE_SIZE ? height : TILE_SIZE;
	x1 = (x_pos_ + x_val_)/ TILE_SIZE;
	x2 = (x_pos_ + x_val_ + width -1)/ TILE_SIZE;

	y1 = (y_pos_ + y_val_)/TILE_SIZE;
	y2 = (y_pos_ + y_val_ +height_min -1)/TILE_SIZE;

	if(x1>=0 && x2<MAX_MAP_X && y1>0 && y2<MAX_MAP_Y)
	{
		if(x_val_ > 0)// vat dang di chuyen tien sang phai
		{
			if(map_data.tile[y1][x2] == BLANK_TAIXIU || map_data.tile[y2][x2] == BLANK_TAIXIU)
			{
				x_val_=0;
				speed=0;
				return true;
			}
		}
		else if(x_val_ < 0)
		{
			if(map_data.tile[y1][x1] == BLANK_TAIXIU || map_data.tile[y2][x1] == BLANK_TAIXIU)
			{
				x_val_=0;
				speed =0;
				return true;
			}
		}
	}

	int width_min = width < TILE_SIZE ? width : TILE_SIZE;
	x1 = x_pos_ / TILE_SIZE;
	x2 = (x_pos_ + width_min) / TILE_SIZE;

	y1 = (y_pos_ + y_val_) / TILE_SIZE;
	y2 = (y_pos_ + y_val_ + height -1) / TILE_SIZE;

	if(x1>=0 && x2<MAX_MAP_X && y1>=0 && y2<MAX_MAP_Y)
	{
		if(y_val_ >0)
		{
			if(map_data.tile[y2][x1] == BLANK_TAIXIU || map_data.tile[y2][x2] == BLANK_TAIXIU)
			{
				y_val_=0;
				speed=0;
				return true;
			}
		}
		if(y_val_<0)
		{
			if(map_data.tile[y1][x1] == BLANK_TAIXIU || map_data.tile[y1][x2] == BLANK_TAIXIU)
			{
				y_val_=0;
				speed=0;
				return true;
			}
		}
	}

	x_pos_+=x_val_;
	y_pos_+=y_val_;
	return false;

}


