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
	//score += rand() % 10;
	Shape* li = inventShape(1, -1, "Red", 8, 5, 1, 1, 1, 1);			//平行四边形
	inventShape(1, -1, "Red", 8, 4, 1, 1, 1, 1);			//平行四边形
	  node a, b;
	  a.x = 0.0;
	  a.y = 0.0;
	  b.x = 1.0;
	  b.y = 1.0;
	  score = DistanceBetweenPoints(&a, &b);
	 //MoveToNearestPoint(&a, &b, li);
	display();
}