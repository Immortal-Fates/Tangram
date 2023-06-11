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
	if(timerID == 0)
	{
		if (game_status != 0 ) return;

		current_time -= 0.1;
		
		display();
		/*int i = (int)(current_time * 10) % 5;
		switch (i) {
			case 0: drawBox(6.5, 4.5, 1.0, 1.0, 0, "Tangram", "S", "blue"); break;
			case 1: drawBox(6.5, 4.5, 1.0, 1.0, 0, "Tangram", "S", "yellow"); break;
			case 2: drawBox(6.5, 4.5, 1.0, 1.0, 0, "Tangram", "S", "green"); break;
			case 3: drawBox(6.5, 4.5, 1.0, 1.0, 0, "Tangram", "S", "black"); break;
			case 4: drawBox(6.5, 4.5, 1.0, 1.0, 0, "Tangram", "S", "red"); break;
		}*/

	}
}