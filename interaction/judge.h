#ifndef _JUDGE_H_
#define JUDGE_H
#include "../frame/shape.h"

//bool Game_win(void);
//double CalculateArea(Shape* shape1, Shape* shape2);
//double CalculatePolygonArea(const Shape* shape);//ʹ��Green��ʽ�����������
//double DistanceBetweenPoints(node* shapeNode, node* mapNode);//������mouseevent.c
//
//void hint(void);

void judge_complishment();
//�ж�map�Ƿ�tangram��������������ɷ���TRUE,x��map[x]�������������ȡ��һ��map
//�ж�ÿ������εĵ��Ƿ���map��ж�ÿ������εĵ��Ƿ��������������

bool judge_point_in_tangram(node point);    //���߷�,
bool judge_point_in_map(node point);   //�����ͼ����֪����ͼ���ô�����
void test();  //����debug
void finish_animation();
void color_change_all(string color);  // //������tangram��ɫ�ı�
#endif // !_JUDGE_H_
