/*****************************************************************//**
 * \file   timer.c
 * \brief  时间回调函数，实现定时器功能
 *		   如果时间到了，游戏结束，并且播放失败的音乐
 * 
 * \author Philfan
 * \date   May 2023
 *********************************************************************/
#include "../Header.h"
void timer(int timerID) {
	/**
	 * \brief 时间回调函数，实现定时器功能
	 * \param timerID	计时器序号
	 */
	switch (timerID) {
		case 0:
		{
			if (game_status != 0) return;

			current_time -= 0.1;
			if (current_time <= 0)
			{
				game_status = -3;
				mciSendString("open ./file/game_lose.mp3 alias game_lose", NULL, 0, NULL);
				mciSendString("play game_lose", NULL, 0, NULL);     //播放成功的音乐
			}
			display();
			break;
		}
		case 1:
		{
			if (game_status - 2) {
				colorindex = (colorindex + 1) % 5;
				display();
				break;
			}
		}
	}
}