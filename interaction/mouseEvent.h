#pragma once
#ifndef _MOUSEEVENT_H_
#define MOUSEEVENT_H
#include "../Header.h"

void MouseEventProcess(int x, int y, int button, int event);
void SnapToLine(Shape* shape, double threshold);
bool IsParallel(line* line1, line* line2);
double DistanceBetweenLines(line* line1, line* line2);
void MoveToParallelLines(line* line1, line* line2, double distance, Shape* shape);

typedef struct shortest_move_path {
	line* mapline;
	line* shapeline;
	Shape* tempshape;
	double distance;
}SMP;
#endif // !_MOUSEEVENT_H_


