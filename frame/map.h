#pragma once
#ifndef _MAP_H_
#define MAP_H
#include "shape.h"
#include "../Header.h"
/*Part ��ͼ������*/
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


/*Part2 �Զ����ͼ*/
void DIY_map(void);

/*Part3 �û���ʾ*/
void DrawSubmap(sub_tangram* temp);
#endif // !_MAP_H_



