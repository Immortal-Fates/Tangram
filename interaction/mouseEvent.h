#pragma once
#ifndef _MOUSEEVENT_H_
#define MOUSEEVENT_H
#include "../Header.h"
#define THRESHOLD 0.5

void MouseEventProcess(int x, int y, int button, int event);

//对线的吸附
void SnapToLine(Shape* shape, double threshold);
bool IsParallel(line* line1, line* line2);
double DistanceBetweenLines(line* line1, line* line2);
void MoveToParallelLines(line* line1, line* line2, double distance, Shape* shape);
//对点的吸附
void SnaptoPoint(Shape* shape, double threshold);
double DistanceBetweenPoints(node* shapeNode, node* mapNode);
void MoveToNearestPoint(node* shapeNode, node* mapnode, Shape* shape);


#endif // !_MOUSEEVENT_H_


