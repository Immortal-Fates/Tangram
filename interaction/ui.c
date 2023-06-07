/*****************************************************************//**
 * \file   ui.c
 * \brief  ����ʵ����Ϸ����Ļ��ƣ�������Ϸ�İ�ť����Ϸ��Ϣ����ʾ
 *			ʹ��imgui.h����а�ť�Ļ���
 * 
 * \author Philfan
 * \date   May 2023
 *********************************************************************/
#include "../Header.h"
#include "ui.h"


void InitButton(void) {
	SetPenColor("Black");
	MovePen(0, 9);
	DrawLine(WindowWidth, 0);
	MovePen(0, 8.55);
	DrawLine(WindowWidth, 0);
	MovePen(0, 0);
	DrawLine(WindowWidth, 0);
	MovePen(0, 0.45);
	DrawLine(WindowWidth, 0);

}

void EchoInfo(void) {
	//ʵʱ��ʾ��Ϸ����
	SetPenColor("Black");
	char timeDisplay[100], scoreDisplay[100];
	sprintf(timeDisplay, "Used Time: %-.4lf", current_time);
	MovePen(5, 8.75);
	DrawTextString(timeDisplay);
	sprintf(scoreDisplay, "SCORE: %d", score);
	MovePen(7, 8.75);
	DrawTextString(scoreDisplay);
}