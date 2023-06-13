#pragma once
#ifndef _MOUSEEVENT_H_
#define MOUSEEVENT_H

#define THRESHOLD 0.15	//������ֵ
#define CALERROR 0.001		//�ж����������ʱ������

void MouseEventProcess(int x, int y, int button, int event);


int isequal(double a, double b);
//���ߵ�����
void SnapToLine(Shape* shape, double threshold);
bool IsParallel(line* line1, line* line2);
double DistanceBetweenLines(line* line1, line* line2);
void MoveToParallelLines(line* line1, line* line2, double distance, Shape* shape);
int Iscrossed(line* line1, line* line2);

//�Ե������
void SnaptoPoint(Shape* shape, double threshold);
double DistanceBetweenPoints(node* shapeNode, node* mapNode);
void MoveToNearestPoint(node* shapeNode, node* mapnode, Shape* shape);


#endif // !_MOUSEEVENT_H_


