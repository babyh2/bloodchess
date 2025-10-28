#include "stdafx.h"
#include "MainObject.h"

MainObject::MainObject()
{
	x_pos_ = 2;
	y_pos_ = 762;
	x_val_ = 0;
	y_val_ = 0;
	width = 0;
	height = 0;
	status_ = WALK_RIGHT;
	input_type_.left_ = 0;
	input_type_.right_ = 0;
	input_type_.up_ = 0;
	input_type_.down_ = 0;
	map_x_ = 0;
	map_y_ = 0;
	speed = PLAYER_SPEED;
};
MainObject::~MainObject() {

};

void MainObject::setPos(int x, int y)
{
	x_pos_ = x;
	y_pos_ = y;
}

bool MainObject::LoadImg(std::string path, SDL_Renderer *screen)
{
	bool ret = BaseObject::LoadImg(path, screen); // ke thua da hinh tai su dung
	if (ret == true)
	{
		width = rect_.w;
		height = rect_.h;
	}
	return ret;

} // ham de xuat anh ke thua da hinh

bool MainObject::LoadPlayerImages(SDL_Renderer *screen)
{
	bool ok = true;
	// Load once and cache
	if (!sprite_left_.LoadImg("img/sieunhan_left.jpg", screen))
		ok = false;
	if (!sprite_right_.LoadImg("img/sieunhan_right.jpg", screen))
		ok = false;
	if (!sprite_up_.LoadImg("img/sieunhan_up.jpg", screen))
		ok = false;
	if (!sprite_down_.LoadImg("img/sieunhan_down.jpg", screen))
		ok = false;
	// optional alternate
	sprite_alt_.LoadImg("img/joker.png", screen);

	// set width/height from one sprite if available
	if (sprite_right_.p_object != NULL)
	{
		rect_.w = sprite_right_.rect_.w;
		rect_.h = sprite_right_.rect_.h;
		width = rect_.w;
		height = rect_.h;
	}
	return ok;
}

void MainObject::Show(SDL_Renderer *des, int x)
{
	// Update position first (map scroll offset applied)
	rect_.x = x_pos_ - map_x_; // lay vi tri
	rect_.y = y_pos_ - map_y_; // khi chay nhan vat man hinh bi cuon theo nen phai tru di luong man hinh bi cuon di

	// Use cached sprites instead of reloading images every frame
	if (x == 1)
	{
		SDL_Texture *tex = nullptr;
		SDL_Rect src = {0, 0, 0, 0};
		if (status_ == WALK_LEFT && sprite_left_.GetObject())
		{
			tex = sprite_left_.GetObject();
			src = sprite_left_.GetRect();
		}
		else if (status_ == WALK_RIGHT && sprite_right_.GetObject())
		{
			tex = sprite_right_.GetObject();
			src = sprite_right_.GetRect();
		}
		else if (status_ == WALK_UP && sprite_up_.GetObject())
		{
			tex = sprite_up_.GetObject();
			src = sprite_up_.GetRect();
		}
		else if (status_ == WALK_DOWN && sprite_down_.GetObject())
		{
			tex = sprite_down_.GetObject();
			src = sprite_down_.GetRect();
		}
		else if (sprite_right_.GetObject())
		{
			tex = sprite_right_.GetObject();
			src = sprite_right_.GetRect();
		}

		if (tex)
		{
			SDL_Rect dest = {rect_.x, rect_.y, src.w, src.h};
			SDL_RenderCopy(des, tex, NULL, &dest);
		}
	}
	else if (x == 2 && sprite_alt_.GetObject())
	{
		SDL_Rect src = sprite_alt_.GetRect();
		SDL_Rect dest = {rect_.x, rect_.y, src.w, src.h};
		SDL_RenderCopy(des, sprite_alt_.GetObject(), NULL, &dest);
	}
	// cac ham xuat anh tuong ung
	// rect_ already updated above
}

