#ifndef _JUDGE_H_
#define JUDGE_H
#include "../frame/shape.h"

bool Game_win(void);
double CalculateArea(Shape* shape1, Shape* shape2);
double CalculatePolygonArea(const Shape* shape);//ʹ��Green��ʽ�����������
double DistanceBetweenPoints(node* shapeNode, node* mapNode);//������mouseevent.c

void hint(void);
#endif // !_JUDGE_H_
