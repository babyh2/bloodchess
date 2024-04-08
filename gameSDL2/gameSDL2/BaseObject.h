#ifndef BASEOBJECT_H
#define BASEOBJECT_H




#include"Commonfunc.h"
class BaseObject{
public:
	BaseObject();
	~BaseObject();
	void SetRect(const int &a, const int &b){
		rect_.x=a;
		rect_.y=b;
	}// ham gan gia tri cho rect
	SDL_Rect GetRect() const{
		return rect_;
	}// ham lay gia tri cua rect_
	SDL_Texture* GetObject() const {
		return p_object;
	}// ham lay gia tri cua p_object

	// ham co tac dung load anh bit map len doi tuong p_object
	// path:duong dan cho tam anh
	//screen con tro tro den doi tuong rendenrer duoc dung de ve anh len man hinh
	virtual bool LoadImg(std::string path,SDL_Renderer* screen);
    // su dung des de ve len man hinh 
	// neu gia tri clip duoc dua vao khac null no se chi ve tren phan hinh anh nam trong vung clip
	// neu clip == null no se ve toan bo hinh anh len man hinh

	void Render(SDL_Renderer* des, const SDL_Rect* clip = NULL);
	void Free();
protected:
	SDL_Texture* p_object; // bien luu tru hinh anh
	SDL_Rect rect_; // bien luu tru kich thuoc tam anh

};



#endif