void MainObject::HandelInputAction(SDL_Event events, SDL_Renderer *screen)
{
	if (events.type == SDL_KEYDOWN)
	{
		switch (events.key.keysym.sym)
		{
		case SDLK_RIGHT:
		{
			status_ = WALK_RIGHT;
			input_type_.right_ = 1;
			input_type_.left_ = 0;
			input_type_.down_ = 0;
			input_type_.up_ = 0;
		}
		break;
		case SDLK_LEFT:
		{
			status_ = WALK_LEFT;
			input_type_.left_ = 1;
			input_type_.right_ = 0;
			input_type_.down_ = 0;
			input_type_.up_ = 0;
		}
		break;
		case SDLK_UP:
		{
			status_ = WALK_UP;
			input_type_.up_ = 1;
			input_type_.right_ = 0;
			input_type_.left_ = 0;
			input_type_.down_ = 0;
		}
		break;
		case SDLK_DOWN:
		{
			status_ = WALK_DOWN;
			input_type_.down_ = 1;
			input_type_.right_ = 0;
			input_type_.left_ = 0;
			input_type_.up_ = 0;
		}
		break;
		default:
			break;
		}
	}
	else if (events.type == SDL_KEYUP)
	{
		switch (events.key.keysym.sym)
		{
		case SDLK_RIGHT:
		{
			input_type_.right_ = 0;
		}
		break;
		case SDLK_LEFT:
		{
			input_type_.left_ = 0;
		}
		break;
		case SDLK_UP:
		{
			input_type_.up_ = 0;
		}
		break;
		case SDLK_DOWN:
		{
			input_type_.down_ = 0;
		}

		default:
			break;
		}
	}
}

void MainObject::DoPlayer(Map &map_data)
{
	x_val_ = 0;
	y_val_ = 0;
	if (input_type_.left_ == 1)
	{
		x_val_ -= speed;
	}
	if (input_type_.right_ == 1)
	{
		x_val_ += speed;
	}
	if (input_type_.up_ == 1)
	{
		y_val_ -= speed;
	}
	if (input_type_.down_ == 1)
	{
		y_val_ += speed;
	}
	CheckToMap(map_data);
	CenterEntityOnMap(map_data);
}

void MainObject::CenterEntityOnMap(Map &map_data)
{
	// Neu nhan vat di chuyen den vi tri nua ban do thi di chuyen map theo nhan vat
	map_data.start_x_ = x_pos_ - (SCREEN_WIDTH / 2);
	if (map_data.start_x_ < 0) // xet nhan vat di chuyen theo chieu ngang
	{
		map_data.start_x_ = 0;
	}
	else if (map_data.start_x_ + SCREEN_WIDTH >= map_data.max_x_)
	{
		map_data.start_x_ = map_data.max_x_ - SCREEN_WIDTH;
	}
	map_data.start_y_ = y_pos_ - (SCREEN_HEIGHT / 2);
	if (map_data.start_y_ < 0) // xet nhan vat di chuyen theo chieu doc
	{
		map_data.start_y_ = 0;
	}
	else if (map_data.start_y_ + SCREEN_HEIGHT >= map_data.max_y_)
	{
		map_data.start_y_ = map_data.max_y_ - SCREEN_HEIGHT;
	}
}

