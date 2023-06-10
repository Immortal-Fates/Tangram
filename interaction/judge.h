#ifndef _JUDGE_H_
#define JUDGE_H
#include "../frame/shape.h"

//bool Game_win(void);
//double CalculateArea(Shape* shape1, Shape* shape2);
//double CalculatePolygonArea(const Shape* shape);//使用Green公式计算多边形面积
//double DistanceBetweenPoints(node* shapeNode, node* mapNode);//定义在mouseevent.c
//
//void hint(void);

void judge_complishment();
//判断map是否被tangram填满，若是则完成返回TRUE,x是map[x]数组的索引，读取哪一个map
//判断每个多边形的点是否在map里，判断每个多边形的点是否不在其他多边形内

bool judge_point_in_tangram(node point);    //射线法,
bool judge_point_in_map(node point);   //传入地图（不知道地图的用处？）
void test();  //用于debug
void finish_animation();
void color_change_all(string color);  // //让所有tangram颜色改变
#endif // !_JUDGE_H_
