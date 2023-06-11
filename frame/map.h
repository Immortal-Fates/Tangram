#pragma once
#ifndef _MAP_H_
#define MAP_H
#include "shape.h"
#include "../Header.h"

typedef struct MAP {
	int vertexNum;
	double vertex[100][2];
}mymap;


extern int current_map;
extern Shape* Map_head, * Map_tail;
mymap map[20];

void InitMap(int MapNumber_MAX);
Shape* CreateMap(int MapNumber);
void DrawMap(int MapNumber);
void MapData(void);

void DIY_map(void);
#endif // !_MAP_H_