void MainObject::CheckToMap(Map &map_data)
{
	int x1 = (x_pos_ + x_val_) / TILE_SIZE;
	int x2 = (x_pos_ + x_val_ + width - 1) / TILE_SIZE;
	int y1 = (y_pos_ + y_val_) / TILE_SIZE;
	int y2 = (y_pos_ + y_val_ + height - 1) / TILE_SIZE;

	bool is_x_collide = false;
	bool is_y_collide = false;

	// Kiểm tra va chạm theo chiều ngang
	if (x_val_ > 0)
	{ // Di chuyển sang phải
		if (map_data.tile[y1][x2] == BLANK_TILE || map_data.tile[y2][x2] == BLANK_TILE)
		{
			x_pos_ = x2 * TILE_SIZE - width; // Điều chỉnh vị trí nhân vật để tránh va chạm
			x_val_ = 0;						 // Dừng di chuyển theo chiều ngang
			is_x_collide = true;
		}
	}
	else if (x_val_ < 0)
	{ // Di chuyển sang trái
		if (map_data.tile[y1][x1] == BLANK_TILE || map_data.tile[y2][x1] == BLANK_TILE)
		{
			x_pos_ = (x1 + 1) * TILE_SIZE; // Điều chỉnh vị trí nhân vật để tránh va chạm
			x_val_ = 0;					   // Dừng di chuyển theo chiều ngang
			is_x_collide = true;
		}
	}

	// Kiểm tra va chạm theo chiều dọc
	if (y_val_ > 0)
	{ // Di chuyển xuống
		if (map_data.tile[y2][x1] == BLANK_TILE || map_data.tile[y2][x2] == BLANK_TILE)
		{
			y_pos_ = y2 * TILE_SIZE - height; // Điều chỉnh vị trí nhân vật để tránh va chạm
			y_val_ = 0;						  // Dừng di chuyển theo chiều dọc
			is_y_collide = true;
		}
	}
	else if (y_val_ < 0)
	{ // Di chuyển lên
		if (map_data.tile[y1][x1] == BLANK_TILE || map_data.tile[y1][x2] == BLANK_TILE)
		{
			y_pos_ = (y1 + 1) * TILE_SIZE; // Điều chỉnh vị trí nhân vật để tránh va chạm
			y_val_ = 0;					   // Dừng di chuyển theo chiều dọc
			is_y_collide = true;
		}
	}

	// Nếu có va chạm theo cả hai chiều, không cập nhật vị trí
	if (is_x_collide && is_y_collide)
	{
		return;
	}

	// Cập nhật vị trí nhân vật sau khi kiểm tra va chạm
	x_pos_ += x_val_;
	y_pos_ += y_val_;

	// Kiểm tra giới hạn của bản đồ
	if (x_pos_ < 0)
	{
		x_pos_ = 0;
		x_val_ = 0;
	}
	else if (x_pos_ + width > map_data.max_x_)
	{
		x_pos_ = map_data.max_x_ - width;
		x_val_ = 0;
	}

	if (y_pos_ < 0)
	{
		y_pos_ = 0;
		y_val_ = 0;
	}
	else if (y_pos_ + height > map_data.max_y_)
	{
		y_pos_ = map_data.max_y_ - height;
		y_val_ = 0;
	}
}

bool MainObject::CheckVaCham(Map &map_data, const int &KIEMTRA, const int &moi)
{
	int x1 = 0;
	int y1 = 0;
	int x2 = 0;
	int y2 = 0;

	int height_min = height < TILE_SIZE ? height : TILE_SIZE;
	x1 = (x_pos_ + x_val_) / TILE_SIZE;
	x2 = (x_pos_ + x_val_ + width - 1) / TILE_SIZE;

	y1 = (y_pos_ + y_val_) / TILE_SIZE;
	y2 = (y_pos_ + y_val_ + height_min - 1) / TILE_SIZE;

	if (x1 >= 0 && x2 < MAX_MAP_X && y1 > 0 && y2 < MAX_MAP_Y)
	{
		if (x_val_ > 0) // vat dang di chuyen tien sang phai
		{
			if (map_data.tile[y1][x2] == KIEMTRA)
			{
				map_data.tile[y1][x2] = moi;
				return true;
			}
			else if (map_data.tile[y2][x2] == KIEMTRA)
			{
				map_data.tile[y2][x2] = moi;
				return true;
			}
		}
		else if (x_val_ < 0)
		{
			if (map_data.tile[y1][x1] == KIEMTRA)
			{
				map_data.tile[y1][x1] = moi;
				return true;
			}
			else if (map_data.tile[y2][x1] == KIEMTRA)
			{
				map_data.tile[y2][x1] = moi;
				return true;
			}
		}
	}

	int width_min = width < TILE_SIZE ? width : TILE_SIZE;
	x1 = x_pos_ / TILE_SIZE;
	x2 = (x_pos_ + width_min) / TILE_SIZE;

	y1 = (y_pos_ + y_val_) / TILE_SIZE;
	y2 = (y_pos_ + y_val_ + height - 1) / TILE_SIZE;

	if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
	{
		if (y_val_ > 0)
		{
			if (map_data.tile[y2][x1] == KIEMTRA)
			{
				map_data.tile[y2][x1] = moi;
				return true;
			}
			else if (map_data.tile[y2][x2] == KIEMTRA)
			{
				map_data.tile[y2][x2] = moi;
				return true;
			}
		}
		if (y_val_ < 0)
		{
			if (map_data.tile[y1][x1] == KIEMTRA)
			{
				map_data.tile[y1][x1] = moi;
				return true;
			}
			else if (map_data.tile[y1][x2] == KIEMTRA)
			{
				map_data.tile[y1][x2] = moi;
				return true;
			}
		}
	}
	x_pos_ += x_val_;
	y_pos_ += y_val_;
	return false;
}

