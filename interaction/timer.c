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
	//Shape* li = inventShape(1, -1, "Red", 8, 5, 1, 1, 1, 1);			//ƽ���ı���
	//  inventShape(1, -1, colorList[8], 7,3, 1, 1, 1, 1);			//ƽ���ı���
	//line m, n;
	//m.start.x = 8;
	//m.start.y = 5;
	//m.end.x = 9;
	//m.end.y = 5;
	//n.start.x = 1.3;
	//n.start.y = 3;
	//n.end.x =3.3;
	//n.end.y = 3;
	//line *mm = &m, *nn = &n;
	//MoveToParallelLines(nn,mm, DistanceBetweenLines(mm, nn), li);
	//score = DistanceBetweenLines(mm, nn);
	display();
}