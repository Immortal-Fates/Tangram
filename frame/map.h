#pragma once
#ifndef _MAP_H_
#define MAP_H
#include "shape.h"
//#include"../interaction/judge.h"
#include"../include/linkedlist.h"

/*Part ��ͼ������*/
typedef struct MAP {
	int vertexNum;
	double vertex[200][2];
	double px;
	double py;
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
void DIY_map_anmination(int issuccess);

/*Part3 �û���ʾ*/
void DrawSubmap(int MapNumber);
void save_subMap(int MapNumber);

void create_submap_line_link();
void create_submap_line(void);
void create_submap_vertex(void);

#endif // !_MAP_H_



