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

	current_time -= 0.1;
	
	display();
}