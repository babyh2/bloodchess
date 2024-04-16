#include"stdafx.h"
#include"Game_map.h"

void GameMap::LoadMap(char* name){
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

void GameMap::LoadTiles(SDL_Renderer* screen){
	char file_img[30];
	FILE* fp=NULL;
	for(int i=0;i<MAX_TILES;i++){
		sprintf_s(file_img,"map/%d.jpg",i);

		fopen_s(&fp, file_img,"rb");
		if(fp==NULL) continue;
		fclose(fp);
		tile_mat[i].LoadImg(file_img, screen);

	}
	
}



void GameMap::DrawMap(SDL_Renderer* screen){
	int x1=0;
	int x2=0;
	int y1=0;
	int y2=0;// cac gia tri vua khai bao de xac dinh pham vi can ve cua ban do tren man hinh
	int map_x = 0;
	int map_y = 0;
	/* map_x va map_y dung de xac ding vi tri tren ma tran de lay gia tri tuong ung voi anh
	   de dua anh len man hinh
	*/
	map_x = game_map_.start_x_/TILE_SIZE;
	x1=(game_map_.start_x_%TILE_SIZE)*-1;
	x2=x1+SCREEN_WIDTH+(x1==0 ? 0 : TILE_SIZE);

	map_y = game_map_.start_y_/TILE_SIZE;
	y1=(game_map_.start_y_%TILE_SIZE)*-1;
	y2=y1+SCREEN_HEIGHT+(y1==0 ? 0 : TILE_SIZE);

	for(int i=y1;i<y2;i+=TILE_SIZE){
		map_x=game_map_.start_x_/TILE_SIZE;
		for(int j=x1;j<x2;j+=TILE_SIZE)
		{
			int val = game_map_.tile[map_y][map_x];
			// lay gia tri tuong ung tu ma tran sau do luu vao bien val de xac dinh hinh anh can ve
			if(val>0){ // val>0 tuc co anh can ve len man hinh neu val=0 thi k can ve gi
				tile_mat[val].SetRect(j,i); // thiet lap vi tri cua anh
				tile_mat[val].Render(screen); // dua anh len man hinh
			}
			map_x++;
		}
		map_y++;
	}

}

void GameMap::KhoiPhucMap(Map& map_data)
{
	for(int i=0;i<MAX_MAP_Y;i++)
	{
		for(int j=0;j<MAX_MAP_X;j++)
		{
			switch(map_data.tile[i][j])
			{
			case MOI_TAO_DOC:
				{
					map_data.tile[i][j]=BLANK_TAODOC;
					break;
				}
			case MOI_HOI_PHUC:
				{
					map_data.tile[i][j]=BLANK_HOIPHUC;
					break;
				}
			case MOI_BOM:
				{
					map_data.tile[i][j]=BLANK_BOM;
					break;
				}
			case MOI_SIEU_HOI_PHUC:
				{
					map_data.tile[i][j]=BLANK_SIEUHOIPHUC;
					break;
				}
			case MOI_TAI_XIU:
				{
					map_data.tile[i][j]=BLANK_TAIXIU;
					break;
				}
			default: break;
			};
		}
	}
}