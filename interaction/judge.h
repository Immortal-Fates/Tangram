#ifndef _JUDGE_H_
#define JUDGE_H
#include "../frame/shape.h"

bool Game_win(void);
double CalculateArea(Shape* shape1, Shape* shape2);
double CalculatePolygonArea(const Shape* shape);//使用Green公式计算多边形面积
double DistanceBetweenPoints(node* shapeNode, node* mapNode);//定义在mouseevent.c

void hint(void);
#endif // !_JUDGE_H_
