#ifndef GAME_MAP_H
#define GAME_MAP_H

#define MAX_TILES 20


#include"Commonfunc.h"
#include"BaseObject.h"

class TileMat : public BaseObject{
public:
	TileMat() {;}
	~TileMat() {;}
};

class GameMap{
public:
	GameMap() {;}
	~GameMap() {;}
	void LoadMap(char* name);// doc toan bo thong tin cua file map
	void LoadTiles(SDL_Renderer* screen); // load toan bo hinh anh vao cai tile
	void DrawMap(SDL_Renderer* screen); // load hinh anh de xay dung mot map hoan thien


	
private: 
	Map game_map_;
	TileMat tile_mat[MAX_TILES];

};




#endif
