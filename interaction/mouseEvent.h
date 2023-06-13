#pragma once
#ifndef _MOUSEEVENT_H_
#define MOUSEEVENT_H

#define THRESHOLD 0.15	//吸附阈值
#define CALERROR 0.001		//判定浮点数相等时候的误差

void MouseEventProcess(int x, int y, int button, int event);


int isequal(double a, double b);
//对线的吸附
void SnapToLine(Shape* shape, double threshold);
bool IsParallel(line* line1, line* line2);
double DistanceBetweenLines(line* line1, line* line2);
void MoveToParallelLines(line* line1, line* line2, double distance, Shape* shape);
int Iscrossed(line* line1, line* line2);

//对点的吸附
void SnaptoPoint(Shape* shape, double threshold);
double DistanceBetweenPoints(node* shapeNode, node* mapNode);
void MoveToNearestPoint(node* shapeNode, node* mapnode, Shape* shape);


#endif // !_MOUSEEVENT_H_


