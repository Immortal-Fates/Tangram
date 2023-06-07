/*****************************************************************//**
 * \file   timer.c
 * \brief  时间回调函数，实现定时器功能
 * 
 * \author Philfan
 * \date   May 2023
 *********************************************************************/
#include "../Header.h"
void timer(int timerID) {
	/**
	 * \brief 时间回调函数，实现定时器功能
	 * 
	 * \param timerID	计时器序号
	 */
	if (game_status) return;

	current_time += 0.1;
	score += rand() % 10;
	Shape* li = inventShape(1, -1, "Red", 8, 5, 1, 1, 1, 1);			//平行四边形
	  inventShape(1, -1, colorList[8], 7,4, 1, 1, 1, 1);			//平行四边形
	line m, n;
	m.start.x = 8;
	m.start.y = 2;
	m.end.x = 8;
	m.end.y = 1;
	n.start.x = 1.3;
	n.start.y = 3;
	n.end.x =1.5;
	n.end.y = 5;
	line *mm = &m, *nn = &n;
	//MoveToParallelLines(nn,mm, 0, li);
	//score = DistanceBetweenLines(mm, nn);
	display();
}