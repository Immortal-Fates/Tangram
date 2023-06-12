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
mymap map[100];

void InitMap();
Shape* CreateMap(int MapNumber);
void DrawMap(int MapNumber);
void MapData(void);


/*Part2 �Զ����ͼ*/
void DIY_map(void);

/*Part3 �û���ʾ*/
void DrawSubmap(int MapNumber);

//todo: ����ĸ���
#endif // !_MAP_H_



