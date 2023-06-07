/*****************************************************************//**
 * \file   map.c
 * \brief
 *			生成七巧板的problem map
 *			使用结构体存储地图顶点的坐标，并存储地图的编号
 *			用shape结构体构建地图的形状
 *			记录每一个顶点的坐标和每一条边
 * \author
 * \date   May 2023
 *********************************************************************/
#include "../Header.h"
#include "map.h"
MapNumber_MAX = 1;  //地图数量
current_map = 1;	//当前地图编号
mymap map[20];		//地图数据
Shape* Map_head = NULL, * Map_tail = NULL;
Shape* mapShape = NULL;//指向当前地图的指针


Shape* CreateMap(int MapNumber) {
	/**
	 * \brief: 生成地图,记录地图的编号，顶点坐标，边的数据
	 * 
	 * \param MapNumber: 地图的编号
	 * \return : 以shape结构体返回地图的形状
	 */
	Shape* t = (Shape*)malloc(sizeof(Shape));

	//初始化地图的数据
	t->vertexNum = map[MapNumber].vertexNum;
	t->pX = 4.5;
	t->pY = 4;
	t->angle = 1;
	strcpy(t->color, "Black");
	t->isFilled = 0;
	t->isSelected = FALSE;
	t->Pensize = 1;
	t->shape = 3;//地图
	t->map_number = MapNumber;
	t->next = t->last = NULL;

	//从存储的地图数据中读取顶点坐标，计算出边的数据
	for(int i = 0;i <= t->vertexNum-1;i++){				
		t->vertex[i].x = map[MapNumber].vertex[i][0];
		t->vertex[i].y = map[MapNumber].vertex[i][1];
		if (i >= 1) {
			t->edge[i - 1].start = t->vertex[i-1];
			t->edge[i - 1].end = t->vertex[i];
		}
	}
	t->edge[t->vertexNum-1].start = t->vertex[t->vertexNum-1];
	t->edge[t->vertexNum-1].end = t->vertex[0];

	//存储进入地图的链表中
	if (!Map_head) 
		Map_head = Map_tail = t;
	else {
		Map_tail->next = t;
		t->last = Map_tail;
		Map_tail = t;
	}
	return t;
}
void InitMap(int t) {
	//MapData();
	GenerateMap();
	for (int i = 1; i <= t; i++) {
		CreateMap(i);
	}
	
}

void DrawMap(int MapNumber) {
	/**
	 * \brief: 画出地图
	 * \param MapNumber: 地图的编号
	 */
	Shape* temp = Map_head;
	while (temp) {
		if (temp->map_number == MapNumber) { 
			mapShape = temp;
			//StartFilledRegion(1);
			int pensize = GetPenSize();
			string pencolor = GetPenColor();
			SetPenColor(temp->color);
			SetPenSize(temp->Pensize);
			MovePen(temp->pX, temp->pY);
			for (int i = 0; i <= temp->vertexNum-1; i++) {
				DrawLine(temp->edge[i].end.x - temp->edge[i].start.x, temp->edge[i].end.y - temp->edge[i].start.y);
			}
			//EndFilledRegion();
			SetPenSize(pensize);	//back to system pensize
			SetPenColor(pencolor);	//back to system pencolor
		}
		temp = temp->next;
	}
}

void MapData(void) {
	//存储地图的函数，记录每一个地图所有顶点的坐标
	map[1].vertexNum = 4;
	map[1].vertex[0][0] = 0;
	map[1].vertex[0][1] = 0;
	map[1].vertex[1][0] = 2 * sqrt(2);
	map[1].vertex[1][1] = 0;
	map[1].vertex[2][0] = 2 * sqrt(2);
	map[1].vertex[2][1] = 2 * sqrt(2);
	map[1].vertex[3][0] = 0;
	map[1].vertex[3][1] = 2 * sqrt(2);
}