bool MainObject::checktaodoc(Map &map_data, const int &TAODOC, const int &moi)
{
	bool a = CheckVaCham(map_data, TAODOC, moi);
	return a;
}

bool MainObject::checktaixiu(Map &map_data, const int &KIEMTRA)
{
	int x1 = 0;
	int y1 = 0;
	int x2 = 0;
	int y2 = 0;
	bool isCollided = false;
	int height_min = height < TILE_SIZE ? height : TILE_SIZE;
	x1 = (x_pos_ + x_val_) / TILE_SIZE;
	x2 = (x_pos_ + x_val_ + width - 1) / TILE_SIZE;

	y1 = (y_pos_ + y_val_) / TILE_SIZE;
	y2 = (y_pos_ + y_val_ + height_min - 1) / TILE_SIZE;

	if (x1 >= 0 && x2 < MAX_MAP_X && y1 > 0 && y2 < MAX_MAP_Y)
	{
		if (x_val_ > 0) // vat dang di chuyen tien sang phai
		{
			if (map_data.tile[y1][x2] == KIEMTRA)
			{

				isCollided = true;
			}
			else if (map_data.tile[y2][x2] == KIEMTRA)
			{

				isCollided = true;
			}
		}
		else if (x_val_ < 0)
		{
			if (map_data.tile[y1][x1] == KIEMTRA)
			{

				isCollided = true;
			}
			else if (map_data.tile[y2][x1] == KIEMTRA)
			{

				isCollided = true;
			}
		}
	}

	int width_min = width < TILE_SIZE ? width : TILE_SIZE;
	x1 = x_pos_ / TILE_SIZE;
	x2 = (x_pos_ + width_min) / TILE_SIZE;

	y1 = (y_pos_ + y_val_) / TILE_SIZE;
	y2 = (y_pos_ + y_val_ + height - 1) / TILE_SIZE;

	if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
	{
		if (y_val_ > 0)
		{
			if (map_data.tile[y2][x1] == KIEMTRA)
			{

				isCollided = true;
			}
			else if (map_data.tile[y2][x2] == KIEMTRA)
			{

				isCollided = true;
			}
		}
		if (y_val_ < 0)
		{
			if (map_data.tile[y1][x1] == KIEMTRA)
			{

				isCollided = true;
			}
			else if (map_data.tile[y1][x2] == KIEMTRA)
			{

				isCollided = true;
			}
		}
	}
	if (!isCollided)
	{

		x_pos_ += x_val_;
		y_pos_ += y_val_;
	}
	return isCollided;
}

bool MainObject::checkhoiphuc(Map &map_data, const int &HOIPHUC, const int &moi)
{
	bool a = CheckVaCham(map_data, HOIPHUC, moi);
	return a;
}

bool MainObject::checkbom(Map &map_data, const int &BOM, const int &moi)
{
	bool a = CheckVaCham(map_data, BOM, moi);
	return a;
}

bool MainObject::checksieuhoiphuc(Map &map_data, const int &SIEUHOIPHUC, const int &moi)
{
	bool a = CheckVaCham(map_data, SIEUHOIPHUC, moi);
	return a;
}
