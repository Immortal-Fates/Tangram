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
	int pensize = GetPenSize();
	string pencolor = GetPenColor();
	SetPenColor("Black");
	SetPenSize(1);
	MovePen(0, 9);
	DrawLine(WindowWidth, 0);
	MovePen(0, 8.55);
	DrawLine(WindowWidth, 0);
	MovePen(0, 0);
	DrawLine(WindowWidth, 0);
	MovePen(0, 0.45);
	DrawLine(WindowWidth, 0);
	SetPenSize(pensize);	//back to system pensize
	SetPenColor(pencolor);	//back to system pencolor

}

void EchoInfo(void) {
	//ʵʱ��ʾ��Ϸ����
	int pensize = GetPenSize();
	string pencolor = GetPenColor();
	SetPenColor("Black");
	char timeDisplay[100], scoreDisplay[100],cu_map[100];
	sprintf(timeDisplay, "Used Time: %-.4lf", current_time);
	MovePen(1, 8.75);
	DrawTextString(timeDisplay);
	sprintf(scoreDisplay, "SCORE: %lf", score);
	MovePen(5, 8.75);
	DrawTextString(scoreDisplay);
	sprintf(cu_map, "map_number: %d", current_map);
	MovePen(10, 8.75);
	DrawTextString(cu_map);
	SetPenSize(pensize);	//back to system pensize
	SetPenColor(pencolor);	//back to system pencolor
}