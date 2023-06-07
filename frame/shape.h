#ifndef _SHAPE_H_
#define _SHAPE_H_


#define M_PI       3.14159265358979323846   // pi
#include <stdbool.h>

#include "genlib.h"


void InitColor(void);							//innitialize color

typedef struct Node {
	double x, y;
}node;
typedef struct Line {
	node start, end;
}line;
typedef struct Tangram {
	bool isFilled;		// 0-not filled 1-filled
	int shape;			// 0-triangle  1-box  2-parallelogram 3-map
	char color[20];		// ͼ�ε���ɫ
	char fix_color[20];	// �̶�����ɫ
	double pX, pY, width, height;
	/*
		pX, pY is the left bottom point(triangle,parallelogram),middle point(box)
		width, height is the width and height of the shape
		���������У�width�ǶԽ���
	*/
	int Pensize;					//���ʴ�ϸ
	int angle;						//��ת�Ƕ� 0,45,90,135,180,225,270,315
	node vertex[20];				//ͼ�εĶ�������
	line edge[20];					//ͼ�εı�
	bool isSelected;				//�Ƿ�ѡ��
	struct Tangram* next, * last;	//ָ����һ������һ��ͼ�ε�ָ��
	int vertexNum;					//������
	int map_number;					//��ͼ���
}Shape;//�洢ͼ�εĽṹ��


void DrawShape(Shape* t);//��ͼ��
Shape *inventShape(bool fill, int shapetype, char * _color,
	double px, double py, double w, double h,int angle,int Pensize, ... );//����ͼ��
void Initshape(void);							//��ʼ���߸����ɰ�ͼ��
void delete_shape(void);						//ɾ��ͼ��
bool isInShape(Shape* t, double x, double y);	//�жϵ��Ƿ���ͼ����
#endif // !_SHAPE_H_
