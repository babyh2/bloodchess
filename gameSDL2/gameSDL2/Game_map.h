#ifndef GAME_MAP_H
#define GAME_MAP_H

#define MAX_TILES 20

#include "Commonfunc.h"
#include "BaseObject.h"

class TileMat : public BaseObject
{
public:
	TileMat() { ; }
	~TileMat() { ; }
};

class GameMap
{
public:
	GameMap() { ; }
	~GameMap() { ; }
	void LoadMap(const char *name);		  // doc toan bo thong tin cua file map
	void LoadTiles(SDL_Renderer *screen); // load toan bo hinh anh vao cai tile
	void DrawMap(SDL_Renderer *screen);	  // load hinh anh de xay dung mot map hoan thien
	Map getMap() const { return game_map_; }
	void SetMap(Map &map_data) { game_map_ = map_data; }
	void KhoiPhucMap(Map &map_data);
	void random_vatcan(Map &map_data);

private:
	Map game_map_;
	TileMat tile_mat[MAX_TILES];
};

#endif
