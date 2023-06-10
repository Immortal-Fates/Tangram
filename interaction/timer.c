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

	current_time -= 0.1;
	
	display();
}