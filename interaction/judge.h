#ifndef _JUDGE_H_
#define JUDGE_H

#include "../frame/shape.h"
#include"../include/linkedlist.h"

/*Part1 使用 面积法 判定游戏结束*/
bool Game_win(void);
double CalculateArea(Shape* shape1, Shape* shape2);
double CalculatePolygonArea(const Shape* shape);//使用Green公式计算多边形面积
double DistanceBetweenPoints(node* shapeNode, node* mapNode);//定义在mouseevent.c

/*Part2 使用 顶点判断 + 射线法 判定游戏结束*/
void judge_complishment();
//判断map是否被tangram填满，若是则完成返回TRUE,x是map[x]数组的索引，读取哪一个map
//判断每个多边形的点是否在map里，判断每个多边形的点是否不在其他多边形内

bool judge_point_in_tangram(node point);    //射线法,
bool judge_point_in_map(node point);   //传入地图（不知道地图的用处？）
bool dcmp(double x);

bool Is_superposition(linkedlistADT node1, linkedlistADT node2);
void add_line(linkedlistADT node1, linkedlistADT node2);
bool Is_same_line(void* obj1, void* obj2);
bool Is_psame_line(void* obj1, void* obj2);
bool have_same_point(void* obj1, void* obj2);

#endif // !_JUDGE_H_
