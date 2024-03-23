#include "stdafx.h"
#include "BaseObject.h"


using namespace std;


BaseObject::BaseObject(){
	p_object = NULL;
	rect_.x=0;
	rect_.y=0;
	rect_.h=0;
	rect_.w=0;
}

BaseObject::~BaseObject(){
	Free();
}

bool BaseObject::LoadImg(std::string path,SDL_Renderer* screen){
	SDL_Texture* new_texture = NULL;
	// ham doc tam anh tu duong dan path
	SDL_Surface* load_surface = IMG_Load(path.c_str());
	// ham IMG se tra ve 1 tam anh ta lay surface de giu no
	//ktra xem surface co bang null hay khong 
	if(load_surface != NULL){
		// ham de xoa background cua hinh anh nhan vat(ham se tao mau trong suot cho background bang cach phoi hop 3 mau R G B)
		SDL_SetColorKey(load_surface, SDL_TRUE, SDL_MapRGB(load_surface->format, COLOR_KEY_R, COLOR_KEY_G, COLOR_KEY_B));
		//ham chuyen surface thanh texture
		new_texture = SDL_CreateTextureFromSurface(screen, load_surface);
		// tao mot texture moi co du lieu tu surface truyen vao. no duoc ve len man hinh thong qua screen
		if(new_texture != NULL){
			rect_.w = load_surface->w;
			rect_.h = load_surface->h;
			// truyen thong so va thuoc tinh tam anh vao rect_ gan thong so cho doi tuong sau khi lay duoc thong tin anh thanh cong 
		}
		SDL_FreeSurface(load_surface);//xoa load_surface sau khi da su dung xong
	}
	p_object = new_texture;
	return p_object != NULL; // ban dau ktra xem p_o vaf NULL co bang nhau hay khong, neu p khac null lap tuc return1 
}

//tao nen laod tam anh len
void BaseObject::Render(SDL_Renderer* des, const SDL_Rect* clip){
	SDL_Rect renderquad ={rect_.x, rect_.y, rect_.w, rect_.h};
	// lay kic thuoc 
	SDL_RenderCopy(des, p_object, clip, &renderquad);// day thong so cuar p len cho des voi kich thuoc va vi tri duoc neu o tren

}

void BaseObject::Free(){
	if(p_object != NULL){
		SDL_DestroyTexture(p_object);
		p_object = NULL;
		rect_.w=0;
		rect_.h=0;
	}
}