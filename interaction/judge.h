#ifndef _JUDGE_H_
#define JUDGE_H
#include "../frame/shape.h"

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



#endif // !_JUDGE_H_
