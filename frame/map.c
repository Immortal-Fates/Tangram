/*****************************************************************//**
 * \file   map.c
 * \brief
 *			�������ɰ��problem map
 *			ʹ�ýṹ��洢��ͼ��������꣬���洢��ͼ�ı��
 *			��shape�ṹ�幹����ͼ����״
 *			��¼ÿһ������������ÿһ����
 * \author
 * \date   May 2023
 *********************************************************************/
#include "../Header.h"
#include "map.h"
MapNumber_MAX = 1;  //��ͼ����
current_map = 1;	//��ǰ��ͼ���
mymap map[20];		//��ͼ����
Shape* Map_head = NULL, * Map_tail = NULL;
Shape* mapShape = NULL;//ָ��ǰ��ͼ��ָ��


Shape* CreateMap(int MapNumber) {
	/**
	 * \brief: ���ɵ�ͼ,��¼��ͼ�ı�ţ��������꣬�ߵ�����
	 * 
	 * \param MapNumber: ��ͼ�ı��
	 * \return : ��shape�ṹ�巵�ص�ͼ����״
	 */
	Shape* t = (Shape*)malloc(sizeof(Shape));

	//��ʼ����ͼ������
	t->vertexNum = map[MapNumber].vertexNum;
	t->pX = 4.5;
	t->pY = 4;
	t->angle = 1;
	strcpy(t->color, "Black");
	t->isFilled = 0;
	t->isSelected = FALSE;
	t->Pensize = 1;
	t->shape = 3;//��ͼ
	t->map_number = MapNumber;
	t->next = t->last = NULL;

	//�Ӵ洢�ĵ�ͼ�����ж�ȡ�������꣬������ߵ�����
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

	//�洢�����ͼ��������
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
	 * \brief: ������ͼ
	 * \param MapNumber: ��ͼ�ı��
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
	//�洢��ͼ�ĺ�������¼ÿһ����ͼ���ж��������
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

