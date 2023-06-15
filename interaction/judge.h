#ifndef _JUDGE_H_
#define JUDGE_H

#include "../frame/shape.h"
#include"../include/linkedlist.h"

/*Part1 ʹ�� ����� �ж���Ϸ����*/
bool Game_win(void);
double CalculateArea(Shape* shape1, Shape* shape2);
double CalculatePolygonArea(const Shape* shape);//ʹ��Green��ʽ�����������
double DistanceBetweenPoints(node* shapeNode, node* mapNode);//������mouseevent.c

/*Part2 ʹ�� �����ж� + ���߷� �ж���Ϸ����*/
void judge_complishment();
//�ж�map�Ƿ�tangram��������������ɷ���TRUE,x��map[x]�������������ȡ��һ��map
//�ж�ÿ������εĵ��Ƿ���map��ж�ÿ������εĵ��Ƿ��������������

bool judge_point_in_tangram(node point);    //���߷�,
bool judge_point_in_map(node point);   //�����ͼ����֪����ͼ���ô�����
bool dcmp(double x);

bool Is_superposition(linkedlistADT node1, linkedlistADT node2);
void add_line(linkedlistADT node1, linkedlistADT node2);
bool Is_same_line(void* obj1, void* obj2);
bool Is_psame_line(void* obj1, void* obj2);
bool have_same_point(void* obj1, void* obj2);

#endif // !_JUDGE_H_
