/*****************************************************************//**
 * \file   timer.c
 * \brief  ʱ��ص�������ʵ�ֶ�ʱ������
 *		   ���ʱ�䵽�ˣ���Ϸ���������Ҳ���ʧ�ܵ�����
 * 
 * \author Philfan
 * \date   May 2023
 *********************************************************************/
#include "../Header.h"
void timer(int timerID) {
	/**
	 * \brief ʱ��ص�������ʵ�ֶ�ʱ������
	 * \param timerID	��ʱ�����
	 */
	if(timerID == 0)
	{
		if (game_status != 0 ) return;
		current_time -= TIME_INTERVAL/1000;
		if (current_time <= 0)
		{
			game_status = -3;
			mciSendString("open ./file/game_lose.mp3 alias game_lose", NULL, 0, NULL);
			mciSendString("play game_lose", NULL, 0, NULL);     //���ųɹ�������
		}
		display();
	}
}