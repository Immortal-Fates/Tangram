/*****************************************************************//**
 * \file   timer.c
 * \brief  ʱ��ص�������ʵ�ֶ�ʱ������
 * 
 * \author Philfan
 * \date   May 2023
 *********************************************************************/
#include "../Header.h"
void timer(int timerID) {
	/**
	 * \brief ʱ��ص�������ʵ�ֶ�ʱ������
	 * 
	 * \param timerID	��ʱ�����
	 */
	if (game_status) return;

	current_time += 0.1;
	//score += rand() % 10;
	Shape* li = inventShape(1, -1, "Red", 8, 5, 1, 1, 1, 1);			//ƽ���ı���
	inventShape(1, -1, "Red", 8, 4, 1, 1, 1, 1);			//ƽ���ı���
	  node a, b;
	  a.x = 0.0;
	  a.y = 0.0;
	  b.x = 1.0;
	  b.y = 1.0;
	  score = DistanceBetweenPoints(&a, &b);
	 //MoveToNearestPoint(&a, &b, li);
	display();
}