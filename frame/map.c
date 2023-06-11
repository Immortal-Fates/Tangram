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

current_map = 0;	//��ǰ��ͼ���
mymap map[20];		//��ͼ����
Shape* Map_head = NULL, * Map_tail = NULL;
Shape* mapShape = NULL;//ָ��ǰ��ͼ��ָ��
int totalVertices;
node allVertices[140];
node contourCoords[140];

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
void InitMap(int t) {
	for (int i = 0; i <= MapNumber_MAX-1; i++) {
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


void extractVertices(const Shape* head, node* allVertices, int* totalVertices) {
	/**
	 * \brief ����������ȡ���ж��㵽��������
	 * \param head: �����ͷָ��
	 * \param allVertices: �洢���ж��������
	 * \param totalVertices: �洢���������ı�����ָ��
	 */
	Shape* current = head;
	int vertexIndex = 0;

	while (current) {
		for (int i = 0; i < current->vertexNum; i++) {
			allVertices[vertexIndex] = current->vertex[i];
			vertexIndex++;
		}
		current = current->next;
	}

	*totalVertices = vertexIndex;
}


bool isLeftTurn(const node* p1, const node* p2, const node* p3) {
	/**
	 * \brief �ж��������Ƿ��γ���ʱ�뷽��
	 * \param p1, p2, p3: ���жϵ�������
	 * \return true����ʱ�뷽��false��˳ʱ�뷽�����
	 */
	double crossProduct = (p2->x - p1->x) * (p3->y - p1->y) - (p2->y - p1->y) * (p3->x - p1->x);
	return crossProduct > 0;
}


void getContourCoordinates(const node* allVertices, int totalVertices, node* contourCoords) {
	/**
	 * \brief ������ʱ�뷽�������ϵ�����
	 * \param allVertices: ���ж��������
	 * \param totalVertices: ���������
	 * \param contourCoords: �洢���������������
	 */
	int contourIndex = 0;

	// �ҵ�����ߵĶ�����Ϊ���������
	int startIndex = 0;
	for (int i = 1; i < totalVertices; i++) {
		if (allVertices[i].x < allVertices[startIndex].x) {
			startIndex = i;
		}
	}

	// ����ʱ�뷽�����������ϵ�����
	int currentIndex = startIndex;
	int nextIndex;

	do {
		contourCoords[contourIndex] = allVertices[currentIndex];
		contourIndex++;

		nextIndex = (currentIndex + 1) % totalVertices;

		for (int i = 0; i < totalVertices; i++) {
			if (isLeftTurn(&allVertices[currentIndex], &allVertices[i], &allVertices[nextIndex])) {
				nextIndex = i;
			}
		}

		currentIndex = nextIndex;
	} while (currentIndex != startIndex);

	// �����һ�����������������
	contourCoords[contourIndex] = allVertices[currentIndex];
}

void DIYMap() {
	/**
	 * \brief �Զ����ͼ
	 */

	// ����������ȡ���ж��㵽��������
	extractVertices(head, allVertices, &totalVertices);
	// �����ʱ�뷽�������ϵ�����
	getContourCoordinates(allVertices, totalVertices, contourCoords);

	
	// ��ӡ��������
	for (int i = 0; i < totalVertices; i++) {
		printf("Coordinate %d: (%lf, %lf)\n", i + 1, contourCoords[i].x, contourCoords[i].y);
	}
	MapNumber_MAX++;


	return 0;
}


