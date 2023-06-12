#pragma once
#ifndef _MAP_H_
#define MAP_H
#include "shape.h"
#include "../Header.h"
/*Part 地图的生成*/
typedef struct MAP {
	int vertexNum;
	double vertex[100][2];
}mymap;


extern int current_map;
extern Shape* Map_head, * Map_tail;
mymap map[100];

void InitMap();
Shape* CreateMap(int MapNumber);
void DrawMap(int MapNumber);
void MapData(void);


/*Part2 自定义地图*/
void DIY_map(void);

/*Part3 用户提示*/
void DrawSubmap(int MapNumber);

//todo: 坐标的更新
#endif // !_MAP_H_



