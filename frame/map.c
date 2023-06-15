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
#include "map.h"
#include "../Header.h"

current_map = 0;	//��ǰ��ͼ���
mymap map[100];		//��ͼ����

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
	double x_[9] = { 4.3,6.5,6.15,4.9,5.5,4.5,6.5,5.5 };
	double y_[9] = { 4,4,2.9,4,4.2,4,3,3 };

	//��ʼ����ͼ������
	t->vertexNum = map[MapNumber].vertexNum;
	t->pX = x_[MapNumber];
	t->pY = y_[MapNumber];

	t->angle = 1;
	strcpy(t->color, "#232946");
	t->isFilled = 0;
	t->isSelected = FALSE;
	t->Pensize = 2;
	t->shape = 3;//��ͼ
	t->map_number = MapNumber;
	t->next = t->last = NULL;
	for (int i = 1; i <= 7; i++) {
		t->graphics[i].isvisible = 0;
	}

	//�Ӵ洢�ĵ�ͼ�����ж�ȡ�������꣬������ߵ�����
	for(int i = 0;i <= t->vertexNum-1;i++){				
		t->vertex[i].x = map[MapNumber].vertex[i][0]+t->pX;//!!!!������Ҫ�ѵ�ͼ���������ת��Ϊ�������꣬����������������
		t->vertex[i].y = map[MapNumber].vertex[i][1]+t->pY;
		
	}
	for(int i = 0;i <= t->vertexNum-2;i++){
		t->edge[i].start = t->vertex[i];
		t->edge[i].end = t->vertex[i+1];
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
void InitMap() {
	for (int i = 0; i < MapNumber_MAX; i++) {
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

void DrawSubmap(int MapNumber) {
	/**
	 * \brief ������ʾͼ��
	 * \relates Is_Hint = 1 ������ʾģʽ�� Is_Hint = 0 �ر���ʾģʽ��mouseevent.c�иı�Is_Hint��
	 *
	 *
	 * \param MapNumber
	 */
	if (Is_Hint == 0) return;

	Shape* ttemp = Map_head;
	while (ttemp) {
		if (ttemp->map_number == MapNumber) {
			mapShape = ttemp;
			//FILE* fp;
			//fp = fopen("./file/
			//
			// .txt", "w");
			//fprintf(fp, "%d\n", mapShape->vertexNum);

			int pensize = GetPenSize();
			string pencolor = GetPenColor();

			SetPenColor("Red");
			SetPenSize(3);
			//StartFilledRegion(1);
			for (int i = 1; i <= 7; i++) {
				if (mapShape->graphics[i].isvisible == 0) continue;
				sub_tangram* temp = &mapShape->graphics[i];
				int vertexcount = 3;
				if (i > 5) vertexcount = 4;
				MovePen(temp->vertex[0].x, temp->vertex[0].y);
				for (int i = 0; i < vertexcount - 1; i++) {
					//fprintf(fp, "%lf %lf\n", temp->vertex[i].x, temp->vertex[i].y);
					DrawLine(temp->vertex[i + 1].x - temp->vertex[i].x, temp->vertex[i + 1].y - temp->vertex[i].y);
				}
				DrawLine(temp->vertex[0].x - temp->vertex[vertexcount - 1].x, temp->vertex[0].y - temp->vertex[vertexcount - 1].y);
			}
			//EndFilledRegion();
			SetPenSize(pensize);	//back to system pensize
			SetPenColor(pencolor);	//back to system pencolor

			//fclose(fp);
		}
		ttemp = ttemp->next;
	}

}

void DIYMap() {
	/**
	 * \brief �Զ����ͼ
	 */

	//��headΪͷ����������ȡ��������״��line������ӵ�DIY_headΪͷ��������

	//


	return;
}

